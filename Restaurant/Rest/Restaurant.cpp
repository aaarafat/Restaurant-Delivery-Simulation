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
		Simulation(false);
		break;
	case MODE_STEP:
		Simulation(true);
		break;
	case MODE_SLNT:
		Silent_Simulation();
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
void Restaurant::AutoPromote(int cTime)
{
	for(int i = A_REG; i < REG_CNT; i++)
	{
		Reg[i]->AutoPromote(cTime, AutoPromo);
	}
}
//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while(EventsQueue.peekFront(pE))	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep)	//no more events at current time
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




/////////////////////////////////////////
//Reading input files



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
			Motorcycle* tmp = new Motorcycle(TYPE_NRM, SN, REGION(k)); 
			Reg[k]->setNormalMotor(tmp);
		}
		for(int i = 0; i < F; i++)
		{
			Motorcycle* tmp = new Motorcycle(TYPE_FROZ, SF, REGION(k)); 
			Reg[k]->setFrozenMotor(tmp);
		}
		for(int i = 0; i < V; i++)
		{
			Motorcycle* tmp = new Motorcycle(TYPE_VIP, SV, REGION(k)); 
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

//only outputs the final file and doesnt open a GUI
void Restaurant :: Silent_Simulation()   
{


	//Generate the Output File



}
/////////////////////////////////////////////////////

void Restaurant :: Simulation(bool StepByStep)
{
	pGUI->UpdateInterface();
	int CurrentTimeStep = 1;
	int x,y;
	// Save the drawings in a Linked List 
	while(!EventsQueue.isEmpty() || ActiveOrdersExist() || AssignedMotorsExist())
	{
		ArrivedMotors(CurrentTimeStep);

		//Execute the event and turn them into orders
		ExecuteEvents(CurrentTimeStep);

		//Print the number of the Orders in each region 
		AssignOrder(CurrentTimeStep);
		pGUI->PrintMessage(Reg[A_REG]->Print(), Reg[B_REG]->Print(), Reg[C_REG]->Print(), Reg[D_REG]->Print());

		//Drawing the Orders
		pGUI->ResetDrawingList();
		SharingOrdersToDraw();
		Draw_All();
		pGUI->PrintTime(CurrentTimeStep);
		
		//Check for Auto Promotion
		if(CurrentTimeStep>=AutoPromo)
			AutoPromote(CurrentTimeStep);

		//Advance timestep
		if(StepByStep)
			Sleep(1000);
		else
			pGUI->waitForClick();
			
		CurrentTimeStep++;	
	}
	
	pGUI->PrintTime(CurrentTimeStep - 1, RED);
	pGUI->PrintMessage("Test Done. Click Anywhere to terminate", Reg[A_REG]->Print(), Reg[B_REG]->Print(), Reg[C_REG]->Print(), Reg[D_REG]->Print());
	pGUI->waitForClick();


}

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
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

void Restaurant::SharingOrdersToDraw()
{
	for (int i=A_REG;i<REG_CNT;i++)
	{
		//create function to Share from Normal to Draw
		Reg[i]->SharingOrderstoDraw();
	}	
}
/////////////////////////////////
void Restaurant::DeleteFirstDrawn(int region)
{
	if(!Reg[region]->VIPOrderIsEmpty())
	{
		Order* O = Reg[region]->getVIPOrder();
		delete O;
	}
	if(!Reg[region]->FrozenOrderIsEmpty())
	{
		Order* O = Reg[region]->getFrozenOrder();
		delete O;
	}
		if(!Reg[region]->NormalOrderIsEmpty())
	{
		Order* O = Reg[region]->getNormalOrder();
		delete O;
	}
}

//////////////////////////////////////
bool Restaurant::ActiveOrdersExist()
{
	bool Exist = false;
	for (int i = A_REG; i < REG_CNT; i++)
		Exist = Reg[i]->NormalOrderIsEmpty() ? Exist : true;
	for (int i = A_REG; i < REG_CNT; i++)
		Exist = Reg[i]->VIPOrderIsEmpty() ? Exist : true;
	for (int i = A_REG; i < REG_CNT; i++)
		Exist = Reg[i]->FrozenOrderIsEmpty() ? Exist :true;
	return Exist;

}

/////////////////////////////////////
bool Restaurant::AssignedMotorsExist()
{
	bool Exist = false;
	for (int i = A_REG; i < REG_CNT; i++)
		Exist = Reg[i]->AssignedMotorsEmpty() ? Exist : true;
	for (int i = A_REG; i < REG_CNT; i++)
		Exist = Reg[i]->AssignedMotorsEmpty() ? Exist:true;
	for (int i = A_REG;i < REG_CNT; i++)
		Exist = Reg[i]->AssignedMotorsEmpty() ? Exist : true;
	return Exist;
}

/////////////////////////////////////
void Restaurant::ArrivedMotors(int CurrentTimeStep)
{
	for(int i = A_REG; i < REG_CNT; i++)
		Reg[i]->ArrivedMotors(CurrentTimeStep);
}

void Restaurant::AssignOrder(int CurrentTimeStep)
{
	for(int i = A_REG; i < REG_CNT; i++)
	{
		while(!Reg[i]->VIPOrderIsEmpty())
		{
			Order* Ord = NULL;
			Motorcycle* Moto = NULL;
			//vip motor then normal motor then frozen motor
			if(!Reg[i]->VIPMotorIsEmpty())
			{
				Ord = Reg[i]->getVIPOrder();
				Moto = Reg[i]->getVIPMotor();
			}
			else if(!Reg[i]->NormalMotorIsEmpty())
			{
				Ord = Reg[i]->getVIPOrder();
				Moto = Reg[i]->getNormalMotor();
			}
			else if(!Reg[i]->FrozenMotorIsEmpty())
			{
				Ord = Reg[i]->getVIPOrder();
				Moto = Reg[i]->getFrozenMotor();
			}
			if(Ord && Moto)
			{
				Ord->SetWaitTime(CurrentTimeStep);
				Ord->FinishOrder(Moto->GetSpeed());
				int ArriveTime = Ord->GetFinishTime() + ceil(Ord->GetDistance() * 1.0 / Moto->GetSpeed());
				Moto->SetArriveTime(ArriveTime);
				Reg[i]->setFinishedOrder(Ord);
				Reg[i]->setAssignedMotor(Moto);
			}
			else break;

		}
		while(!Reg[i]->FrozenOrderIsEmpty())
		{
			//frozen motor only
			if(!Reg[i]->FrozenMotorIsEmpty())
			{
				Order* Ord = Reg[i]->getFrozenOrder();
				Motorcycle* Moto = Reg[i]->getFrozenMotor();
				Ord->SetWaitTime(CurrentTimeStep);
				Ord->FinishOrder(Moto->GetSpeed());
				int ArriveTime = Ord->GetFinishTime() + ceil(Ord->GetDistance() * 1.0 / Moto->GetSpeed());
				Moto->SetArriveTime(ArriveTime);
				Reg[i]->setFinishedOrder(Ord);
				Reg[i]->setAssignedMotor(Moto);
			}
			else break;
		}
		while(!Reg[i]->NormalOrderIsEmpty())
		{
			//Normal motor if possible then vip motors
			Order* Ord = NULL;
			Motorcycle* Moto = NULL;
			if(!Reg[i]->NormalMotorIsEmpty())
			{
				Ord = Reg[i]->getNormalOrder();
				Moto = Reg[i]->getNormalMotor();
			}
			else if(!Reg[i]->VIPMotorIsEmpty())
			{
				Ord = Reg[i]->getNormalOrder();
				Moto = Reg[i]->getVIPMotor();
			}
			if(Ord && Moto)
			{
				Ord->SetWaitTime(CurrentTimeStep);
				Ord->FinishOrder(Moto->GetSpeed());
				int ArriveTime = Ord->GetFinishTime() + ceil(Ord->GetDistance() * 1.0 / Moto->GetSpeed());
				Moto->SetArriveTime(ArriveTime);
				Reg[i]->setFinishedOrder(Ord);
				Reg[i]->setAssignedMotor(Moto);
			}
			else break;
		}
	}

}
