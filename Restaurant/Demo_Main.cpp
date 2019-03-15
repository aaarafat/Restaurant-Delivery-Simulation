//#include "Drawing.h"
#include "Rest\Restaurant.h"
#include "GUI\GUI.h"
#include "Generic_DS\Heap_PriorityQueue.h"
#include <iostream>
int main()
{
	/*	
	Restaurant* pRest = new Restaurant;
	pRest->RunSimulation();
	
	delete pRest;
	*/
	Heap_PriorityQueue<int> Q;
	Q.add(2);
	Q.add(3);
	Q.add(5);
	Q.add(6);
	Q.add(2);
	Q.add(1);
	Q.add(9);
	Heap_PriorityQueue<int> Copy = Q;
	while (!Copy.isEmpty())
	{
		std::cout<< Copy.peek() << '\n';
		Copy.remove();
	}

	return 0;
}
