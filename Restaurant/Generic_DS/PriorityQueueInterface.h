#ifndef  _PRIORITY_QUEUE_INTERFACE
#define _PRIORITY_QUEUE_INTERFACE

template<class ItemType>
class PriorityQueueInterface
{
public:
	// sees whether the queue is empty
	virtual bool isEmpty() const = 0;

	// Adds new item to the queue
	virtual bool add(ItemType* Item) = 0;

	// Remove the item with the highest priority
	virtual bool remove() = 0;

	// Returns the Item with the highest priority
	virtual ItemType* peek() const = 0;
};
#endif _PRIORITY_QUEUE_INTERFACE