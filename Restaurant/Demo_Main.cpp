//#include "Drawing.h"
#include "Rest\Restaurant.h"
#include "GUI\GUI.h"
#include "Generic_DS\PriorityQueueADT.h"
#include <iostream>
int main()
{
	
	//Restaurant* pRest = new Restaurant;
	//pRest->RunSimulation();
	
	//delete pRest;
	PriortyQueueADT<int,100> Q;
	Q.Insert(2);
	Q.Insert(3);
	int result = 0;
	Q.ExtractMax(result);
	std::cout << result << std::endl;

	return 0;
}
