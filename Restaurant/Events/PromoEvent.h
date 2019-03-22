#pragma once
#include "Event.h"
class Event;
class Restaurant;
class PromoEvent :	public Event
{
	int ExMon;
public:
	PromoEvent(Restaurant* pR);
	void ReadEvent(ifstream& fin);
	void Execute();
	~PromoEvent(void);
};

