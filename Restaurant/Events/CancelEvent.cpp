#include "CancelEvent.h"


CancelEvent::CancelEvent(void)
{
}

void CancelEvent::ReadEvent(ifstream& fin)
{
	fin>>EventTime>>OrderID;
}
void CancelEvent::Execute(Restaurant* pRest)
{

}

CancelEvent::~CancelEvent(void)
{
}
