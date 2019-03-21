#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_


#include "..\Defs.h"

#pragma once
class Motorcycle	
{
	static int count;
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding motorcycle type 
	int speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	//region of the motorcycle
	STATUS	status;	//idle or in-service

public:
	Motorcycle();
	Motorcycle(ORD_TYPE type, int spd, REGION reg, STATUS);
	int GetID() const;
	void SetType(ORD_TYPE type);
	ORD_TYPE GetType() const;
	void SetSpeed(int spd);
	int GetSpeed() const;
	void SetRegion(REGION reg);
	REGION GetRegion() const;
	void SetStatus(STATUS st);
	STATUS GetStatus() const;
	virtual ~Motorcycle();
};

#endif