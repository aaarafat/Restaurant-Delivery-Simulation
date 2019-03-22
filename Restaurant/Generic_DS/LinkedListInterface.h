/** Interface for the ADT list
@file ListInterface.h */
#ifndef _LIST_INTERFACE
#define _LIST_INTERFACE
template <class ItemType>
class LinkedListInterface
{
public :
	virtual bool isEmpty() const = 0;
	virtual int Size() const = 0;
	virtual bool add(const ItemType& newEntry) = 0;
	virtual bool remove( int position) = 0;
	virtual void clear() = 0;
	virtual ItemType getEntry( int position) const = 0;
};
#endif