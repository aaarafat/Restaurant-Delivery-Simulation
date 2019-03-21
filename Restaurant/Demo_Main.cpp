//#include "Drawing.h"
#include "Rest\Restaurant.h"
#include "GUI\GUI.h"
#include "Generic_DS\Heap_PriorityQueue.h"
#include "Rest\Motorcycle.h"
#include <iostream>
#include "Generic_DS\LinkedList.h"
#define watch(x) std::cout<<(#x)<< " = " <<x<<'\n'
int main()
{
	/*
	Restaurant* pRest = new Restaurant;
	pRest->RunSimulation();
	
	delete pRest;
	*/
	//Priority Queue Test
	/*
	Heap_PriorityQueue<int> Q;
	int x;
	cin >> x;
	while (x != -1)
	{
		Q.add(x);
		watch(Q.Capcity());
		cin >> x;
	}
	Heap_PriorityQueue<int> Copy = Q;
	while (!Copy.isEmpty())
	{
		std::cout<< *Copy.peek() << '\n';
		Copy.remove();
		watch(Copy.Capcity());
	}
	/*cin >> x;
	while (x != -1)
	{
		Copy.add(x);
		cin >> x;
	}
	Q = Copy;
	while (!Q.isEmpty())
	{
		std::cout<< *Q.peek() << '\n';
		Q.remove();
	}
	*/
	LinkedList<int> l;
	/*Heap_PriorityQueue<Motorcycle> moto;
	int n;
	cin >> n;
	while (n != -1)
	{
		l.Add(n);
		cin >> n;
	}
	for (int i = 1; i <= 5; i++)
	{
		std::cout << l.getEntry(i) << '\n';
	}
		moto.add(Motorcycle(TYPE_VIP,n,A_REG,IDLE));
		cin >> n;
	}
	while (!moto.isEmpty())
	{
		cout << moto.peek()->GetSpeed() << '\n';
		moto.remove();
	}*/

	return 0;
}
