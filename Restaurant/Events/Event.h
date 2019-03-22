#ifndef __EVENT_H_
#define __EVENT_H_
#include <fstream>
#include "..\Defs.h"
using namespace std;
class Restaurant;	//Forward declation
//The base class for all possible events in the system (abstract class)
class Event
{
protected:
	int EventTime;	//Timestep when this event takes place
	int OrderID;	//each event is related to certain order
	Restaurant* pRest;
public:
	Event(int eTime, int ordID, Restaurant* pR);
	Event(Restaurant* pR);
	int getEventTime();
	int getOrderID();
	virtual void ReadEvent(ifstream& fin) = 0;
	virtual ~Event();


	virtual void Execute()=0;	////a pointer to "Restaurant" and events need it to execute

};


#endif