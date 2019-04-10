#include <cstdlib>
#include <time.h>
#include <iostream>
#include <Windows.h>
using namespace std;

#include "Restaurant.h"

Restaurant::Restaurant() 
{
	pGUI = NULL;
	for(int i = A_REG; i < REG_CNT; i++)
	{
		Reg[i] = new Region();
	}

}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
	pGUI->PrintMessage("Select The input file.");
	while(!ReadFile(pGUI->GetFileName()))
	{
		mode = pGUI->getGUIMode();
		pGUI->PrintMessage("Select The input file.");
	}
	

	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		Interactive_Simulation();
		break;
	case MODE_STEP:
		StepByStep_Simulation();
		break;
	case MODE_SLNT:
		Silent_Simulation();
		break;
	case MODE_TEST:
		Test_Simulation();
		break;
	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}
bool Restaurant::CancelOrder(int id)
{
		for(int i = A_REG; i < REG_CNT; i++)
	{
		if(Reg[i]->CancelOrder(id)) 
		{
			return true;
		}
	}
		return false;
}
bool Restaurant::PromoteOrder(int id,int money)
{
		for(int i = A_REG; i < REG_CNT; i++)
	{
		if(Reg[i]->PromoteOrder(id,money)) 
		{
			return true;
		}
	}
		return false;
}
//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute();
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
	delete pGUI;
	for(int i = A_REG; i < REG_CNT; i++)
	{
		delete Reg[i];
	}
}




////////////////////////////////////////////////////////////////////////////////
/// ==> 
///  DEMO-related functions. Should be removed in phases 1&2

//This is just a demo function for project introductory phase
//It should be removed starting phase 1
void Restaurant::Just_A_Demo()
{
	
	//
	// THIS IS JUST A DEMO FUNCTION
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
	
	int EventCnt;	
	Order* pOrd;
	Event* pEv;
	srand(time(NULL));

	pGUI->PrintMessage("Just a Demo. Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->UpdateInterface();

	pGUI->PrintMessage("Generating orders randomly... In next phases, orders should be loaded from a file");
		
	int EvTime = 0;
	
	//Create Random events
	//All generated event will be "ArrivalEvents" for the demo
	for(int i=0; i<EventCnt; i++)
	{
		int O_id = i+1;
		
		//Rendomize order type
		int OType;
		if(i<EventCnt*0.2)	//let 1st 20% of orders be VIP (just for sake of demo)
			OType = TYPE_VIP;
		else if(i<EventCnt*0.5)	
			OType = TYPE_FROZ;	//let next 30% be Frozen
		else
			OType = TYPE_NRM;	//let the rest be normal

		
		int reg = rand()% REG_CNT;	//randomize region


		//Randomize event time
		EvTime += rand()%4;
		pEv = new ArrivalEvent(EvTime,O_id,(ORD_TYPE)OType,(REGION)reg, this);
		AddEvent(pEv);

	}	

	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while(!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep,timestep,10);	
		pGUI->PrintMessage(timestep);


		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		//The above line may add new orders to the DEMO_Queue

		//Let's draw all arrived orders by passing them to the GUI to draw

		Draw_All();
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
	}


	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

	
}
////////////////

void Restaurant::AddtoDemoQueue(Order *pOrd)
{
	DEMO_Queue.enqueue(pOrd);
}

Order* Restaurant::getDemoOrder()
{
	Order* pOrd;
	DEMO_Queue.dequeue(pOrd);
	return pOrd;

}


/// ==> end of DEMO-related function


bool Restaurant::ReadFile(string filename)
{
	ifstream fin;
	fin.open(filename);
	if(!fin.is_open())
	{
		return false;
	}
	int SN, SF, SV, N, F, V;
	fin>>SN>>SF>>SV;
	for(int k = A_REG; k < REG_CNT; k++)
	{
		fin>>N>>F>>V;
		for(int i = 0; i < N; i++)
		{
			Motorcycle* tmp = new Motorcycle(TYPE_NRM, SN, REGION(k), IDLE); 
			Reg[k]->setNormalMotor(tmp);
		}
		for(int i = 0; i < F; i++)
		{
			Motorcycle* tmp = new Motorcycle(TYPE_FROZ, SF, REGION(k), IDLE); 
			Reg[k]->setFrozenMotor(tmp);
		}
		for(int i = 0; i < V; i++)
		{
			Motorcycle* tmp = new Motorcycle(TYPE_VIP, SV, REGION(k), IDLE); 
			Reg[k]->setVIPMotor(tmp);
		}
	}
	fin>>AutoPromo;
	int n;
	fin>>n;
	for(int i = 0; i < n; i++)
	{
		Event* ptr;
		char s;
		fin>>s;
		switch (s)
		{
		case 'R':
			{
				ptr = new ArrivalEvent(this);
				ptr->ReadEvent(fin);
				break;
			}
		case 'X':
			{
				ptr = new CancelEvent(this);
				ptr->ReadEvent(fin);
				break;
			}
		case 'P':
			{
				ptr = new PromoEvent(this);
				ptr->ReadEvent(fin);
				break;
			}
		}
		AddEvent(ptr);
	}
	fin.close();

	return true;
}
Region* Restaurant::GetRegion(REGION x)
{
	return Reg[x];
}

//////////////////////////////////////////////////////////////
//// Functions of Simulation
//////////////////////////////////////////////////////////////


//Steps Only when mouse is clicked and outputs the final file
void Restaurant :: Interactive_Simulation()
{

	pGUI->PrintMessage("Interactive Simulation.Left Mouse Click to Step ");

	//Call The ReadFile Function And Assign the Events to the Events Queue

	//Loop on the Events Queue to execute the active Events

	//Delete Finished Orders

	//Generate the Output File

	pGUI->PrintMessage("Simulation Finished. Please Click to Exit");
	pGUI->waitForClick();

}

////////////


//steps every one second and outputs the final file
void Restaurant :: StepByStep_Simulation()
{

	pGUI->PrintMessage("Step By Step Simulation. Steps Every One second. Click to start Simulation.");

	//Call The ReadFile Function And Assign the Events to the Events Queue

	//Loop on the Events Queue to execute the active Events

	//Delete Finished Orders

	//Generate the Output File

	pGUI->PrintMessage("Simulation Finished. Please Click to Exit");
	pGUI->waitForClick();

}

////////////


//only outputs the final file and doesnt open a GUI
void Restaurant :: Silent_Simulation()   
{


	//Generate the Output File



}

/////////////////////////////////////////////////////


/////////////////////////////
////Testing Functions 
////////////////////////////

void Restaurant :: Test_Simulation()
{
	pGUI->UpdateInterface();
		
	int CurrentTimeStep = 1;
	//string mn, secs;
	int x,y;
	// Save the drawings in a Linked List 
	while(!EventsQueue.isEmpty()||ActiveOrdersExist())
	{
		//print current timestep
		//Delete the highest priority from each region
		for(int i=0;i<4;i++)
			DeleteFirstDrawn(i);
		//Execute the event and turn them into orders
		ExecuteEvents(CurrentTimeStep);
		//Print the number of the Orders in each region 
		pGUI->PrintMessage(Reg[A_REG]->Print(), Reg[B_REG]->Print(), Reg[C_REG]->Print(), Reg[D_REG]->Print());
		//Drawing the Orders
		pGUI->ResetDrawingList();
		CopyOrdersToDraw();
		Draw_All();
		pGUI->PrintTime(CurrentTimeStep);
		pGUI->waitForClick();
		CurrentTimeStep++;	//advance timestep
	}
	for(int i = 0; i < 4; i++)
	{
		DeleteFirstDrawn(i);
		ExecuteEvents(CurrentTimeStep);
		
		pGUI->PrintMessage(Reg[A_REG]->Print(), Reg[B_REG]->Print(), Reg[C_REG]->Print(), Reg[D_REG]->Print());
		//execute all events at current time step
		//The above line may add new orders to the DEMO_Queue

		//Let's draw all arrived orders by passing them to the GUI to draw
		//function to draw 
		pGUI->ResetDrawingList();
		CopyOrdersToDraw();
		Draw_All();
		pGUI->PrintTime(CurrentTimeStep);
		pGUI->waitForClick();
		CurrentTimeStep++;


	}
	pGUI->PrintTime(CurrentTimeStep - 1, RED);
	pGUI->PrintMessage("Test Done. Click Anywhere to terminate", Reg[A_REG]->Print(), Reg[B_REG]->Print(), Reg[C_REG]->Print(), Reg[D_REG]->Print());
	pGUI->waitForClick();


}

/////////////////////////////////////////////////////

void Restaurant :: Draw_All()
{
	Order* pOrd=nullptr;
	bool Empty;
	for(int i = A_REG; i < REG_CNT; i++)
	{
		Empty=Reg[i]->DrawOrdersIsEmpty();
		while(!Empty)
		{
			pOrd=Reg[i]->getDrawOrders(pOrd);
			pGUI->AddOrderForDrawing(pOrd);
			Empty=Reg[i]->DrawOrdersIsEmpty();
		}
	}

	pGUI->UpdateInterface();

}

void Restaurant::CopyOrdersToDraw()
{
	for (int i=A_REG;i<REG_CNT;i++)
		{
			//create function to copy from Normal to Draw
			Reg[i]->CopyOrderstoDraw();


		}	
}/////////////////////////////////
void Restaurant::DeleteFirstDrawn(int region)
{
	switch(region)
		{case A_REG:
			if(!Reg[A_REG]->VIPOrderIsEmpty())
			{
				Order* O = Reg[A_REG]->getVIPOrder();
				delete O;
			}
			else if(!Reg[A_REG]->FrozenOrderIsEmpty())
			{
				Order* O = Reg[A_REG]->getFrozenOrder();
				delete O;
			}
			else if(!Reg[A_REG]->NormalOrderIsEmpty())
			{
				Order* O = Reg[A_REG]->getNormalOrder();
				delete O;
			}
			break;
		case B_REG:
			if(!Reg[B_REG]->VIPOrderIsEmpty())
			{
				Order* O = Reg[B_REG]->getVIPOrder();
				delete O;
			}
			else if(!Reg[B_REG]->FrozenOrderIsEmpty())
			{
				Order* O = Reg[B_REG]->getFrozenOrder();
				delete O;
			}
			else if(!Reg[B_REG]->NormalOrderIsEmpty())
			{
				Order* O = Reg[B_REG]->getNormalOrder();
				delete O;
			}
			break;
		case C_REG:
			if(!Reg[C_REG]->VIPOrderIsEmpty())
			{
				Order* O = Reg[C_REG]->getVIPOrder();
				delete O;
			}
			else if(!Reg[C_REG]->FrozenOrderIsEmpty())
			{
				Order* O = Reg[C_REG]->getFrozenOrder();
				delete O;
			}
			else if(!Reg[C_REG]->NormalOrderIsEmpty())
			{
				Order* O = Reg[C_REG]->getNormalOrder();
				delete O;
			}
			break;
		case D_REG:
			if(!Reg[D_REG]->VIPOrderIsEmpty())
			{
				Order* O = Reg[D_REG]->getVIPOrder();
				delete O;
			}
			else if(!Reg[D_REG]->FrozenOrderIsEmpty())
			{
				Order* O = Reg[D_REG]->getFrozenOrder();
				delete O;
			}
			else if(!Reg[D_REG]->NormalOrderIsEmpty())
			{
				Order* O = Reg[D_REG]->getNormalOrder();
				delete O;
			}
			break;
		}
}

//////////////////////////////////////
bool Restaurant::ActiveOrdersExist()
{
	bool Exist=false;
	for (int i=A_REG;i<REG_CNT;i++)
		Exist=Reg[i]->NormalOrderIsEmpty()?Exist:true;
	for (int i=A_REG;i<REG_CNT;i++)
		Exist=Reg[i]->VIPOrderIsEmpty()?Exist:true;
	for (int i=A_REG;i<REG_CNT;i++)
		Exist=Reg[i]->FrozenOrderIsEmpty()?Exist:true;
	return Exist;

}