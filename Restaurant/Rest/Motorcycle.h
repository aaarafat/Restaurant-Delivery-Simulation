#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_

#include <string>
#include "..\Defs.h"
#include <exception>
#include <cstdlib>
#include <iostream>

#pragma once
class Motorcycle	
{
	static int count;
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding motorcycle type 
	int speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	//region of the motorcycle
	int ArriveTime; //arrive time of the motorcycle
	int RepairTime; //Number of steps to repaire the motorcycle
	int RestTime;   //Number of steps that motor needs to rest
public:
	Motorcycle();
	Motorcycle(ORD_TYPE type, int spd, REGION reg);
	int GetID() const;
	void SetType(ORD_TYPE type);
	void SetArriveTime(int ArriveTime);
	int GetArriveTime() const;
	ORD_TYPE GetType() const;
	void SetSpeed(int spd);
	int GetSpeed() const;
	int GetRepairTime() const;
	void SetRepairTime(int rp);
	int GetRestTime() const;
	void SetRestTime(int rs);
	void SetRegion(REGION reg);
	REGION GetRegion() const;
	friend bool operator> (const Motorcycle& moto, const Motorcycle& moto2);
	friend bool operator< (const Motorcycle& moto, const Motorcycle& moto2);
	virtual ~Motorcycle();
};

#endif