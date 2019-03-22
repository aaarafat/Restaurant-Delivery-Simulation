#include "CancelEvent.h"


CancelEvent::CancelEvent(Restaurant* pR) : Event(pR)
{
}

void CancelEvent::ReadEvent(ifstream& fin)
{
	fin>>EventTime>>OrderID;
}
void CancelEvent::Execute()
{

}

CancelEvent::~CancelEvent(void)
{
}
