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
bool Region::ArrivedMotors(int TimeStep) 
{
	bool Arrived = true;
	bool Arrived_Flag = true;
	while (!AssignedMotorsEmpty() && Arrived_Flag)
	{
		Arrived_Flag = false;
		Motorcycle* AssignedMotor = AssignedMotors.peek();
		if (AssignedMotor->GetArriveTime() <= TimeStep)
		{
			Arrived = true;
			Arrived_Flag = true;
			AssignedMotors.remove();
			AssignedMotor->SetArriveTime(-1);
			
			if (AssignedMotor->GetArriveTime() > 5) AssignedMotor->SetRestTime(2);
			else AssignedMotor->SetRestTime(1);

			switch (AssignedMotor->GetType())
			{
			case TYPE_NRM:
				setNormalMotor(AssignedMotor);
				break;
				
			case TYPE_FROZ:
				setFrozenMotor(AssignedMotor);
				break;
				
			case TYPE_VIP:
				setVIPMotor(AssignedMotor);
				break;
			}
		}
	}
	return Arrived;
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
			+ "                                        Orders -->  VIP: "
			+ to_string(VIPOrder.Size()) + "    Served: " + to_string(VIPServed.Size())
			+ "    Frozen: " + to_string(FrozenOrder.Size()) + "    Served: " + to_string(FrozenServed.Size())
			+ "    Normal: " + to_string(NormalOrder.Size()) + "    Served: " + to_string(NormalServed.Size());
}
void Region::SharingOrderstoDraw()
{
	Queue<Order*> Q;
	Order* O;
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
