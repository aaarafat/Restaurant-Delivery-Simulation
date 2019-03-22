#include "PromoEvent.h"


PromoEvent::PromoEvent(Restaurant* pR) : Event(pR)
{
}
void PromoEvent::ReadEvent(ifstream& fin)
{
	fin>>EventTime>>OrderID>>ExMon;
}
void PromoEvent::Execute()
{

}

PromoEvent::~PromoEvent(void)
{
}
