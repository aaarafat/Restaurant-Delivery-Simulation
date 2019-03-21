#include "Motorcycle.h"

int Motorcycle::count = 0;

Motorcycle::Motorcycle()
{
	count++;
	ID = count;
}

Motorcycle::Motorcycle(ORD_TYPE type, int spd, REGION reg, STATUS st) :
	ID(++count), type(type), speed(spd), region(reg), status(st)
{
}

int Motorcycle::GetID() const
{
	return ID;
}

void Motorcycle::SetType(ORD_TYPE type)
{
	type = this->type;
}

ORD_TYPE Motorcycle::GetType() const
{
	return type;
}

void Motorcycle::SetSpeed(int spd)
{
	if (speed > 0)
	{
		speed = spd;
	}
}

int Motorcycle::GetSpeed() const
{
	return speed;
}

void Motorcycle::SetRegion(REGION reg)
{
	region = reg;
}

REGION Motorcycle::GetRegion() const
{
	return region;
}

void Motorcycle::SetStatus(STATUS st)
{
	status = st;
}

STATUS Motorcycle::GetStatus() const
{
	return status;
}

bool operator> (const Motorcycle& moto, const Motorcycle& moto2)
{
	return moto.speed > moto2.speed;
}

bool operator< (const Motorcycle& moto, const Motorcycle& moto2)
{
	return moto.speed < moto2.speed;
}

Motorcycle::~Motorcycle()
{

}
