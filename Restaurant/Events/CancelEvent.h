#pragma once
#include "Event.h"
class Event;
class Restaurant;
class CancelEvent : public Event
{

public:
	CancelEvent(void);
	void ReadEvent(ifstream& fin);
	void Execute(Restaurant* pRest);
	~CancelEvent(void);
};

