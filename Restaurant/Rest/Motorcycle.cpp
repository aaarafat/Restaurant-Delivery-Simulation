#include "Motorcycle.h"

int Motorcycle::count = 0;

Motorcycle::Motorcycle()
{
	count++;
	ID = count;
	ArriveTime = -1;
	RestTime = -1;
	status = ASSIGNED;
	Damaged = false;
}

Motorcycle::Motorcycle(MOTO_TYPE type, int spd, REGION reg) :
	ID(++count), type(type), speed(spd), region(reg), ArriveTime(-1)
{
	RestTime = -1;
	status = ASSIGNED;
	Damaged = false;
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
void Motorcycle::SetRestTime(int RestTime)
{
	this->RestTime = RestTime;
}

int Motorcycle::GetRestTime() const
{
	return RestTime;
}
void Motorcycle::SetType(MOTO_TYPE type)
{
	type = this->type;
}

MOTO_TYPE Motorcycle::GetType() const
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
void Motorcycle::SetStatus(STATUS_TYPE st)
{
	status = st;
}

STATUS_TYPE Motorcycle::GetStatus() const
{
	return status;
}
void Motorcycle::SetDamaged(bool dmg)
{
	Damaged = dmg;
}
bool Motorcycle::GetDamaged() const
{
	return Damaged;
}
bool operator> (const Motorcycle& moto, const Motorcycle& moto2)
{
	try
	{
		if (moto.ArriveTime == -1 && moto2.ArriveTime == -1 && moto.RestTime == -1 && moto2.RestTime == -1) //Ready to service motors
		{
			return moto.speed > moto2.speed;
		}
		else if (moto.ArriveTime != -1 && moto2.ArriveTime != -1) //Assigned Motors
		{
			return moto.ArriveTime < moto2.ArriveTime;
		}
		else if(moto.ArriveTime == -1 && moto2.ArriveTime == -1 && moto.RestTime != -1 && moto2.RestTime != -1)
		{
			return moto.RestTime < moto2.RestTime;
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
