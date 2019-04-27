#include "Motorcycle.h"

int Motorcycle::count = 0;

Motorcycle::Motorcycle()
{
	count++;
	ID = count;
	ArriveTime = -1;
	RestTime = -1;
	RepairTime = -1;
}

Motorcycle::Motorcycle(ORD_TYPE type, int spd, REGION reg) :
	ID(++count), type(type), speed(spd), region(reg), ArriveTime(-1), RestTime(-1), RepairTime(-1)
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
int Motorcycle::GetRepairTime() const
{
	return RepairTime;
}
void Motorcycle::SetRepairTime(int rp)
{
	RepairTime = rp;
}
int Motorcycle::GetRestTime() const
{
	return RestTime;
}
void Motorcycle::SetRestTime(int rs)
{
	RestTime = rs;
}
void Motorcycle::SetRegion(REGION reg)
{
	region = reg;
}

REGION Motorcycle::GetRegion() const
{
	return region;
}
bool operator> (const Motorcycle& moto, const Motorcycle& moto2)
{
	try
	{
		if (moto.ArriveTime == -1 && moto2.ArriveTime == -1)
		{
			if (moto.RepairTime != -1 && moto2.RepairTime != -1)
			{
				return moto.RepairTime < moto2.RepairTime;
			}
			if (moto.RestTime == -1 && moto2.RestTime == -1)
			{
				return moto.speed > moto2.speed;
			}
			if (moto.RestTime != -1 && moto2.RestTime != -1)
			{
				if (moto.RestTime == moto2.RestTime) 
					return moto.speed > moto2.speed;
				return moto.RestTime < moto2.RestTime;
			}
		}
		else if (moto.ArriveTime != -1 && moto2.ArriveTime != -1)
		{
			if (moto.ArriveTime == moto2.ArriveTime)
			{
				return moto.speed > moto2.speed;
			}
			return moto.ArriveTime < moto2.ArriveTime;
		}
		else
		{
			std::string error = "Cannot Compare Ready Motorcycle with Unready Motorcycle  ";
			error += std::to_string(moto.ArriveTime);
			error += " and ";
			error += std::to_string(moto2.ArriveTime);
			std::cout << moto.GetRegion() << " " << moto.GetType()  << " " << moto.GetRepairTime()<< std::endl;
			std::cout << moto2.GetRegion() << " " << moto2.GetType() << " " << moto2.GetRepairTime()<< std::endl;
			throw std::exception(error.c_str());
		}
	}catch(std::exception& e)
	{
		std::cout << e.what() << '\n';
		//std::exit(0);
		throw e;
	}
	
}

bool operator< (const Motorcycle& moto, const Motorcycle& moto2)
{
	try
	{
		if (moto.ArriveTime == -1 && moto2.ArriveTime == -1)
		{
			if (moto.RepairTime != -1 && moto2.RepairTime != -1)
			{
				return moto.RepairTime > moto2.RepairTime;
			}
			if (moto.RestTime == -1 && moto2.RestTime == -1)
			{
				return moto.speed < moto2.speed;
			}
			if (moto.RestTime != -1 && moto2.RestTime != -1)
			{
				if (moto.RestTime == moto2.RestTime) 
					return moto.speed < moto2.speed;
				return moto.RestTime > moto2.RestTime;
			}
		}
		else if (moto.ArriveTime != -1 && moto2.ArriveTime != -1)
		{
			if (moto.ArriveTime == moto2.ArriveTime)
			{
				return moto.speed < moto2.speed;
			}
			return moto.ArriveTime > moto2.ArriveTime;
		}
		else
		{
			std::string error = "Cannot Compare Ready Motorcycle with Unready Motorcycle  ";
			error += std::to_string(moto.ArriveTime);
			error += " and ";
			error += std::to_string(moto2.ArriveTime);
			std::cout << moto.GetRegion() << " " << moto.GetType()  << " " << moto.GetRepairTime()<< std::endl;
			std::cout << moto2.GetRegion() << " " << moto2.GetType() << " " << moto2.GetRepairTime()<< std::endl;
			throw std::exception(error.c_str());
		}
	}catch(std::exception& e)
	{
		std::cout << e.what() << '\n';
		//std::exit(0);
		throw e;
	}
}

Motorcycle::~Motorcycle()
{

}
