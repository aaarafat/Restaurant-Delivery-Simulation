#include <cstdlib>
#include <time.h>
#include <iostream>
#include <Windows.h>
#include <iomanip>
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
void Restaurant::AutoPromote(int cTime)
{
		for(int i = A_REG; i < REG_CNT; i++)
	{
		Reg[i]->AutoPromote(cTime,AutoPromo);
	}
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
	while(!EventsQueue.isEmpty() || ActiveOrdersExist() || AssignedMotorsExist())
	{
		//print current timestep
		//Delete the highest priority order from each type in each region

		/*for(int i=A_REG;i<REG_CNT;i++)
		{	
			DeleteFirstDrawn(i);
		}*/
		ArrivedMotors(CurrentTimeStep);

		//Execute the event and turn them into orders
		ExecuteEvents(CurrentTimeStep);
		//Print the number of the Orders in each region 
		AssignOrder(CurrentTimeStep);
		pGUI->PrintMessage(Reg[A_REG]->Print(), Reg[B_REG]->Print(), Reg[C_REG]->Print(), Reg[D_REG]->Print());
		//Drawing the Orders
		pGUI->ResetDrawingList();
		CopyOrdersToDraw();
		Draw_All();
		pGUI->PrintTime(CurrentTimeStep);
		pGUI->waitForClick();
		/*if(CurrentTimeStep>=AutoPromo)
			AutoPromote(CurrentTimeStep);*/
		CurrentTimeStep++;	//advance timestep
	}
	
	pGUI->PrintTime(CurrentTimeStep - 1, RED);
	pGUI->PrintMessage("Test Done. Click Anywhere to terminate", Reg[A_REG]->Print(), Reg[B_REG]->Print(), Reg[C_REG]->Print(), Reg[D_REG]->Print());
	pGUI->waitForClick();
	PrintOutputFile();


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
}
/////////////////////////////////
void Restaurant::DeleteFirstDrawn(int region)
{
	switch(region)
		{case A_REG:
			if(!Reg[A_REG]->VIPOrderIsEmpty())
			{
				Order* O = Reg[A_REG]->getVIPOrder();
				delete O;
			}
			if(!Reg[A_REG]->FrozenOrderIsEmpty())
			{
				Order* O = Reg[A_REG]->getFrozenOrder();
				delete O;
			}
			 if(!Reg[A_REG]->NormalOrderIsEmpty())
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
			if(!Reg[B_REG]->FrozenOrderIsEmpty())
			{
				Order* O = Reg[B_REG]->getFrozenOrder();
				delete O;
			}
			if(!Reg[B_REG]->NormalOrderIsEmpty())
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
			if(!Reg[C_REG]->FrozenOrderIsEmpty())
			{
				Order* O = Reg[C_REG]->getFrozenOrder();
				delete O;
			}
			if(!Reg[C_REG]->NormalOrderIsEmpty())
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
			if(!Reg[D_REG]->FrozenOrderIsEmpty())
			{
				Order* O = Reg[D_REG]->getFrozenOrder();
				delete O;
			}
			if(!Reg[D_REG]->NormalOrderIsEmpty())
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
			//vip motor or normal motor or frozen motor
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
				FinishedOrders.add(Ord);
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
				FinishedOrders.add(Ord);
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
				FinishedOrders.add(Ord);
				Reg[i]->setAssignedMotor(Moto);
			}
			else break;
		}
	}

}

void Restaurant :: PrintOutputFile()
{
	string Out="Output.txt";
	ofstream Outfile(Out);
	Order*ord=nullptr;
	//counters
	int Avip=0,Anorm=0,Afroz=0,Atotwait=0,Atotserve=0;
	int Bvip=0,Bnorm=0,Bfroz=0,Btotwait=0,Btotserve=0;
	int Cvip=0,Cnorm=0,Cfroz=0,Ctotwait=0,Ctotserve=0;
	int Dvip=0,Dnorm=0,Dfroz=0,Dtotwait=0,Dtotserve=0;

	Outfile<<"FT  ID  AT  WT  ST"<<endl;
	while(!FinishedOrders.isEmpty())
	{
		ord=FinishedOrders.peek();
		FinishedOrders.remove();

		switch(ord->GetRegion())
		{
			case(A_REG):
				{
					switch(ord->GetType())
					{
						case(TYPE_VIP):
							{
								Avip++;
								Atotwait+=ord->GetWaitTime();
								Atotserve+=ord->getServeTime();
								break;
							}
						case(TYPE_FROZ):
							{
								Afroz++;
								Atotwait+=ord->GetWaitTime();
								Atotserve+=ord->getServeTime();
								break;
							}
						case(TYPE_NRM):
							{
								Anorm++;
								Atotwait+=ord->GetWaitTime();
								Atotserve+=ord->getServeTime();
								break;
							}
					}
					break;
				}

			case(B_REG):
				{
					switch(ord->GetType())
					{
						case(TYPE_VIP):
							{
								Bvip++;
								Btotwait+=ord->GetWaitTime();
								Btotserve+=ord->getServeTime();
								break;
							}
						case(TYPE_FROZ):
							{
								Bfroz++;
								Btotwait+=ord->GetWaitTime();
								Btotserve+=ord->getServeTime();
								break;
							}
						case(TYPE_NRM):
							{
								Bnorm++;
								Btotwait+=ord->GetWaitTime();
								Btotserve+=ord->getServeTime();
								break;
							}
					}
					break;
				}
			case(C_REG):
				{
					switch(ord->GetType())
					{
						case(TYPE_VIP):
							{
								Cvip++;
								Ctotwait+=ord->GetWaitTime();
								Ctotserve+=ord->getServeTime();
								break;
							}
						case(TYPE_FROZ):
							{
								Cfroz++;
								Ctotwait+=ord->GetWaitTime();
								Ctotserve+=ord->getServeTime();
								break;
							}
						case(TYPE_NRM):
							{
								Cnorm++;
								Ctotwait+=ord->GetWaitTime();
								Ctotserve+=ord->getServeTime();
								break;
							}
					}
					break;
				}
			case(D_REG):
				{
					switch(ord->GetType())
					{
						case(TYPE_VIP):
							{
								Dvip++;
								Dtotwait+=ord->GetWaitTime();
								Dtotserve+=ord->getServeTime();
								break;
							}
						case(TYPE_FROZ):
							{
								Dfroz++;
								Dtotwait+=ord->GetWaitTime();
								Dtotserve+=ord->getServeTime();
								break;
							}
						case(TYPE_NRM):
							{
								Dnorm++;
								Dtotwait+=ord->GetWaitTime();
								Dtotserve+=ord->getServeTime();
								break;
							}
					}
					break;
				}
		}

		Outfile<<setw(2)<<ord->GetFinishTime()<<setw(6)<<ord->GetID()<<setw(6)<<ord->getArrTime()<<setw(8)<<ord->GetWaitTime()<<setw(6)<<ord->getServeTime()<<endl;
	}
	//Region A
	Outfile<<endl<<"Region A: "<<endl;
	Outfile<<setw(5)<<"Orders: "<<Avip+Anorm+Afroz<<" [Norm:"<<Anorm<<", Froz:"<<Afroz<<",VIP:"<<Avip<<"]"<<endl;
	Outfile<<setw(5)<<"MotorC: "<<Reg[A_REG]->getVIPMotornum()+Reg[A_REG]->getNormalMotornum()+Reg[A_REG]->getFrozenMotornum()<<" [Norm:"<<Reg[A_REG]->getNormalMotornum()<<", Froz:"<<Reg[A_REG]->getFrozenMotornum()<<",VIP:"<<Reg[A_REG]->getVIPMotornum()<<"]"<<endl;
	Outfile<<setw(5)<<"Avg Wait = "<<setprecision(5)<<(float)Atotwait/(Avip+Anorm+Afroz)<<",  Avg Serv = "<<(float)Atotserve/(Avip+Anorm+Afroz)<<endl;

	//Region B
	Outfile<<endl<<"Region B: "<<endl;
	Outfile<<setw(5)<<"Orders: "<<Bvip+Bnorm+Bfroz<<" [Norm:"<<Bnorm<<", Froz:"<<Bfroz<<",VIP:"<<Bvip<<"]"<<endl;
	Outfile<<setw(5)<<"MotorC: "<<Reg[B_REG]->getVIPMotornum()+Reg[B_REG]->getNormalMotornum()+Reg[B_REG]->getFrozenMotornum()<<" [Norm:"<<Reg[B_REG]->getNormalMotornum()<<", Froz:"<<Reg[B_REG]->getFrozenMotornum()<<",VIP:"<<Reg[B_REG]->getVIPMotornum()<<"]"<<endl;
	Outfile<<setw(5)<<"Avg Wait = "<<setprecision(5)<<(float)Btotwait/(Bvip+Bnorm+Bfroz)<<",  Avg Serv = "<<(float)Btotserve/(Bvip+Bnorm+Bfroz)<<endl;

	//Region C
	Outfile<<endl<<"Region C: "<<endl;
	Outfile<<setw(5)<<"Orders: "<<Cvip+Cnorm+Cfroz<<" [Norm:"<<Cnorm<<", Froz:"<<Cfroz<<",VIP:"<<Cvip<<"]"<<endl;
	Outfile<<setw(5)<<"MotorC: "<<Reg[C_REG]->getVIPMotornum()+Reg[C_REG]->getNormalMotornum()+Reg[C_REG]->getFrozenMotornum()<<" [Norm:"<<Reg[C_REG]->getNormalMotornum()<<", Froz:"<<Reg[C_REG]->getFrozenMotornum()<<",VIP:"<<Reg[C_REG]->getVIPMotornum()<<"]"<<endl;
	Outfile<<setw(5)<<"Avg Wait = "<<setprecision(5)<<(float)Ctotwait/(Cvip+Cnorm+Cfroz)<<",  Avg Serv = "<<(float)Ctotserve/(Cvip+Cnorm+Cfroz)<<endl;

	//Region D
	Outfile<<endl<<"Region D: "<<endl;
	Outfile<<setw(5)<<"Orders: "<<Dvip+Dnorm+Dfroz<<" [Norm:"<<Dnorm<<", Froz:"<<Dfroz<<",VIP:"<<Dvip<<"]"<<endl;
	Outfile<<setw(5)<<"MotorC: "<<Reg[D_REG]->getVIPMotornum()+Reg[D_REG]->getNormalMotornum()+Reg[D_REG]->getFrozenMotornum()<<" [Norm:"<<Reg[D_REG]->getNormalMotornum()<<", Froz:"<<Reg[D_REG]->getFrozenMotornum()<<",VIP:"<<Reg[D_REG]->getVIPMotornum()<<"]"<<endl;
	Outfile<<setw(5)<<"Avg Wait = "<<setprecision(5)<<(float)Dtotwait/(Dvip+Dnorm+Dfroz)<<",  Avg Serv = "<<(float)Dtotserve/(Dvip+Dnorm+Dfroz)<<endl;

	//Retaurant
	Outfile<<endl<<"Restaurant: "<<endl;
	Outfile<<setw(5)<<"Orders: "<<Avip+Anorm+Afroz+Bvip+Bnorm+Bfroz+Cvip+Cnorm+Cfroz+Dvip+Dnorm+Dfroz<<" [Norm:"<<Anorm+Bnorm+Cnorm+Dnorm<<", Froz:"<<Afroz+Bfroz+Cfroz+Dfroz<<",VIP:"<<Avip+Bvip+Cvip+Dvip<<"]"<<endl;
	Outfile<<setw(5)<<"MotorC: "<<Reg[A_REG]->getVIPMotornum()+Reg[A_REG]->getNormalMotornum()+Reg[A_REG]->getFrozenMotornum()+Reg[B_REG]->getVIPMotornum()+Reg[B_REG]->getNormalMotornum()+Reg[B_REG]->getFrozenMotornum()+Reg[C_REG]->getVIPMotornum()+Reg[C_REG]->getNormalMotornum()+Reg[C_REG]->getFrozenMotornum()+Reg[D_REG]->getVIPMotornum()+Reg[D_REG]->getNormalMotornum()+Reg[D_REG]->getFrozenMotornum();
	Outfile<<" [Norm:"<<Reg[A_REG]->getNormalMotornum()+Reg[B_REG]->getNormalMotornum()+Reg[C_REG]->getNormalMotornum()+Reg[D_REG]->getNormalMotornum()<<", Froz:"<<Reg[A_REG]->getFrozenMotornum()+Reg[B_REG]->getFrozenMotornum()+Reg[C_REG]->getFrozenMotornum()+Reg[D_REG]->getFrozenMotornum()<<",VIP:"<<Reg[A_REG]->getVIPMotornum()+Reg[B_REG]->getVIPMotornum()+Reg[C_REG]->getVIPMotornum()+Reg[D_REG]->getVIPMotornum()<<"]"<<endl;
	Outfile<<setw(5)<<"Avg Wait = "<<setprecision(5)<<(float)(Atotwait+Btotwait+Ctotwait+Dtotwait)/(Avip+Anorm+Afroz+Bvip+Bnorm+Bfroz+Cvip+Cnorm+Cfroz+Dvip+Dnorm+Dfroz)<<",  Avg Serv = "<<(float)(Atotserve+Btotserve+Ctotserve+Dtotserve)/(Avip+Anorm+Afroz+Bvip+Bnorm+Bfroz+Cvip+Cnorm+Cfroz+Dvip+Dnorm+Dfroz)<<endl;
}