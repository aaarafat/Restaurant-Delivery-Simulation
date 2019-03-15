#ifndef _ARRAY_MAX_HEAP
#define _ARRAY_MAX_HEAP
#include "HeapInterface.h"
#include <functional> // std::bad_function_call

template<class T>
class ArrayMaxHeap : public HeapInterface
{
	static const int DEFAULT_CAPACITY = 15;
	T* items; // Array of heap items
	int Count; // Current count of heap items
	int maxItems; // Maximum capacity of the heap

	/* /////////////////////////
			Utility Functions
	*///////////////////////////

	// Gets the array index of the left child node
	int LeftChild(int nodeIndex) const;

	// Gets the array index of the right child node
	int RightChild(int nodeIndex) const;

	// Gets the array index of the parent node
	int Parent(int nodeIndex) const;

	// sees whether this node is a leaf
	bool isLeaf(int nodeIndex) const;

	// Converts a semiheap to a heap.
	void heapRebuild( int subTreeRootIndex);

	// Creates a heap from an unordered array.
	void heapCreate();
	////////////////////////////
public:
	ArrayMaxHeap();
	ArrayMaxHeap(const T Array[], const int Size);
	ArrayMaxHeap(const ArrayMaxHeap<T>& Array); // Copy constructor
	virtual ~ArrayMaxHeap();

	/* /////////////////////////
			Methods
	*///////////////////////////

	// sees whether the heap is empty
	bool isEmpty() const;

	// Gets the number of nodes
	int getNumberOfNodes() const;

	// Gets the Height of the heap
	int getHeight() const;

	// Gets the data that is in the root (top) of this heap
	T peekTop() const;

	// Adds new node to the heap
	bool add(const T& newData);

	// Remove the root (top) node
	bool remove();

	// Removes all nodes from the heap
	void clear();
};
// Gets the array index of the left child node
template<class T>
int ArrayMaxHeap<T>::LeftChild(int nodeIndex) const
{
	return 2 * nodeIndex;
}

// Gets the array index of the right child node
template<class T>
int ArrayMaxHeap<T>::RightChild(int nodeIndex) const
{
	return 2 * nodeIndex + 1;
}

// Gets the array index of the parent node
template<class T>
int ArrayMaxHeap<T>::Parent(int nodeIndex) const
{
	return nodeIndex / 2;
}

// sees whether this node is a leaf
template<class T>
bool ArrayMaxHeap<T>::isLeaf(int nodeIndex) const
{
	return LeftChild(nodeIndex) > Count && RightChild(nodeIndex) > Count;
}

// Creates a heap from an unordered array.
template<class T>
void ArrayMaxHeap<T>::heapCreate()
{

}

template<class T>
ArrayMaxHeap<T>::ArrayMaxHeap() :
	Count(0), maxItems(DEFAULT_CAPACITY)
{
	items = new T [DEFAULT_CAPACITY];	
}
template<class T>
ArrayMaxHeap<T>::ArrayMaxHeap(const T Array[], const int Size) : 
	Count(Size), maxItems(2 * Size)
{
	items = new T [maxItems];

	// Copy
	for (int i = 0; i < Size; i++)
	{
		items[i] = Array[i];
	}

	// Create the heap from the unordered items array
	heapCreate();
}
template<class T>
ArrayMaxHeap<T>::ArrayMaxHeap(const ArrayMaxHeap<T>& Array) // Copy constructor
{
	this->clear();
	Count = Array.Count;
	maxItems = Array.maxItems;

	items = new T [maxItems];

	// Copy
	for (int i = 0; i < Size; i++)
	{
		items[i] = Array.items[i];
	}
}
template<class T>
virtual ArrayMaxHeap<T>::~ArrayMaxHeap()
{
	this->clear();
}

// sees whether the heap is empty
template<class T>
bool ArrayMaxHeap<T>::isEmpty() const;
// Gets the number of nodes
template<class T>
int ArrayMaxHeap<T>::getNumberOfNodes() const;
// Gets the Height of the heap
template<class T>
int ArrayMaxHeap<T>::getHeight() const;
// Gets the data that is in the root (top) of this heap
template<class T>
T ArrayMaxHeap<T>::peekTop() const;
// Adds new node to the heap
template<class T>
bool ArrayMaxHeap<T>::add(const T& newData);
// Remove the root (top) node
template<class T>
bool ArrayMaxHeap<T>::remove();
// Removes all nodes from the heap
template<class T>
void ArrayMaxHeap<T>::clear();

#endif _ARRAY_MAX_HEAP