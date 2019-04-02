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
	LinkedList<Order*> FrozenOrder;
	LinkedList<Order*> NormalOrder;
	Queue<Order*> DrawOrders;
	
public:
	Motorcycle* getVIPMotor() ;
	void setVIPMotor(Motorcycle* M);
	Motorcycle* getNormalMotor() ;
	void setNormalMotor(Motorcycle* M);
	Motorcycle* getFrozenMotor() ;
	void setFrozenMotor(Motorcycle* M);
	Order* getVIPOrder() ;
	void setVIPOrder(Order* O);
	bool getFrozenOrder();
	void setFrozenOrder(Order* O);
	bool getNormalOrder();
	void setNormalOrder(Order* O);
	//seter and getter for both the list
	//search functions for the cancelation and Prompotion 
	bool VIPOrderIsEmpty();
	bool NormalOrderIsEmpty();
	bool FrozenOrderIsEmpty();
	bool CancelOrder(int id);
	//DrawFunctions
	Order* getVIPDraw(Order* O) ;
	void setVIPDraw(Order* O);
	Order* getFrozenDraw(Order* O);
	void setFrozenDraw(Order* O);
	Order* getDrawOrders(Order* O);
	void setDrawOrders(Order* O);
	bool VIPDrawIsEmpty();
	bool DrawOrdersIsEmpty();
	bool FrozenDrawIsEmpty();
	void CopyOrderstoDraw();
	///////////////////////////////
	string Print();

	Region();
	~Region();
};

