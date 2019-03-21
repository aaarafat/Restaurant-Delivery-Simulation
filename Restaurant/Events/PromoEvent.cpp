#include "PromoEvent.h"


PromoEvent::PromoEvent(void)
{
}
void PromoEvent::ReadEvent(ifstream& fin)
{
	fin>>EventTime>>OrderID>>ExMon;
}
void PromoEvent::Execute(Restaurant* pRest)
{

}

PromoEvent::~PromoEvent(void)
{
}
