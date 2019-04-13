#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg, Restaurant* pR): Event(eTime, oID, pR)
{
	OrdType = oType;
	OrdRegion = reg;
}
ArrivalEvent::ArrivalEvent(Restaurant* pR) : Event(pR)
{
}

void ArrivalEvent::Execute()
{
	//This function should create an order and fills its data 
	// Then adds it to normal, frozen, or VIP order lists that you will create in phase1
	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phase 1&2
	Order* pOrd = new Order(OrderID,OrdType,OrdRegion,OrdDistance,OrdMoney,EventTime);
	Region* R = pRest->GetRegion(OrdRegion);
	if (OrdType == TYPE_NRM)
	{
		R->setNormalOrder(pOrd);
	}
	else if (OrdType == TYPE_VIP)
	{
		R->setVIPOrder(pOrd);
	}
	else if (OrdType == TYPE_FROZ)
	{
		R->setFrozenOrder(pOrd);
	}

}
void ArrivalEvent::ReadEvent(ifstream& fin)
{
	char oType, reg;
	fin>>EventTime>>oType>>OrderID>>OrdDistance>>OrdMoney>>reg;
	switch (oType)
	{
	case 'N': OrdType = TYPE_NRM; break;
	case 'V': OrdType = TYPE_VIP; break;
	case 'F': OrdType = TYPE_FROZ; break;
	}
	switch (reg)
	{
	case 'A': OrdRegion = A_REG; break;
	case 'B': OrdRegion = B_REG; break;
	case 'C': OrdRegion = C_REG; break;
	case 'D': OrdRegion = D_REG; break;
	}
	OrdReg = pRest->GetRegion(OrdRegion);

}
