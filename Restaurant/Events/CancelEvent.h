#pragma once
#include "Event.h"
class Restaurant;
class Region;
class CancelEvent : public Event
{

public:
	CancelEvent(Restaurant* pR);
	void ReadEvent(ifstream& fin);
	void Execute();
	~CancelEvent(void);
};

