//#include "Drawing.h"
#include "Rest\Restaurant.h"
#include "GUI\GUI.h"
#include "Generic_DS\ArrayMaxHeap.h"
#include <iostream>
int main()
{
	/*	
	Restaurant* pRest = new Restaurant;
	pRest->RunSimulation();
	
	delete pRest;
	*/
	ArrayMaxHeap<int> heap;
	int x;
	cin >> x;
	while (x != -1)
	{
		heap.add(x);
		cin >> x;
	}
	while (true)
	{
		std::cout << heap.peekTop() << '\n';
		heap.remove();
	}

	return 0;
}
