#include "Event.h"


Event::Event(int eTime, int ordID, Restaurant* pR)
{
	pRest = pR;
	EventTime = eTime;
	OrderID	= ordID;
}
Event::Event(Restaurant* pR) : pRest(pR)
{
}


int Event::getEventTime()
{
	return EventTime;
}
int Event::getOrderID()
{
	return OrderID;
}



Event::~Event()
{

}

