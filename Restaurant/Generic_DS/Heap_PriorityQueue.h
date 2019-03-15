#ifndef _HEAP_PRIORITY_QUEUE 
#define _HEAP_PRIORITY_QUEUE
#include "ArrayMaxHeap.h"
#include "PriorityQueueInterface.h"

template<class ItemType>
class Heap_PriorityQueue :
	public PriorityQueueInterface<ItemType>,
	private ArrayMaxHeap<ItemType> 
{
public:
	Heap_PriorityQueue();
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
bool Heap_PriorityQueue<ItemType>::isEmpty() const
{
	return ArrayMaxHeap<ItemType>::isEmpty();
}

template<class ItemType>
bool Heap_PriorityQueue<ItemType>::add(const ItemType& Item)
{
	ArrayMaxHeap<ItemType>::add(Item);
}

template<class ItemType>
bool Heap_PriorityQueue<ItemType>::remove()
{
	ArrayMaxHeap<ItemType>::remove();
}

template<class ItemType>
ItemType Heap_PriorityQueue<ItemType>::peek() const
{
	return ArrayMaxHeap<ItemType>::peekTop();
}

#endif _HEAP_PRIORITY_QUEUE