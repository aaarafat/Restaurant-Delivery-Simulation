#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, REGION r_region,int Dist,int TotalMon,int ArrTim)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	Region = r_region;	
	Distance=Dist;
	totalMoney=TotalMon;
	ArrTime=ArrTim;
}


Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


int Order::GetType() const
{
	return type;
}

int Order::getArrTime() const
{
	return ArrTime;
}
void Order::toVIP(int money)
{
	type = TYPE_VIP;
	totalMoney += money;
}

REGION Order::GetRegion() const
{
	return Region;
}

void Order::SetDistance(int d)
{
	Distance = d>0?d:0; // d pos or zero
}

int Order::GetDistance() const
{
	return Distance;
}
double Order::Priorty() const
{
	return (double(Distance)/ArrTime)+(double(totalMoney)/Distance);
}
bool Order::operator< (const Order& o)
{
	return Priorty()<o.Priorty();
}

bool Order::operator> (const Order& o)
{
	return Priorty()>o.Priorty();
}
bool Order::operator== (int id)
{
	return GetID() == id;
}