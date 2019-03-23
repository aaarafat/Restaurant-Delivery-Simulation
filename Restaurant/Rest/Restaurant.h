#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\CancelEvent.h"
#include "..\Events\PromoEvent.h"
#include "Order.h"
#include "..\Region.h"
using namespace std;
// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file

	
	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	
	/// ==>
	
	//
	// TODO: Add More Data Members As Needed
	Region* Reg[REG_CNT];
	int AutoPromo;
	LinkedList<Order*> DrawOrders;

public:
	
	Restaurant();
	~Restaurant();
	void AddEvent(Event* pE);	//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	/// ==> 
	///  DEMO-related functions. Should be removed in phases 1&2
	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue
	Order* getDemoOrder();			//return the front order from demo queue
	/// ==> 

	bool ReadFile(string filename);
	Region* GetRegion(REGION x);
	bool CancelOrder(int id);
	//
	// TODO: Add More Member Functions As Needed
	//
	//Simulation Functions
	void Interactive_Simulation(); //Steps on mouse clicks
	void StepByStep_Simulation(); //Steps every Second
	void Silent_Simulation();     //Doesn't generate a GUI 
	void Test_Simulation(); //Testing for phase 1
	void Test_Draw_All(); //testing drawing from the queues
	void setDrawOrder(Order *O);
	Order* getDrawOrder();
};

#endif