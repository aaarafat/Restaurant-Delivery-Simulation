#include "Event.h"


Event::Event(int eTime, int ordID)
{
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

