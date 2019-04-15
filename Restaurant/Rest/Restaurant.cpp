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

	AssignedOrders="";
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
	pGUI->PrintMenuMessage("Select The input file.");
	while(!ReadFile(pGUI->GetFileName()))
	{
		mode = pGUI->getGUIMode();
		pGUI->PrintMenuMessage("Select The input file.");
	}

	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		Simulation(false,false);
		break;
	case MODE_STEP:
		Simulation(true,false);
		break;
	case MODE_SLNT:
		Simulation(true,true);
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

void Restaurant :: Simulation(bool StepByStep,bool Silent)
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

			//Copying the string to temp for printing the last timestep
			AssignedOrderstemp=AssignedOrders;

			//Print the number of the Orders in each region 
			AssignOrder(CurrentTimeStep);
			if(!Silent)
			{
				Draw(false,CurrentTimeStep);

			}
			//Check for Auto Promotion
			if(CurrentTimeStep>=AutoPromo)
				AutoPromote(CurrentTimeStep);

			//Advance timestep
			if(!Silent)
			{
				if(!StepByStep)
				{
					while(true)
					{
						pGUI->waitForClick(x,y);
						if(pGUI->MenuClicked(x,y))
						{
							Draw(StepByStep,CurrentTimeStep);	
						}
						else break;
					}
				}
				else
				{

					/*pGUI->getClick(x,y);
					if(pGUI->MenuClicked(x,y))
					{
						Draw(StepByStep,CurrentTimeStep);
					}
					else{
						Sleep(1000);
						//pGUI->ClearMouseClicks();
					}*/
					//to get action while sleeping we divide the sleeping period into 200 parts
					for(int i = 0; i < 200; i++)
					{
						pGUI->getClick(x,y);
						if(pGUI->MenuClicked(x,y))
						{
							Draw(StepByStep,CurrentTimeStep);
							i += 100; //we already slept 500 ms in the draw function
						}
						Sleep(5);
					}
				}
			}
			CurrentTimeStep++;	
		}
	if(!Silent)
	{
		pGUI->PrintTime(CurrentTimeStep - 1, RED);

		pGUI->PrintMessage("Click Anywhere to terminate", Reg[A_REG]->Print(), Reg[B_REG]->Print(), Reg[C_REG]->Print(), Reg[D_REG]->Print());
	}
	pGUI->PrintMenuMessage("Save the Output file");
	PrintOutputFile(pGUI->SaveFileName());
	pGUI->PrintMessage("Click Anywhere to terminate");
	pGUI->PrintMenuMessage("Simulation Done Check Output file");
	pGUI->waitForClick(x,y);

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
void Restaurant::Draw(bool StepByStep,int CurrentTimeStep)
{
	if(StepByStep) Sleep(250);
	pGUI->PrintMessage(Reg[A_REG]->Print(), Reg[B_REG]->Print(), Reg[C_REG]->Print(), Reg[D_REG]->Print(),AssignedOrderstemp);
	pGUI->ResetDrawingList();
	SharingOrdersToDraw();
	Draw_All();
	pGUI->PrintTime(CurrentTimeStep);
	if(StepByStep) Sleep(250);
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
	AssignedOrders="";
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
				AssignedOrders+='V'+to_string(Moto->GetID())+"(V"+to_string(Ord->GetID())+") ";
			}
			else if(!Reg[i]->NormalMotorIsEmpty())
			{
				Ord = Reg[i]->getVIPOrder();
				Moto = Reg[i]->getNormalMotor();
				AssignedOrders+='N'+to_string(Moto->GetID())+"(V"+to_string(Ord->GetID())+") ";
			}
			else if(!Reg[i]->FrozenMotorIsEmpty())
			{
				Ord = Reg[i]->getVIPOrder();
				Moto = Reg[i]->getFrozenMotor();
				AssignedOrders+='F'+to_string(Moto->GetID())+"(V"+to_string(Ord->GetID())+") ";
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
				AssignedOrders+='F'+to_string(Moto->GetID())+"(F"+to_string(Ord->GetID())+")  ";
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
				AssignedOrders+='N'+to_string(Moto->GetID())+"(N"+to_string(Ord->GetID())+") ";
			}
			else if(!Reg[i]->VIPMotorIsEmpty())
			{
				Ord = Reg[i]->getNormalOrder();
				Moto = Reg[i]->getVIPMotor();
				AssignedOrders+='V'+to_string(Moto->GetID())+"(N"+to_string(Ord->GetID())+") ";
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

void Restaurant :: PrintOutputFile(string file)
{
	file.append(".txt");
	ofstream Outfile(file);
	Order*ord=nullptr;
	//counters
	int totwait[4] = {0}, totserve[4] = {0} , ordcnt[4][3] = {0};

	Outfile<<" FT\tID\tAT\tWT\tST"<<endl;
	while(!FinishedOrders.isEmpty())
	{
		ord = FinishedOrders.peek();
		FinishedOrders.remove();
		REGION reg = ord->GetRegion();
		totwait[reg] += ord->GetWaitTime();
		totserve[reg] += ord->getServeTime();
		ordcnt[reg][ord->GetType()]++;

		Outfile<<setw(3)<<ord->GetFinishTime()<<"\t"<<ord->GetID()<<"\t"<<ord->getArrTime()<<"\t"<<ord->GetWaitTime()<<"\t"<<ord->getServeTime()<<endl;
		delete ord;
	}
	//Restaurant Counters
	int Orders = 0, Normal = 0, Frozen = 0, VIP = 0;
	int Motors = 0, MNormal = 0, MFrozen = 0, MVIP = 0;
	int W = 0, S = 0; 
	for(int i = A_REG; i < REG_CNT; i++)
	{
		int sum_ord = ordcnt[i][TYPE_NRM] + ordcnt[i][TYPE_FROZ] + ordcnt[i][TYPE_VIP];
		int sum_moto = Reg[i]->getVIPMotornum() + Reg[i]->getNormalMotornum() + Reg[i]->getFrozenMotornum();
		Orders += sum_ord;
		Motors += sum_moto;
		W += totwait[i]; S += totserve[i];
		Normal += ordcnt[i][TYPE_NRM]; Frozen += ordcnt[i][TYPE_FROZ]; VIP += ordcnt[i][TYPE_VIP];
		MNormal += Reg[i]->getNormalMotornum(); MFrozen += Reg[i]->getFrozenMotornum(); MVIP += Reg[i]->getVIPMotornum();
		Outfile<<endl<<"Region "<<(char)('A' + i)<<": "<<endl;
		Outfile<<setw(5)<<"Orders: "<<sum_ord<<" [Norm:"<<ordcnt[i][TYPE_NRM]<<", Froz:"<<ordcnt[i][TYPE_FROZ]<<", VIP:"<<ordcnt[i][TYPE_VIP]<<"]"<<endl;
		Outfile<<setw(5)<<"MotorC: "<<sum_moto<<" [Norm:"<<Reg[i]->getNormalMotornum()<<", Froz:"<<Reg[i]->getFrozenMotornum()<<", VIP:"<<Reg[i]->getVIPMotornum()<<"]"<<endl;
		Outfile<<setw(5)<<"Avg Wait = "<<setprecision(5)<<(float)totwait[i] / (sum_ord)<<",  Avg Serv = "<<(float)totserve[i] / (sum_ord)<<endl;
	}

	//Retaurant
	Outfile<<endl<<"Restaurant: "<<endl;
	Outfile<<setw(5)<<"Orders: "<<Orders<<" [Norm:"<<Normal<<", Froz:"<<Frozen<<",VIP:"<<VIP<<"]"<<endl;
	Outfile<<setw(5)<<"MotorC: "<<Motors;
	Outfile<<" [Norm:"<<MNormal<<", Froz:"<<MFrozen<<",VIP:"<<MVIP<<"]"<<endl;
	Outfile<<setw(5)<<"Avg Wait = "<<setprecision(5)<<(float)(W)/(Orders)<<",  Avg Serv = "<<(float)(S)/(Orders)<<endl;
	Outfile.close();
}