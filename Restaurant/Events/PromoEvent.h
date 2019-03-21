#pragma once
#include "Event.h"
class Event;
class Restaurant;
class PromoEvent :	public Event
{
	int ExMon;
public:
	PromoEvent(void);
	void ReadEvent(ifstream& fin);
	void Execute(Restaurant* pRest);
	~PromoEvent(void);
};

