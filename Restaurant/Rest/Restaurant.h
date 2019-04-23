#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
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
	Heap_PriorityQueue<Order> FinishedOrders;
	string AssignedOrders;
	string AssignedOrderstemp;
	
	Region* Reg[REG_CNT];
	int AutoPromo;
	

public:
	
	Restaurant();
	~Restaurant();
	void AddEvent(Event* pE);	//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	bool ReadFile(string filename);
	Region* GetRegion(REGION x);
	bool CancelOrder(int id);
	bool PromoteOrder(int id,int money);
	void AutoPromote(int cTime);
	void ServingOrders(int cTime);
	//Simulation Functions
	void Simulation(bool SBS,bool S); //Testing for phase 1
	void Draw_All(); //drawing from the Draw Queue
	void SharingOrdersToDraw(); //Copy Orders to be Drawn
	void DeleteFirstDrawn(int region); //for test deletes the first in the queue
	void ArrivedMotors(int CurrentTimeStep); //Add Arrived Motors to the Restaurant Motors
	bool ActiveOrdersExist(); // returns true if active orders exist 
	bool AssignedMotorsExist(); // returns true if assigned motor exist 
	void AssignOrder(int TimeStep);
	void PrintOutputFile(string file);
	void Draw(int CurrentTimeStep);
};

#endif