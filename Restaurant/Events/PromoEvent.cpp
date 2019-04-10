#include "PromoEvent.h"
#include "..\Rest\Restaurant.h"

PromoEvent::PromoEvent(Restaurant* pR) : Event(pR)
{
}
void PromoEvent::ReadEvent(ifstream& fin)
{
	fin>>EventTime>>OrderID>>ExMon;
}
void PromoEvent::Execute()
{
	pRest->PromoteOrder(OrderID,ExMon);
}

PromoEvent::~PromoEvent(void)
{
}
