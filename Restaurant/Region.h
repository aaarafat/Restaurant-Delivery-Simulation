#pragma once
#include "Generic_DS\LinkedList.h"
#include "Generic_DS\Heap_PriorityQueue.h"
#include "Rest\Motorcycle.h"
#include "Rest\Order.h"
#include <iostream>
using namespace std;
class Region
{
	Heap_PriorityQueue<Motorcycle> VIPMotor;
	Heap_PriorityQueue<Motorcycle> FrozenMotor;
	Heap_PriorityQueue<Motorcycle> NormalMotor;
	Heap_PriorityQueue<Order> VIPOrder;
	LinkedList<Order*> FrozenOrder;
	LinkedList<Order*> NormalOrder;
	int NormOrd;
	int FrozOrd;
	int VIPOrd;
	int NormMoto;
	int VIPMoto;
	int FrozMoto;

	
public:
	Motorcycle* getVIPMotor() ;
	void setVIPMotor(Motorcycle* M);
	Motorcycle* getNormalMotor() ;
	void setNormalMotor(Motorcycle* M);
	Motorcycle* getFrozenMotor() ;
	void setFrozenMotor(Motorcycle* M);
	Order* getVIPOrder() ;
	void setVIPOrder(Order* O);
	Order* getFrozenOrder();
	void setFrozenOrder(Order* O);
	Order* getNormalOrder();
	void setNormalOrder(Order* O);
	//seter and getter for both the list
	//search functions for the cancelation and Prompotion 
	bool VIPOrderIsEmpty();
	bool NormalOrderIsEmpty();
	bool FrozenOrderIsEmpty();
	bool CancelOrder(int id);
	Region();
	~Region();
};

