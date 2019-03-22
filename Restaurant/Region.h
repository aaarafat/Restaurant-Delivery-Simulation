#pragma once
#include "Generic_DS\LinkedList.h"
#include "Generic_DS\Heap_PriorityQueue.h"
#include "Rest\Motorcycle.h"
#include "Rest\Order.h"
class Region
{
	Heap_PriorityQueue<Motorcycle> VIPMotor;
	Heap_PriorityQueue<Motorcycle> FrozenMotor;
	Heap_PriorityQueue<Motorcycle> NormalMotor;
	Heap_PriorityQueue<Order> VIPOrder;
	LinkedList<Order*> FrozenOrder;
	LinkedList<Order*> NormalOrder;

	
public:
	Motorcycle* getVIPMotor() const;
	void setVIPMotor(Motorcycle* M);
	Motorcycle* getNormalMotor() const;
	void setNormalMotor(Motorcycle* M);
	Motorcycle* getFrozenMotor() const;
	void setFrozenMotor(Motorcycle* M);
	Order* getVIPOrder() const;
	void setVIPOrder(Order* O);
	Order* getFrozenOrder() const;
	void setFrozenOrder(Order* O);
	Order* getNormalOrder() const;
	void setNormalOrder(Order* O);
	//seter and getter for both the list
	//search functions for the cancelation and Prompotion 

	
	Region();
	~Region();
};

