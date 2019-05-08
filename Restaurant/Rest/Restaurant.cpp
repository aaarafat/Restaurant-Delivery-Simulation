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
		Reg[i] = new Region(this);
	}
	
	for(int i=A_REG;i<REG_CNT;i++)
		AssignedOrders[i] = "";
	CharityProfit=-1;
	CharityTimesteps=-1;
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
void Restaurant::ServingOrders(int cTime)
{
	for(int i = A_REG; i < REG_CNT; i++)
	{
		Reg[i]->ServingOrders(cTime);
		Reg[i]->AddCharityOrders(CharityProfit,CharityTimesteps,cTime);
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
	int S[MOTO_CNT], N[MOTO_CNT];
	if(pGUI->getSpeed())
	{
		for(int k = A_REG; k < REG_CNT; k++)
		{
			int speed;
			char type;
			char t[] = {'N', 'F', 'V'};
			for(int i = MOTO_NRM; i < MOTO_CNT; i++) fin>>N[i];
			for(int i = MOTO_NRM; i < MOTO_CNT; i++)
			{
				fin>>type;
				if(type != t[i]) 
				{
					pGUI->PrintMenuMessage("Please Choose a Valid File.");
					Sleep(2500);
					 return false;
				}
				for(int j = 0; j < N[i]; j++)
				{
					fin>>speed;
					Motorcycle* tmp = new Motorcycle(MOTO_TYPE(i), speed, REGION(k));
					Reg[k]->setMotor(tmp);
				}

			}
		}
	}
	else
	{
		for(int i = MOTO_NRM; i < MOTO_CNT; i++) fin>>S[i];
		for(int k = A_REG; k < REG_CNT; k++)
		{
			for(int i = MOTO_NRM; i < MOTO_CNT; i++) fin>>N[i];
			for(int i = MOTO_NRM; i < MOTO_CNT; i++)
			{
				for(int j = 0; j < N[i]; j++)
				{
					Motorcycle* tmp = new Motorcycle(MOTO_TYPE(i), S[i], REGION(k));
					Reg[k]->setMotor(tmp);
				}

			}
		}
	}
	fin>>AutoPromo;
	string t;int n;
	fin>>t;
	if(t[0] == 'C'|| t[0] == 'c')
	{
		fin>>CharityTimesteps>>CharityProfit>>n;
	}
	else
		n = stoi(t);
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
		while(!EventsQueue.isEmpty() || ActiveOrdersExist() || SMotorsExist())
		{
			ArrivedMotors(CurrentTimeStep);

			//Execute the event and turn them into orders
			ExecuteEvents(CurrentTimeStep);

			//Copying the string to temp for printing the last timestep
			for(int i=A_REG;i<REG_CNT;i++)
				AssignedOrderstemp[i] =AssignedOrders[i];

			//Print the number of the Orders in each region 
			AssignOrder(CurrentTimeStep);

			ServingOrders(CurrentTimeStep);

			if(!Silent)
			{
				Draw(CurrentTimeStep);

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
							Draw(CurrentTimeStep);	
						}
						else break;
					}
				}
				else
				{

					for(int i = 0; i < 250; i++)
					{
						pGUI->getClick(x,y);
						if(pGUI->MenuClicked(x,y))
						{
							Draw(CurrentTimeStep);
							i += 15; 
						}
							Sleep(1);
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
void Restaurant::Draw(int CurrentTimeStep)
{
	pGUI->PrintMessage(Reg[A_REG]->Print(), Reg[B_REG]->Print(), Reg[C_REG]->Print(), Reg[D_REG]->Print(),AssignedOrderstemp[0],AssignedOrderstemp[1],AssignedOrderstemp[2],AssignedOrderstemp[3]);
	pGUI->ResetDrawingList();
	SharingOrdersToDraw();
	Draw_All();
	pGUI->PrintTime(CurrentTimeStep);
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
bool Restaurant::getTraffic()
{
	return pGUI->getTraffic();
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
bool Restaurant::SMotorsExist() //returns true if there's still assigned, rest or damaged motorcycles
{
	for (int i = A_REG; i < REG_CNT; i++)
	{
		for(int j = ASSIGNED; j < STATUS_CNT; j++)
		{
			if(!Reg[i]->SMotorsEmpty((STATUS_TYPE)j))
			{
				return true;
			}
		}
	}
	return false;
}

/////////////////////////////////////
void Restaurant::ArrivedMotors(int CurrentTimeStep)
{
	for(int i = A_REG; i < REG_CNT; i++)
		Reg[i]->ArrivedMotors(CurrentTimeStep);
}

void Restaurant::AssignOrder(int CurrentTimeStep)
{
	for(int i=A_REG;i<REG_CNT;i++)
		AssignedOrders[i] = "";
	for(int i = A_REG; i < REG_CNT; i++)
	{
		while(!Reg[i]->CharityOrderIsEmpty())
		{
			Order* Ord = NULL;
			Motorcycle* Moto = NULL;
			if(!Reg[i]->MotorIsEmpty(MOTO_NRM))
			{
				Ord = Reg[i]->getCharityOrder();
				Moto = Reg[i]->getMotor(MOTO_NRM);
			}
			else if(!Reg[i]->SMotorsEmpty(REST_NRM))
			{
				Ord = Reg[i]->getCharityOrder();
				Moto = Reg[i]->getSMotor(REST_NRM);
				Moto->SetDamaged(true);
			}
			if(Ord && Moto)
			{
				Ord->SetWaitTime(CurrentTimeStep);
				Ord->FinishOrder(Moto->GetSpeed());
				int ArriveTime = Ord->GetFinishTime() + ceil(Ord->GetDistance() * 1.0 / Moto->GetSpeed());
				Moto->SetArriveTime(ArriveTime);
				FinishedOrders.add(Ord);
				Reg[i]->setAssignedOrder(Ord);
				Moto->SetStatus(ASSIGNED);
				Reg[i]->setSMotor(Moto);
				AssignedOrders[Ord->GetRegion()] += 'N' + to_string(Moto->GetID()) + "(CH" + to_string(Ord->GetID()) + ")  ";
			}
			else break;
		}

		while(!Reg[i]->VIPFrozenOrderIsEmpty())
		{
			Order* Ord = NULL;
			Motorcycle* Moto = NULL;
			if(!Reg[i]->MotorIsEmpty(MOTO_FROZ))
			{
				Ord = Reg[i]->getVIPFrozenOrder();
				Moto = Reg[i]->getMotor(MOTO_FROZ);
			}
			else if(!Reg[i]->SMotorsEmpty(REST_FROZ))
			{
				Ord = Reg[i]->getVIPFrozenOrder();
				Moto = Reg[i]->getSMotor(REST_FROZ);
				Moto->SetDamaged(true);
			}
			if(Ord && Moto)
			{
				Ord->SetWaitTime(CurrentTimeStep);
				Ord->FinishOrder(Moto->GetSpeed());
				int ArriveTime = Ord->GetFinishTime() + ceil(Ord->GetDistance() * 1.0 / Moto->GetSpeed());
				Moto->SetArriveTime(ArriveTime);
				FinishedOrders.add(Ord);
				Reg[i]->setAssignedOrder(Ord);
				Moto->SetStatus(ASSIGNED);
				Reg[i]->setSMotor(Moto);
				AssignedOrders[Ord->GetRegion()] += 'F' + to_string(Moto->GetID()) + "(VF" + to_string(Ord->GetID()) + ")  ";
			}
			else break;
		}

		while(!Reg[i]->VIPOrderIsEmpty())
		{
			Order* Ord = NULL;
			Motorcycle* Moto = NULL;
			if(!Reg[i]->MotorIsEmpty(MOTO_VIP))
			{
				Ord = Reg[i]->getVIPOrder();
				Moto = Reg[i]->getMotor(MOTO_VIP);
				AssignedOrders[Ord->GetRegion()] += 'V' + to_string(Moto->GetID()) + "(V" + to_string(Ord->GetID()) + ") ";
			}
			else if(!Reg[i]->MotorIsEmpty(MOTO_NRM))
			{
				Ord = Reg[i]->getVIPOrder();
				Moto = Reg[i]->getMotor(MOTO_NRM);
				AssignedOrders[Ord->GetRegion()] += 'N' + to_string(Moto->GetID()) + "(V" + to_string(Ord->GetID()) + ") ";
			}
			else if(!Reg[i]->MotorIsEmpty(MOTO_FROZ))
			{
				Ord = Reg[i]->getVIPOrder();
				Moto = Reg[i]->getMotor(MOTO_FROZ);
				AssignedOrders[Ord->GetRegion()] += 'F' + to_string(Moto->GetID()) + "(V" + to_string(Ord->GetID()) + ") ";
			}
			else if(!Reg[i]->SMotorsEmpty(REST_VIP))
			{
				Ord = Reg[i]->getVIPOrder();
				Moto = Reg[i]->getSMotor(REST_VIP);
				Moto->SetDamaged(true);
				AssignedOrders[Ord->GetRegion()] += 'V' + to_string(Moto->GetID()) + "(V" + to_string(Ord->GetID()) + ") ";
			}
			else if(!Reg[i]->SMotorsEmpty(REST_NRM))
			{
				Ord = Reg[i]->getVIPOrder();
				Moto = Reg[i]->getSMotor(REST_NRM);
				Moto->SetDamaged(true);
				AssignedOrders[Ord->GetRegion()] += 'N' + to_string(Moto->GetID()) + "(V" + to_string(Ord->GetID()) + ") ";
			}
			else if(!Reg[i]->SMotorsEmpty(REST_FROZ))
			{
				Ord = Reg[i]->getVIPOrder();
				Moto = Reg[i]->getSMotor(REST_FROZ);
				Moto->SetDamaged(true);
				AssignedOrders[Ord->GetRegion()] += 'F' + to_string(Moto->GetID()) + "(V" + to_string(Ord->GetID()) + ") ";
			}
			if(Ord && Moto)
			{
				Ord->SetWaitTime(CurrentTimeStep);
				Ord->FinishOrder(Moto->GetSpeed());
				int ArriveTime = Ord->GetFinishTime() + ceil(Ord->GetDistance() * 1.0 / Moto->GetSpeed());
				Moto->SetArriveTime(ArriveTime);
				Reg[i]->setAssignedOrder(Ord);
				FinishedOrders.add(Ord);
				Reg[i]->setAssignedOrder(Ord);
				Moto->SetStatus(ASSIGNED);
				Reg[i]->setSMotor(Moto);
			}
			else break;

		}
		while(!Reg[i]->FrozenOrderIsEmpty())
		{
			Order* Ord = NULL;
			Motorcycle* Moto = NULL;
			if(!Reg[i]->MotorIsEmpty(MOTO_FROZ))
			{
				Ord = Reg[i]->getFrozenOrder();
				Moto = Reg[i]->getMotor(MOTO_FROZ);
			}
			else if(!Reg[i]->SMotorsEmpty(REST_FROZ))
			{
				Ord = Reg[i]->getFrozenOrder();
				Moto = Reg[i]->getSMotor(REST_FROZ);
				Moto->SetDamaged(true);
			}
			if(Ord && Moto)
			{
				Ord->SetWaitTime(CurrentTimeStep);
				Ord->FinishOrder(Moto->GetSpeed());
				int ArriveTime = Ord->GetFinishTime() + ceil(Ord->GetDistance() * 1.0 / Moto->GetSpeed());
				Moto->SetArriveTime(ArriveTime);
				FinishedOrders.add(Ord);
				Reg[i]->setAssignedOrder(Ord);
				Moto->SetStatus(ASSIGNED);
				Reg[i]->setSMotor(Moto);
				AssignedOrders[Ord->GetRegion()] += 'F' + to_string(Moto->GetID()) + "(F" + to_string(Ord->GetID()) + ")  ";
			}
			else break;
		}
		while(!Reg[i]->NormalOrderIsEmpty())
		{
			Order* Ord = NULL;
			Motorcycle* Moto = NULL;
			if(!Reg[i]->MotorIsEmpty(MOTO_NRM))
			{
				Ord = Reg[i]->getNormalOrder();
				Moto = Reg[i]->getMotor(MOTO_NRM);
				AssignedOrders[Ord->GetRegion()] += 'N' + to_string(Moto->GetID()) + "(N" + to_string(Ord->GetID()) + ") ";
			}
			else if(!Reg[i]->MotorIsEmpty(MOTO_VIP))
			{
				Ord = Reg[i]->getNormalOrder();
				Moto = Reg[i]->getMotor(MOTO_VIP);
				AssignedOrders[Ord->GetRegion()] += 'V' + to_string(Moto->GetID()) + "(N" + to_string(Ord->GetID()) + ") ";
			}
			else if(!Reg[i]->SMotorsEmpty(REST_NRM))
			{
				Ord = Reg[i]->getNormalOrder();
				Moto = Reg[i]->getSMotor(REST_NRM);
				Moto->SetDamaged(true);
				AssignedOrders[Ord->GetRegion()] += 'N' + to_string(Moto->GetID()) + "(N" + to_string(Ord->GetID()) + ") ";
			}
			else if(!Reg[i]->SMotorsEmpty(REST_VIP))
			{
				Ord = Reg[i]->getNormalOrder();
				Moto = Reg[i]->getSMotor(REST_VIP);
				Moto->SetDamaged(true);
				AssignedOrders[Ord->GetRegion()] += 'V' + to_string(Moto->GetID()) + "(N" + to_string(Ord->GetID()) + ") ";
			}
			if(Ord && Moto)
			{
				Ord->SetWaitTime(CurrentTimeStep);
				Ord->FinishOrder(Moto->GetSpeed());
				int ArriveTime = Ord->GetFinishTime() + ceil(Ord->GetDistance() * 1.0 / Moto->GetSpeed());
				Moto->SetArriveTime(ArriveTime);
				FinishedOrders.add(Ord);
				Reg[i]->setAssignedOrder(Ord);
				Moto->SetStatus(ASSIGNED);
				Reg[i]->setSMotor(Moto);
			}
			else break;
		}
	}

}

void Restaurant :: PrintOutputFile(string file)
{
	file.append(".txt");
	ofstream Outfile(file);
	Order* ord = nullptr;
	//counters
	int totwait[REG_CNT] = {0}, totserve[REG_CNT] = {0} , ordcnt[REG_CNT][TYPE_CNT] = {0};

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
	int Orders = 0, Order_cnt[TYPE_CNT] = {0};
	int Motors = 0, Motor_cnt[MOTO_CNT] = {0};
	string str[] = {"Norm:", "Froz:", "VIP:", "VIPFrozen:", "Charity:"};
	int W = 0, S = 0; 
	for(int i = A_REG; i < REG_CNT; i++)
	{
		int sum_ord = 0, sum_moto = 0;
		for(int j = TYPE_NRM; j < TYPE_CNT; j++)
		{
			sum_ord += ordcnt[i][j];
			Order_cnt[j] += ordcnt[i][j];
		}
		for(int j = MOTO_NRM; j < MOTO_CNT; j++)
		{
			sum_moto += Reg[i]->getMotornum((MOTO_TYPE)j);
			Motor_cnt[j] += Reg[i]->getMotornum((MOTO_TYPE)j);
		}
		Orders += sum_ord;
		Motors += sum_moto;
		W += totwait[i]; S += totserve[i];
		Outfile<<endl<<"Region "<<(char)('A' + i)<<": "<<endl;
		Outfile<<setw(5)<<"Orders: "<<sum_ord<<" [";
		for(int j = TYPE_NRM; j < TYPE_CNT; j++)
		{
			if(j != 0) Outfile<<", ";
			Outfile<<str[j]<<to_string(ordcnt[i][j]);
		}
		Outfile<<"]"<<endl;
		Outfile<<setw(5)<<"MotorC: "<<sum_moto<<" [";
		for(int j = MOTO_NRM; j < MOTO_CNT; j++)
		{
			if(j != 0) Outfile<<", ";
			Outfile<<str[j]<<Reg[i]->getMotornum((MOTO_TYPE)j);
		}
		Outfile<<"]"<<endl;
		Outfile<<setw(5)<<"Avg Wait = "<<setprecision(5)<<(float)totwait[i] / (sum_ord)<<",  Avg Serv = "<<(float)totserve[i] / (sum_ord)<<endl;
	}

	//Retaurant
	Outfile<<endl<<"Restaurant: "<<endl;
	Outfile<<setw(5)<<"Orders: "<<Orders<<" [";
	for(int j = TYPE_NRM; j < TYPE_CNT; j++)
	{
		if(j != 0) Outfile<<", ";
		Outfile<<str[j]<<Order_cnt[j];
	}
	Outfile<<"]"<<endl;
	Outfile<<setw(5)<<"MotorC: "<<Motors<<" [";
	for(int j = MOTO_NRM; j < MOTO_CNT; j++)
	{
		if(j != 0) Outfile<<", ";
		Outfile<<str[j]<<Motor_cnt[j];
	}
	Outfile<<"]"<<endl;
	Outfile<<setw(5)<<"Avg Wait = "<<setprecision(5)<<(float)(W)/(Orders)<<",  Avg Serv = "<<(float)(S)/(Orders)<<endl;
	Outfile.close();
}