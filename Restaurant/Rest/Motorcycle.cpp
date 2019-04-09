#include "Motorcycle.h"

int Motorcycle::count = 0;

Motorcycle::Motorcycle()
{
	count++;
	ID = count;
	ArriveTime = -1;
}

Motorcycle::Motorcycle(ORD_TYPE type, int spd, REGION reg, STATUS st) :
	ID(++count), type(type), speed(spd), region(reg), status(st), ArriveTime(-1)
{
}

int Motorcycle::GetID() const
{
	return ID;
}

void Motorcycle::SetArriveTime(int ArriveTime)
{
	this->ArriveTime = ArriveTime;
}

int Motorcycle::GetArriveTime() const
{
	return ArriveTime;
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
	try
	{
		if (moto.ArriveTime == -1 && moto2.ArriveTime == -1)
		{
			return moto.speed > moto2.speed;
		}
		else if (moto.ArriveTime != -1 && moto2.ArriveTime != -1)
		{
			return moto.ArriveTime < moto2.ArriveTime;
		}
		else
		{
			throw std::exception("Cannot Compare Ready Motorcycle with Unready Motorcycle");
		}
	}catch(std::exception& e)
	{
		std::cout << e.what() << '\n';
		std::exit(0);
	}
	
}

bool operator< (const Motorcycle& moto, const Motorcycle& moto2)
{
	try
	{
		if (moto.ArriveTime == -1 && moto2.ArriveTime == -1)
		{
			return moto.speed < moto2.speed;
		}
		else if (moto.ArriveTime != -1 && moto2.ArriveTime != -1)
		{
			return moto.ArriveTime > moto2.ArriveTime;
		}
		else
		{
			throw std::exception("Cannot Compare Ready Motorcycle with Unready Motorcycle");
		}
	}catch(std::exception& e)
	{
		std::cout << e.what() << '\n';
		std::exit(0);
	}
}

Motorcycle::~Motorcycle()
{

}
