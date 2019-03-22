#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_

#include "Event.h"
class Restaurant;
class Region;

//class for the arrival event
class ArrivalEvent: public Event
{
	//info about the order ralted to arrival event
	int OrdDistance;	//order distance
	ORD_TYPE OrdType;		//order type: Normal, Frozen, VIP
	REGION OrdRegion;  //Region of this order	                
	double OrdMoney;	//Total order money
	Region* OrdReg;
public:
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg, Restaurant* pR);
	ArrivalEvent(Restaurant* pR);
	//Add more constructors if needed
	void ReadEvent(ifstream& fin);
	virtual void Execute();	//override execute function

};

#endif