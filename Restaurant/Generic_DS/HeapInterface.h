#ifndef _HEAP_INTERFACE
#define _HEAP_INTERFACE
template<class T>
class HeapInterface
{
public:
	// sees whether the heap is empty
	virtual bool isEmpty() const = 0;

	// Gets the number of nodes
	virtual int getNumberOfNodes() const = 0;
	
	// Gets the Height of the heap
	virtual int getHeight() const = 0;
	
	// Gets the data that is in the root (top) of this heap
	virtual T* peekTop() const = 0;

	// Adds new node to the heap
	virtual bool add(const T& Item) = 0;

	// Remove the root (top) node
	virtual bool remove() = 0;

	// Removes all nodes from the heap
	virtual void clear() = 0;
};
#endif _HEAP_INTERFACE