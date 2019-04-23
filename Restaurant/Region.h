#pragma once
#include "Generic_DS\LinkedList.h"
#include "Generic_DS\Heap_PriorityQueue.h"
#include "Generic_DS\Queue.h"
#include "Rest\Motorcycle.h"
#include "Rest\Order.h"
#include <iostream>
using namespace std;
class Region
{
	static int cnt;
	string name;
	Heap_PriorityQueue<Motorcycle> VIPMotor;
	Heap_PriorityQueue<Motorcycle> FrozenMotor;
	Heap_PriorityQueue<Motorcycle> NormalMotor;
	Heap_PriorityQueue<Order> VIPOrder;
	Queue<Order*> FrozenOrder;
	LinkedList<Order*> NormalOrder;
	Heap_PriorityQueue<Motorcycle> AssignedMotors;
	Queue<Order*> DrawOrders;
	Queue<Order*> NormalServed;
	Queue<Order*> VIPServed;
	Queue<Order*> FrozenServed;
	Heap_PriorityQueue<Order> AssignedOrder;
	Heap_PriorityQueue<Motorcycle> DamagedMotors;
public:
	Motorcycle* getVIPMotor() ;
	void setVIPMotor(Motorcycle* M);
	int getVIPMotornum();
	Motorcycle* getNormalMotor() ;
	void setNormalMotor(Motorcycle* M);
	int getNormalMotornum();
	Motorcycle* getFrozenMotor() ;
	void setFrozenMotor(Motorcycle* M);
	int getFrozenMotornum();
	Order* getVIPOrder() ;
	void setVIPOrder(Order* O);
	Order* getFrozenOrder() ;
	void setFrozenOrder(Order* O);
	Order* getNormalOrder() ;
	void setNormalOrder(Order* O);
	Order* getVIPServed() ;
	void setVIPServed(Order* O);
	Order* getFrozenServed() ;
	void setFrozenServed(Order* O);
	Order* getNormalServed() ;
	void setAssignedOrder(Order* O);
	Order* getAssignedOrder();
	void setNormalServed(Order* O);
	void setAssignedMotor(Motorcycle* M);
	//seter and getter for both the list
	//search functions for the cancelation and Prompotion 
	bool VIPOrderIsEmpty() const;
	bool NormalOrderIsEmpty() const;
	bool FrozenOrderIsEmpty() const;
	bool VIPMotorIsEmpty() const;
	bool FrozenMotorIsEmpty() const;
	bool NormalMotorIsEmpty() const;
	bool AssignedMotorsEmpty() const;
	bool DamagedMotorsEmpty() const;
	bool ArrivedMotors(int TimeStep);
	bool CancelOrder(int id);
	bool PromoteOrder(int id,int money=0);
	void AutoPromote(int cTime,int pTime);
	void ServingOrders(int cTime);
	//DrawFunctions
	Order* getVIPDraw(Order* O) ;
	void setVIPDraw(Order* O);
	Order* getFrozenDraw(Order* O) ;
	void setFrozenDraw(Order* O);
	Order* getDrawOrders(Order* O) ;
	void setDrawOrders(Order* O);
	bool VIPDrawIsEmpty() const;
	bool DrawOrdersIsEmpty() const;
	bool FrozenDrawIsEmpty() const;
	void SharingOrderstoDraw();
	///////////////////////////////
	string Print();

	Region();
	~Region();
};

