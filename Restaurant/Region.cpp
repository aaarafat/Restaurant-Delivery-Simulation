#include "Region.h"
#include "Rest\Restaurant.h"
#include <string>
int Region::cnt = 0;
Region::Region(Restaurant* ptr)
{
	pRest = ptr;
	name = 'A' + cnt;
	cnt++;
}
Motorcycle* Region::getMotor(MOTO_TYPE type)
{
	Motorcycle* M = Motor[type].peek();
	Motor[type].remove();
	return M;
}
Motorcycle* Region::getSMotor(STATUS_TYPE type)
{
	Motorcycle* M = MotorStatus[type].peek();
	MotorStatus[type].remove();
	return M;
}

void Region::setMotor(Motorcycle* M)
{
	Motor[M->GetType()].add(M);
}

int Region::getMotornum(MOTO_TYPE type)
{
	return Motor[type].Size();
}

Order* Region::getVIPOrder() 
{
	Order*O = VIPOrder.peek();
	VIPOrder.remove();
	return O;
}
Order* Region::getFrozenOrder() 
{
	Order* O;
	FrozenOrder.dequeue(O);
	return O;
}
Order* Region::getNormalOrder() 
{
	Order* O;
	NormalOrder.removeBegin(O);
	return O;
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
void Region::setSMotor(Motorcycle* M)
{
	MotorStatus[M->GetStatus()].add(M);
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
bool Region::SMotorsEmpty(STATUS_TYPE type) const
{
	return MotorStatus[type].isEmpty();
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

bool Region::MotorIsEmpty(MOTO_TYPE type) const
{
	return Motor[type].isEmpty();
}


bool Region::ArrivedMotors(int TimeStep) 
{
	bool Arrived = false;
	while(!SMotorsEmpty(ASSIGNED))
	{
		Motorcycle* M = MotorStatus[ASSIGNED].peek();
		if(M->GetArriveTime() <= TimeStep)
		{
			Arrived = true;
			MotorStatus[ASSIGNED].remove();
			M->SetArriveTime(-1);
			if(pRest->getTraffic())
			{
				srand(time(NULL));
				if(M->GetDamaged())
				{
					int Rest = rand() % 20 + 10;
					M->SetRestTime(Rest + TimeStep);
					M->SetStatus(DMGD);
					M->SetDamaged(false);
				}
				else
				{
					int Rest = rand() % 10 + 5;
					M->SetRestTime(Rest + TimeStep);
					M->SetStatus(STATUS_TYPE(REST_NRM + M->GetType()));
				}
				setSMotor(M);
			}
			else
				setMotor(M);
		}
		else
		{
			break;
		}
	}
	if(pRest->getTraffic())
	{
		for(int i = REST_NRM; i < STATUS_CNT; i++)
		{
			while(!SMotorsEmpty((STATUS_TYPE)i))
			{
				Motorcycle* M = MotorStatus[i].peek();
				if(M->GetRestTime() <= TimeStep)
				{
					Arrived = true;
					MotorStatus[i].remove();
					M->SetRestTime(-1);
					M->SetStatus(ASSIGNED);
					setMotor(M);
				}
				else
				{
					break;
				}
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
	return "Region " + name + ":    Motors -->  VIP: " + to_string(Motor[MOTO_VIP].Size()) 
			+ "    Frozen: " + to_string(Motor[MOTO_FROZ].Size()) 
			+ "    Normal: " + to_string(Motor[MOTO_NRM].Size())
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
