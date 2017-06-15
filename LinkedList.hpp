#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include "Node.hpp"

using namespace std;

template <class T> 
class LinkedList {
    private:
        /* pointer to the first node */
        Node<T>* front=NULL;
        /* pointer to the last node */
        Node<T>* back=NULL;

        size_t size;

        void empty_insert(Node<T> *newNode);

    public:
        LinkedList();
        LinkedList(const LinkedList<T>& ll);
        LinkedList<T>& operator=(const LinkedList<T>& ll);
        ~LinkedList();

        /* returns the first node of the linked list */
        Node<T>& getFront() const;
        /* returns the last node of the linked list */
        Node<T>& getBack() const;
        /* returns the node in given "pos"ition of the linked list */
        Node<T>& getNodeAt(int pos) const;
        /* returns the pointer of the node in given 
           "pos"ition of the linked list */
        Node<T>* getNodePtrAt(int pos) const;
        
        /* inserts a new node containing "data" 
           after the node "prev" 
           */
        void insert(Node<T>* prev, const T& data);
        /* inserts a new node containing "data" 
           at "pos"ition in the linked list 
           */
        void insertAt(int pos, const T& data);
        /* erases the given "node" from the linked list */
        void erase(Node<T>* node);
        /* erases the node in given "pos"ition from the linked list */
        void eraseFrom(int pos);
        /* clears the contents of the linked list */
        void clear();

        /* inserts a new node containing "data" 
           to the front of the linked list 
           */
        void pushFront(const T& data);
        /* inserts a new node containing "data" 
           to the back of the linked list
           */
        void pushBack(const T& data);

        /* removes the first node */
        void popFront();
        /* removes the last node */
        void popBack();

        /* returns true if the list is empty, false otherwise */
        bool isEmpty() const;
        /* returns the number of items in the list */
        size_t getSize() const;
        /* prints the contents of the linked list 
           one node data per line
           assumes the objects in the node have operator<< overloaded 
           */
        void print() const;
};

template<class T>
void LinkedList<T>::empty_insert(Node<T> *newNode)
{	 	  	  	 	    	 	      	 	
	front = newNode;
	back = newNode;
	front->setPrev(NULL);
	front->setNext(NULL);
}

template<class T>
LinkedList<T>::LinkedList():
size(0)
{}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& ll)
{
	*this=ll;//First overload = operator
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& ll)
{
	if(this!=&ll)
	{

		clear();//List deleted Front and Back are set to be NULL.
		const Node<T> *rhs=ll.front;
		
		while(rhs)
		{
			if(rhs==ll.front)
			{
				insert(front,rhs->getData());//Inserted 1st node.
			}
			else
			{
				pushBack(rhs->getData());
			}	 	  	  	 	    	 	      	 	
			rhs = rhs->getNext();
		}
		
	}
	return *this;
}

template<class T>
LinkedList<T>::~LinkedList()
{
	clear();
}

template<class T>
Node<T>& LinkedList<T>::getFront() const
{
	return *front;
}

template<class T>
Node<T>& LinkedList<T>::getBack() const
{
	return *back;
}

template<class T>
Node<T>& LinkedList<T>::getNodeAt(int pos) const
{
	if(!isEmpty() && pos>=0 && pos<size)
	{
		Node<T> *head=front;
		for(int i=0;i<pos;i++)
		{
			head=head->getNext();
		}
		return *head;//Return a reference to node.
	}	 	  	  	 	    	 	      	 	
	else
		throw out_of_range("Invalid position");
}

template<class T>
Node<T>* LinkedList<T>::getNodePtrAt(int pos) const
{
	Node<T> *head=front;
	for(int i=0;i<pos;i++)
	{
		head=head->getNext();
	}
	return head;//Return a pointer to node.
}

template<class T>
void LinkedList<T>::insert(Node<T>* pre, const T& data)
{
	Node<T> *newNode = new Node<T>(data);//New node created.

	//Check whether it is an empty list or not.
	if(!isEmpty())//Not empty
	{
		if(pre)//pre!=NULL
		{
			newNode->setPrev(pre);//1st step
			if(pre->getNext()==NULL)//Insert at the end
			{
				back=newNode;//back updated
			}
			else//Arbitrary position
			{
				newNode->setNext(pre->getNext());
				pre->getNext()->setPrev(newNode);
			}
			pre->setNext(newNode);//last step
		}	 	  	  	 	    	 	      	 	
		else//Insert at 0;
			insertAt(0,data);

	}
	else//Empty
	{
		empty_insert(newNode);
	}
	size++;
}

template<class T>
void LinkedList<T>::insertAt(int pos, const T& data)
{
	Node<T> *newNode = new Node<T>(data);//New node created.
	if(pos<0 || pos>size)
		throw out_of_range("Invalid position");
	else
	{
		//Check whether it is an empty list or not.
		if(!isEmpty())//Not empty
		{
			if(pos==0)//Insert at the beginning for a non-empty list
			{
				newNode->setPrev(NULL);
				newNode->setNext(front);
				front->setPrev(newNode);
				front=newNode;//front updated.
			}
			else//Arbitrary position
			{
				Node<T> *pre = getNodePtrAt(pos-1);//Get to (pos-1)th
				
				newNode->setPrev(pre);
				newNode->setNext(pre->getNext());
				if(!(pre->getNext()))//If insertion is to the end.
				{	 	  	  	 	    	 	      	 	
					back=newNode;//back updated.
				}
				else//If insertion is to the middle
				{	
					pre->getNext()->setPrev(newNode);
				}
				pre->setNext(newNode);
			}
		}
		else//Empty
		{
			empty_insert(newNode);
		}
		size++;
	}
}

template<class T>
void LinkedList<T>::erase(Node<T>* node)
{
	if(node)
	{
		if(!node->getPrev())//In front
		{
			front=node->getNext();	
		}

		else
		{
			node->getPrev()->setNext(node->getNext());
		}

		if(!node->getNext())//In back
		{
			back=node->getPrev();
		}	 	  	  	 	    	 	      	 	

		else
		{
			node->getNext()->setPrev(node->getPrev());
		}
		//Cut off the connection
		node->setNext(NULL);
		node->setPrev(NULL);
		delete node;
		size--;
	}
}

template<class T>
void LinkedList<T>::eraseFrom(int pos)
{
	if (!isEmpty() && pos>=0 && pos<size)
	{
		erase(getNodePtrAt(pos));
	}
	else
		throw out_of_range("Invalid position");
}

template<class T>
void LinkedList<T>::clear()
{
	if(!isEmpty())
	{
		Node<T>* tmp=front->getNext();
		while(tmp)//Delete until "back"
		{
			erase(tmp->getPrev());
			tmp=tmp->getNext();
		}	
		erase(back);//Back is deleted.
		front=NULL;
		back=NULL;
	}	 	  	  	 	    	 	      	 	
}

template<class T>
void LinkedList<T>::pushFront(const T& data)
{
	insertAt(0, data);
}

template<class T>
void LinkedList<T>::pushBack(const T& data)
{
	insert(back, data);
}

template<class T>
void LinkedList<T>::popFront()
{
	erase(front);
}

template<class T>
void LinkedList<T>::popBack()
{
	erase(back);
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
	if(!front && !back)
		return true;
	else
		return false;
}

template<class T>
size_t LinkedList<T>::getSize() const
{	 	  	  	 	    	 	      	 	
	return size;
}

template<class T>
void LinkedList<T>::print() const
{
	if(!isEmpty())
	{
		Node<T> *head=front;
		while(1)
		{
			if(head==back)//Last node
			{
				cout<<head->getData()<<endl;
				break;
			}
			cout<<head->getData()<<endl;
			head=head->getNext();
		}
	}
}

#endif