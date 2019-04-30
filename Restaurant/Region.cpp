#include "Region.h"
#include <string>
int Region::cnt = 0;
Region::Region()
{
	name = 'A' + cnt;
	cnt++;
}
Motorcycle* Region::getMotor(MOTO_TYPE type)
{
	Motorcycle* M = Motor[type].peek();
	Motor[type].remove();
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
bool Region::MotorIsEmpty(MOTO_TYPE type) const
{
	return Motor[type].isEmpty();
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
			setMotor(AssignedMotor);
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
	return "Region " + name + ":    Motors -->  VIP: " + to_string(Motor[MOTO_VIP].Size()) + "    Frozen: " + to_string(Motor[MOTO_FROZ].Size()) + "    Normal: " + to_string(Motor[MOTO_NRM].Size())
			+ "                                                                          Orders -->  VIP: "
			+ to_string(VIPOrder.Size()) + "    Frozen: " + to_string(FrozenOrder.Size()) + "    Normal: " + to_string(NormalOrder.Size());
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
