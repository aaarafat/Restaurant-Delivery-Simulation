#ifndef __PRIORITYQUEUEADT_H_
#define __PRIORITYQUEUEADT_H_

template<class T, int MAX_SIZE>
class PriortyQueueADT
{
	T H[MAX_SIZE + 1]; // Heap array
	int size;   // size of the Heap array

	// Utility Functions
	int Parent(int i) const;   // Return Parent Index
	int LeftChild(int i) const; // Return LeftChild Index
	int RightChild(int i) const;  // Return RightChild Index
	void SiftUp(int i);    // Move the Node up
	void SiftDown(int i);  // Move the Node down
	void Swap(int i, int j);  // Swap 2 elements

public:
	bool Insert(T val);  // Insert new element in the Queue
	T ExtractMax();      // Return the Maximum element
	bool Remove(int i);  // Remove index i
	void ChangePriority(int i, T val);   // Chnage priority of node(i)
	PriortyQueueADT();
	~PriortyQueueADT();

};
template<class T>
void PriortyQueueADT<T>::ChangePriority(int i, T val)
{
	T old = H[i];
	H[i] = val;
	if (val > old)
	{
		SiftDown(i);
	}
	else
	{
		SiftUp(i);
	}
}
template<class T>
bool PriortyQueueADT<T>::Remove(int i)
{
	H[i] = INT_MAX; // infinity (i will change it later)
	SiftUp(i);
	T temp;
	ExtractMax(temp);
}
template<class T>
bool PriortyQueueADT<T>::ExtractMax(T& result)
{
	if (size == 0)
	{
		return false;
	}
	result = H[1];
	H[1] = H[size--];
	SiftDown(1);
	return true;
}
template<class T>
bool PriortyQueueADT<T>::Insert(T val)
{
	if (size == MaxSize)
	{
		return false;
	}
	size++;
	H[size] = val;
	SiftUp(size);
	return true;
}
template<class T>
PriortyQueueADT<T>::PriortyQueueADT()
{
	size = 0;
}
template<class T>
PriortyQueueADT<T>::~PriortyQueueADT()
{
}
// Utility Functions
//////////////////////////////////
template<class T>
int PriortyQueueADT<T>::Parent(int i) const  
{
	return i/2;
}
template<class T>
int PriortyQueueADT<T>::LeftChild(int i) const
{
	return 2 * i;
}
template<class T>	
int PriortyQueueADT<T>::RightChild(int i) const
{
	return 2 * i + 1;
}
template<class T>
void PriortyQueueADT<T>::Swap(int i, int j)
{
	T temp = H[i];
	H[i] = H[j];
	H[j] = temp;
}
template<class T>	
void PriortyQueueADT<T>::SiftUp(int i)
{
	while (i > 1 && H[Parent(i)] < H[i])
	{
		swap(Parent(i),i);
		i = Parent(i);
	}
}
template<class T>	
void PriortyQueueADT<T>::SiftDown(int i)
{
	int MaxIdx = i;
	int left = LeftChild(i);
	if (left <= size && H[left] > H[MaxIdx])
	{
		MaxIdx = left;
	}
	int right = RightChild(i);
	if (right <= size && H[right] > H[MaxIdx])
	{
		MaxIdx = right;
	}
	if (i != MaxIdx)
	{
		swap(i,MaxIdx);
		SiftDown(MaxIdx);
	}
}

///////////////////////////////////

#endif