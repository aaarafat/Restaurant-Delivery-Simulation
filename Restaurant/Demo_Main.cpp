//#include "Drawing.h"
#include "Rest\Restaurant.h"
#include "GUI\GUI.h"
#include "Generic_DS\Heap_PriorityQueue.h"
#include "Rest\Motorcycle.h"
#include <iostream>
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
	/*Heap_PriorityQueue<Motorcycle> moto;
	int n;
	cin >> n;
	while (n != -1)
	{
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
