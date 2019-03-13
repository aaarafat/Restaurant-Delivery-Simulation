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
	Q.Insert(1);
	Q.Insert(8);
	Q.Insert(3);
	int result = 0;
	Q.ExtractMax(result);
	std::cout << result << std::endl;
	Q.ExtractMax(result);
	std::cout << result << std::endl;
	Q.ExtractMax(result);
	std::cout << result << std::endl;
	Q.ExtractMax(result);
	std::cout << result << std::endl;
	Q.ChangePriority(1,100);
	Q.ExtractMax(result);
	std::cout << result << std::endl;
	Q.Insert(2);
	Q.Remove(2);
	return 0;
}
