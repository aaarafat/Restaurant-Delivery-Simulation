#ifndef _HEAP_PRIORITY_QUEUE 
#define _HEAP_PRIORITY_QUEUE
#include "ArrayMaxHeap.h"
#include "PriorityQueueInterface.h"

template<class ItemType>
class Heap_PriorityQueue :
	public PriorityQueueInterface<ItemType>,
	private ArrayMaxHeap<ItemType>   // duplicated functions (private)
{
public:
	Heap_PriorityQueue();
	bool isEmpty() const;
	bool add(const ItemType& Item);
	bool remove();
	ItemType peek() const;

private:

};

template<class ItemType>
Heap_PriorityQueue<ItemType>::Heap_PriorityQueue()
{
}

template<class ItemType>
Heap_PriorityQueue<ItemType>::~Heap_PriorityQueue()
{
}

template<class ItemType>
bool Heap_PriorityQueue<ItemType>::isEmpty() const
{

}

template<class ItemType>
bool Heap_PriorityQueue<ItemType>::add(const ItemType& Item)
{

}

template<class ItemType>
bool Heap_PriorityQueue<ItemType>::remove()
{

}

template<class ItemType>
ItemType Heap_PriorityQueue<ItemType>::peek() const
{

}

#endif _HEAP_PRIORITY_QUEUE