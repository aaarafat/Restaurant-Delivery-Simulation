#ifndef _LINKED_LIST
#define _LINKED_LIST
#include "LinkedListInterface.h"
#include "Node.h"
template < class ItemType>
class LinkedList : public LinkedListInterface<ItemType>
{
private :
	Node<ItemType>* headPtr; // Pointer to first node in the chain
	Node<ItemType>* tailPtr;
	int itemCount; // Current count of list items
	Node<ItemType>* getNodeAt( int position) const ; //done
public :
	LinkedList(); //done
	LinkedList(const LinkedList<ItemType>& aList);
	virtual ~LinkedList(); //done
	bool isEmpty() const ; //done
	int Size() const ; //done
	bool add(const ItemType& newEntry); //done
	bool remove( int position); //done
	void clear(); //done
	ItemType getEntry( int position) const; //done
	bool removeBegin(ItemType& I); //done
	bool getID(int id,ItemType& I); //done
	
};
template < class ItemType>
LinkedList<ItemType>::LinkedList( const LinkedList<ItemType>& sList)
{
	itemCount = 0;
	headPtr = tailPtr = nullptr;
	Node<ItemType>* trav = sList.headPtr;
	while(trav)
	{
		insert(trav);
		trav = trav->getNext();
	}

}

template < class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0), tailPtr(nullptr)
{
}

template < class ItemType>
ItemType LinkedList<ItemType>::getEntry( int position) const
{
	Node<ItemType>* nodePtr = getNodeAt(position);
	return nodePtr->getItem();
}

template < class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt( int position) const
{
	Node<ItemType>* curPtr = headPtr;
	for ( int skip = 1; skip < position; skip++)
	curPtr = curPtr->getNext();
	return curPtr ;
}

template < class ItemType>
bool LinkedList<ItemType>::add(const ItemType& newEntry)
{
	Node<ItemType>* nod = new Node<ItemType>(newEntry);
	if(!nod) return false;
	if(!headPtr)
	{
		headPtr = nod;
		tailPtr = headPtr;
		
	}
	else
	{
		tailPtr->setNext(nod);
		tailPtr = nod;
	}
	itemCount++;
	return true;
}

template < class ItemType>
bool LinkedList<ItemType>::remove( int position)
{
	bool ableToRemove = (position >= 1) && (position <= itemCount);
	if (ableToRemove)
	{
		Node<ItemType>* curPtr = nullptr ;
		if (position == 1)
		{
			// Remove the first node in the chain
			curPtr = headPtr; // Save pointer to node
			headPtr = headPtr->getNext();
		}
		else
		{
			// Find node that is before the one to delete
			Node<ItemType>* prevPtr = getNodeAt(position - 1);
			// Point to node to delete
			curPtr = prevPtr->getNext();
			// Disconnect indicated node from chain by connecting the
			// prior node with the one after
			prevPtr->setNext(curPtr->getNext());
		} // end if
		// Return node to system
		curPtr->setNext(nullptr);
		delete curPtr;
		curPtr = nullptr ;
		itemCount--; // Decrease count of entries
	} // end if
	return ableToRemove;
}

template < class ItemType>
void LinkedList<ItemType>::clear()
{
	while (!isEmpty())
	remove(1);
}

template < class ItemType>
LinkedList<ItemType>::~LinkedList()
{
	clear();
}

template <class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
	return !headPtr;
}

template <class ItemType>
int LinkedList<ItemType>::Size() const
{
	return itemCount;
}

template <class ItemType>
bool LinkedList<ItemType>::removeBegin(ItemType& I)
{
	if(headPtr)
	{
		Node<ItemType>* nod = headPtr;
		I=headPtr->getItem();
		headPtr = headPtr->getNext();
		nod->setNext(nullptr);
		itemCount--;
		//return (nod->getItem());
		nod->setNext(nullptr);
		delete nod;
		return true;
	}
	return false;
}

template <class ItemType>
bool LinkedList<ItemType>::getID(int id,ItemType &I)
{
	Node<ItemType>* trav = headPtr;
	if(trav)
	{
		if(*(headPtr->getItem())==id) 
		{
			Node<ItemType> *nod = headPtr;
			headPtr = headPtr->getNext();
			nod->setNext(nullptr);
			I = nod->getItem();
			delete nod;
			nod = nullptr;
			itemCount--;
			return true;
		}
		while(trav)
		{
			if ((*(trav->getNext()->getItem())==id)&&trav->getNext())
			{
				Node<ItemType>* nod = trav->getNext();
				trav->setNext(nod->getNext());
				nod->setNext(nullptr);
				I = nod->getItem();
				delete nod;
				nod = nullptr;
				itemCount--;
				return true;
			}
			else trav=trav->getNext();
		}
	}
	return false;
}
#endif