#ifndef _HEAP_PRIORITY_QUEUE 
#define _HEAP_PRIORITY_QUEUE
#include "ArrayMaxHeap.h"
#include "PriorityQueueInterface.h"

template<class ItemType>
class Heap_PriorityQueue :
	public PriorityQueueInterface<ItemType>,
	public ArrayMaxHeap<ItemType> 
{
public:
	Heap_PriorityQueue();
	Heap_PriorityQueue(const Heap_PriorityQueue<ItemType>& PriorityQueue);
	bool isEmpty() const;
	bool add(const ItemType& Item);
	bool remove();
	ItemType peek() const;
};

template<class ItemType>
Heap_PriorityQueue<ItemType>::Heap_PriorityQueue()
{
	ArrayMaxHeap<ItemType>();
}

template<class ItemType>
Heap_PriorityQueue<ItemType>::Heap_PriorityQueue(const Heap_PriorityQueue<ItemType>& PriorityQueue) : 
	ArrayMaxHeap<ItemType>(PriorityQueue)
{
	
}

template<class ItemType>
bool Heap_PriorityQueue<ItemType>::isEmpty() const
{
	return ArrayMaxHeap<ItemType>::isEmpty();
}

template<class ItemType>
bool Heap_PriorityQueue<ItemType>::add(const ItemType& Item)
{
	return ArrayMaxHeap<ItemType>::add(Item);
}

template<class ItemType>
bool Heap_PriorityQueue<ItemType>::remove()
{
	return ArrayMaxHeap<ItemType>::remove();
}

template<class ItemType>
ItemType Heap_PriorityQueue<ItemType>::peek() const
{
	return ArrayMaxHeap<ItemType>::peekTop();
}

#endif _HEAP_PRIORITY_QUEUE