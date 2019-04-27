#include "Region.h"
#include <string>
int Region::cnt = 0;
Region::Region()
{
	name = 'A' + cnt;
	cnt++;
}

Motorcycle* Region::getVIPMotor()
{
	Motorcycle*M=VIPMotor.peek();
	VIPMotor.remove();
	return M;
}
Motorcycle* Region::getFrozenMotor()  
{
	Motorcycle*M=FrozenMotor.peek();
	FrozenMotor.remove();
	return M;
}
Motorcycle* Region::getNormalMotor() 
{
	Motorcycle*M=NormalMotor.peek();
	NormalMotor.remove();
	return M;
}
Order* Region::getVIPFrozenOrder()
{
	Order* O=VIPFrozenOrder.peek();
	VIPFrozenOrder.remove();
	return O;
}
Order* Region::getVIPOrder() 
{
	Order*O=VIPOrder.peek();
	VIPOrder.remove();
	return O;
}
Order* Region::getFrozenOrder() 
{
	Order* O;
	FrozenOrder.dequeue(O);
	return O;
}
Order* Region::getNormalServed() 
{
	Order*O;
	NormalServed.dequeue(O);
	return O;
}
Order* Region::getVIPServed() 
{
	Order*O;
	VIPServed.dequeue(O);
	return O;
}
Order* Region::getFrozenServed() 
{
	Order * O;
	FrozenServed.dequeue(O);
	return O;
}
Order* Region::getNormalOrder() 
{
	Order* O;
	NormalOrder.removeBegin(O);
	return O;
}
int Region::getVIPMotornum()
{
	return VIPMotor.Size();
}
int Region::getNormalMotornum()
{
	return NormalMotor.Size();
}
int Region::getFrozenMotornum()
{
	return FrozenMotor.Size();
}
void Region::setVIPMotor(Motorcycle* V)
{
	VIPMotor.add(V);
}
void Region::setFrozenMotor(Motorcycle* F)
{
	FrozenMotor.add(F);
}
void Region::setNormalMotor(Motorcycle* N)
{
	NormalMotor.add(N);
}
void Region::setVIPFrozenOrder(Order*O)
{
	VIPFrozenOrder.add(O);
}
void Region::setVIPOrder( Order* O)
{
	VIPOrder.add(O);
}
void Region::setFrozenOrder(Order* O)
{
	FrozenOrder.enqueue(O);
}
void Region::setNormalOrder(Order* O)
{
	NormalOrder.add(O);
}
void Region::setVIPServed(Order* O)
{
	VIPServed.enqueue(O);
}
void Region::setFrozenServed(Order* O)
{
	FrozenServed.enqueue(O);
}
void Region::setNormalServed(Order* O)
{
	NormalServed.enqueue(O);
}
void Region::setAssignedOrder(Order* O)
{
	AssignedOrder.add(O);
}

Order* Region::getAssignedOrder()
{
	Order * O = AssignedOrder.peek();
	AssignedOrder.remove();
	return O;
}

void Region::setAssignedMotor(Motorcycle* M)
{
	AssignedMotors.add(M);
}

void Region::setDamagedMotor(Motorcycle* M)
{
	DamagedMotors.add(M);
}

Motorcycle* Region::getDamagedMotor()
{
	Motorcycle* M = DamagedMotors.peek();
	DamagedMotors.remove();
	return M;
}

void Region::setRestMotor(Motorcycle* M)
{
	switch (M->GetType())
	{
		case TYPE_FROZ:
			RestFrozenMotors.add(M);
			break;
		case TYPE_NRM:
			RestNormalMotors.add(M);
			break;
		case TYPE_VIP:
			RestVIPMotors.add(M);
			break;
	}
}

Motorcycle* Region::getRestVIPMotor()
{
	Motorcycle* M = RestVIPMotors.peek();
	RestVIPMotors.remove();
	return M;
}
Motorcycle* Region::getRestNormalMotor()
{
	Motorcycle* M = RestNormalMotors.peek();
	RestFrozenMotors.remove();
	return M;
}
Motorcycle* Region::getRestFrozenMotor()
{
	Motorcycle* M = RestFrozenMotors.peek();
	RestFrozenMotors.remove();
	return M;
}
bool Region::VIPFrozenOrderIsEmpty() const
{
	return VIPFrozenOrder.isEmpty();
}
bool Region::VIPOrderIsEmpty() const
{
	return VIPOrder.isEmpty();
}
bool Region::NormalOrderIsEmpty() const
{
	return NormalOrder.isEmpty();
}
bool Region::FrozenOrderIsEmpty() const
{
	return FrozenOrder.isEmpty();
}
bool Region::AssignedMotorsEmpty() const
{
	return AssignedMotors.isEmpty();
}
bool Region::VIPMotorIsEmpty() const
{
	return VIPMotor.isEmpty();
}
bool Region::FrozenMotorIsEmpty() const
{
	return FrozenMotor.isEmpty();
}
bool Region::NormalMotorIsEmpty() const
{
	return NormalMotor.isEmpty();
}
bool Region::DamagedMotorsEmpty() const
{
	return DamagedMotors.isEmpty();
}
bool Region::RestVIPMotorsEmpty() const
{
	return RestVIPMotors.isEmpty();
}
bool Region::RestFrozenMotorsEmpty() const
{
	return RestFrozenMotors.isEmpty();
}
bool Region::RestNormalMotorsEmpty() const
{
	return RestNormalMotors.isEmpty();
}
bool Region::ArrivedMotors(int TimeStep) 
{
	bool Arrived = false;
	bool Arrived_Flag = true;
	while (!AssignedMotorsEmpty() && Arrived_Flag)
	{
		Arrived_Flag = false;
		Motorcycle* AssignedMotor = AssignedMotors.peek();
		if (AssignedMotor->GetArriveTime() <= TimeStep)
		{
			Arrived = true;
			Arrived_Flag = true;
			int RepairTime = AssignedMotor->GetRepairTime();
			int ArriveTime = AssignedMotor->GetArriveTime();
			AssignedMotors.remove();
			AssignedMotor->SetArriveTime(-1);
			AssignedMotor->SetRepairTime(-1);
			AssignedMotor->SetRestTime(-1);
			if (RepairTime != -1)
			{
				int rest;
				if (ArriveTime > 5) 
					rest = (4 + TimeStep);
				else 
					rest = (2 + TimeStep);
				AssignedMotor->SetRepairTime(rest + RepairTime);
				cout << " Repair Time : " << AssignedMotor->GetRepairTime() << endl;
				setDamagedMotor(AssignedMotor);
			}
			else
			{
				if (ArriveTime > 5) 
					AssignedMotor->SetRestTime(4 + TimeStep);
				
				else 
					AssignedMotor->SetRestTime(2 + TimeStep);
				setRestMotor(AssignedMotor);
			}
		}
	}
	return Arrived;
}

bool Region::RefreshedMotors(int TimeStep)
{
	bool Refreshed = false;
	bool Refreshed_Flag = true;
	while (!RestVIPMotorsEmpty() && Refreshed_Flag)
	{
		Refreshed_Flag = false;
		Motorcycle* RefMotor = RestVIPMotors.peek();
		if (RefMotor->GetRestTime() <= TimeStep)
		{
			Refreshed = true;
			Refreshed_Flag = true;
			RestVIPMotors.remove();
			RefMotor->SetRestTime(-1);
			RefMotor->SetRepairTime(-1);
			RefMotor->SetArriveTime(-1);
			setNormalMotor(RefMotor);
		}
	}
	while (!RestFrozenMotorsEmpty() && Refreshed_Flag)
	{
		Refreshed_Flag = false;
		Motorcycle* RefMotor = RestFrozenMotors.peek();
		if (RefMotor->GetRestTime() <= TimeStep)
		{
			Refreshed = true;
			Refreshed_Flag = true;
			RestFrozenMotors.remove();
			RefMotor->SetRestTime(-1);
			RefMotor->SetRepairTime(-1);
			RefMotor->SetArriveTime(-1);
			setFrozenMotor(RefMotor);
		}
	}
	while (!RestNormalMotorsEmpty() && Refreshed_Flag)
	{
		Refreshed_Flag = false;
		Motorcycle* RefMotor = RestNormalMotors.peek();
		if (RefMotor->GetRestTime() <= TimeStep)
		{
			Refreshed = true;
			Refreshed_Flag = true;
			RestNormalMotors.remove();
			RefMotor->SetRestTime(-1);
			RefMotor->SetRepairTime(-1);
			RefMotor->SetArriveTime(-1);
			setNormalMotor(RefMotor);
		}
	}
	return Refreshed;
}

bool Region::FixedMotors(int TimeStep)
{
	
	bool Fixed = false;
	bool Fixed_Flag = true;
	while (!DamagedMotorsEmpty() && Fixed_Flag)
	{
		Fixed_Flag = false;
		Motorcycle* FixedMotor = DamagedMotors.peek();
		if (FixedMotor->GetRepairTime() <= TimeStep)
		{
			Fixed = true;
			Fixed_Flag = true;
			DamagedMotors.remove();
			FixedMotor->SetRepairTime(-1);
			FixedMotor->SetArriveTime(-1);
			FixedMotor->SetRestTime(-1);
			switch (FixedMotor->GetType())
			{
				case TYPE_FROZ:
					setFrozenMotor(FixedMotor);
					break;
				case TYPE_VIP:
					setVIPMotor(FixedMotor);
					break;
				case TYPE_NRM:
					setNormalMotor(FixedMotor);
					break;
			}
		}
	}
	return Fixed;
}

bool Region::CancelOrder(int id)
{
	Order* O;
	return NormalOrder.getID(id,O);
	delete O;
}
bool Region::PromoteOrder(int id,int money)
{
	Order* O;
	 if(NormalOrder.getID(id,O))
	 {
		 O->toVIP(money);
		 VIPOrder.add(O);
		 return true;
	 }
	 else
		 return false;
}
void Region::AutoPromote(int cTime,int pTime)
{
	bool found = true;
	while(!NormalOrder.isEmpty()&&found)
	{
		Order* O = NormalOrder.getEntry(1);
		O->SetWaitTime(cTime);
		if(pTime <= O->GetWaitTime())
		{
			NormalOrder.removeBegin(O);
			O->toVIP();
			VIPOrder.add(O);
		}
		else
			found = false;
	}
}
void Region::ServingOrders(int cTime)
{
	bool found = true;
	while(!AssignedOrder.isEmpty() && found)
	{
		Order* O = AssignedOrder.peek();
		if(cTime >= O->GetFinishTime())
		{
			AssignedOrder.remove();
			ORD_TYPE type = O->GetType();
			switch (type)
			{
				case TYPE_NRM:
					NormalServed.enqueue(O);
					break;
				case TYPE_FROZ:
					FrozenServed.enqueue(O);
					break;
				case TYPE_VIP:
					VIPServed.enqueue(O);
					break;
			}
		}
		else
			found = false;

	}

}

//Draw functions

Order* Region::getDrawOrders(Order* O) 
{
	DrawOrders.dequeue(O);
	 return O;
}
void Region::setDrawOrders(Order* O)
{
	DrawOrders.enqueue(O);
}
bool Region::DrawOrdersIsEmpty() const
{
	return DrawOrders.isEmpty();
}
string Region::Print()
{
	return "Region " + name + ":    Motors -->  VIP: " + to_string(VIPMotor.Size()) 
			+ "    Frozen: " + to_string(FrozenMotor.Size()) 
			+ "    Normal: " + to_string(NormalMotor.Size())
			+ "    Damaged: " + to_string(DamagedMotors.Size())
			+ " Rest: "+to_string(RestNormalMotors.Size() + RestFrozenMotors.Size() + RestVIPMotors.Size())
			+ "                       Orders -->  VIP: "
			+ to_string(VIPOrder.Size()) + "    Served: " + to_string(VIPServed.Size())
			+ "    Frozen: " + to_string(FrozenOrder.Size()) + "    Served: " + to_string(FrozenServed.Size())
			+ "    Normal: " + to_string(NormalOrder.Size()) + "    Served: " + to_string(NormalServed.Size());
}
void Region::SharingOrderstoDraw()
{
	Queue<Order*> Q;
	Order* O;
	while(!VIPFrozenOrderIsEmpty())
	{
		O = VIPFrozenOrder.peek();
		VIPFrozenOrder.remove();
		DrawOrders.enqueue(O);
		Q.enqueue(O);

	}
	while(Q.dequeue(O))
	{
		VIPFrozenOrder.add(O);
	}
	while(!VIPOrderIsEmpty())
	{
		O = VIPOrder.peek();
		VIPOrder.remove();
		DrawOrders.enqueue(O);
		Q.enqueue(O);

	}
	while(Q.dequeue(O))
	{
		VIPOrder.add(O);
	}

	int size = FrozenOrder.Size();
	Order*temp = nullptr;

	for(int i=1;i<=size;i++)
	{
		FrozenOrder.dequeue(temp);
		DrawOrders.enqueue(temp);
		FrozenOrder.enqueue(temp);
	}

	size = NormalOrder.Size();
	temp = nullptr;

	for(int i=1;i<=size;i++)
	{
		NormalOrder.removeBegin(temp);
		DrawOrders.enqueue(temp);
		NormalOrder.add(temp);
	}
	
}

////////////////////////////////////////////////////
Region::~Region()
{
}
