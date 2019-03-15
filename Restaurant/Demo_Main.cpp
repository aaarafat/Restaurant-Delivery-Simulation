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
	int x;
	cin >> x;
	while (x != -1)
	{
		Q.add(x);
		cin >> x;
	}
	Heap_PriorityQueue<int> Copy = Q;
	while (!Copy.isEmpty())
	{
		std::cout<< Copy.peek() << '\n';
		Copy.remove();
	}

	return 0;
}
