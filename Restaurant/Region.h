#pragma once
#include "Rest\Motorcycle.h"
#include "Generic_DS\Heap_PriorityQueue.h"
#include "Rest\Order.h"
class Region
{
	Heap_PriorityQueue<Motorcycle> VIPMotor;
	Heap_PriorityQueue<Motorcycle> FrozenMotor;
	Heap_PriorityQueue<Motorcycle> NormalMotor;
	//Heap_PriorityQueue<Order> VIPOrder;
	//List of normal orders to search
	//list of frozen orders to search
	
public:
	Motorcycle* getVIPMotor() const;
	void setVIPMotor(Motorcycle* M);
	Motorcycle* getNormalMotor() const;
	void setNormalMotor(Motorcycle* M);
	Motorcycle* getFrozenMotor() const;
	void setFrozenMotor(Motorcycle* M);
	//Order* getVIPOrder() const;
	//void setVIPOrder(const Order& O);
	//seter and getter for both the list
	//search functions for the cancelation and Prompotion 

	
	Region();
	~Region();
};

