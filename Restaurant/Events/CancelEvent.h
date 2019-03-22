#pragma once
#include "Event.h"
class Event;
class Restaurant;
class CancelEvent : public Event
{

public:
	CancelEvent(Restaurant* pR);
	void ReadEvent(ifstream& fin);
	void Execute();
	~CancelEvent(void);
};

