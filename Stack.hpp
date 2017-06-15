#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>
#include <cstddef>
#include <stdexcept>

using namespace std;

template <class T> 
class Stack {

    private:
        /* array keeping the items of the stack */
        T* items=NULL;
        /* number of items in the stack */
        size_t size;
        /* capacity of the stack */
        size_t capacity;

        int top_index;

    public:
        /* Creates a stack of given "capacity" 
           default is 8 items
           */
        Stack(int capacity=8);

        /* Copy constructor, Assignment operator, Destructor*/
        Stack(const Stack<T>& stack);
        Stack<T>& operator=(const Stack<T>& stack);
        ~Stack();

        /* pushes the "item" to the top of the stack 
           increases the capacity as needed
           doubles the capacity when full
           */
        void push(const T& item);
        /* pops the item at the top of the stack and returns 
           decreases the capacity when needed
           halves the capacity when less then 1/3 full
           */
        T pop();
        /* returns the item at the top of the stack witout modifiying the stack 
           (take a look at the top item) 
           */
        const T& top() const;
        /* clears the contents of the stack */
        void clear();
        /* returns true if the stack is empty, false otherwise */
        bool isEmpty() const;
        /* returns the number of items in the stack */
        size_t getSize() const;
        /* returns the capacity the stack */
        size_t getCapacity() const;
        /* prints the contents of the stack 
           from top to bottom, one item per line
           assumes the objects in the stack have operator<< overloaded 
           */
        void print() const;
        /* prints the contents of the stack 
           from bottom to top, one item per line
           assumes the objects in the stack have operator<< overloaded 
           */
        void printReversed() const;
};

template <class T>
Stack<T>::Stack(int capacity)://Default Cap=8
capacity(capacity),size(0),top_index(-1)
{	 	  	  	 	    	 	      	 	
	items = new T[capacity];
}

template <class T>
Stack<T>::Stack(const Stack<T>& stack)
{
	*this=stack;
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& stack)
{
	if(this != &stack)//If they do not point to the same object already
	{
		if(!isEmpty())//If items is not empty
		{
			delete [] items;
		}
		capacity = stack.getCapacity();
		items = new T[capacity];
		size = stack.getSize();
		for(int i=0;i<size;i++)
		{
			items[i] = stack.items[i];
		}
		top_index=size-1;
	}
	return *this;
}

template <class T>
Stack<T>::~Stack()
{
	delete [] items;
}

template <class T>
void Stack<T>::push(const T& item)
{	 	  	  	 	    	 	      	 	
	if(size+1>capacity)//Double the capacity.
	{
		capacity=capacity*2;
		T* clearOld=items;
		T* tmp = new T[capacity];
		for(int i=0;i<size;i++)
		{
			tmp[i] = items[i];//Copy the content of items to tmp
		}
		tmp[size] = item;//Last item to push.
		size++;//Size updated.
		items = tmp;//Items points to updated stack.
		tmp=NULL;
		delete [] clearOld;
	}
	else
	{
		size++;
		items[size-1] = item;//Push the new value.
	}
	top_index=size-1;
}


template <class T>
T Stack<T>::pop()
{
	if(!isEmpty())
	{
		if(size*3<capacity)//If size is less than 1/3 of capacity, halve it
		{
			if(capacity<=16)//If half of the capacity is less than 8.
			{
				T pop;
				capacity=8;
				T* clearOld=items;
				T* tmp = new T[capacity];
				for(int i=0;i<size-1;i++)
				{	 	  	  	 	    	 	      	 	
					tmp[i] = items[i];//All items copied except the last one.
				}
				pop = items[size-1];
				size--;
				top_index=size-1;
				items=tmp;
				tmp=NULL;
				delete [] clearOld;
				return pop;
			}
			else
			{
				T pop;
				capacity=capacity/2;
				T* clearOld=items;
				T* tmp = new T[capacity];
				for(int i=0;i<size-1;i++)
				{
					tmp[i] = items[i];//All items copied except the last one.
				}
				pop = items[size-1];
				size--;
				top_index=size-1;
				items=tmp;
				tmp=NULL;
				delete [] clearOld;
				return pop;
			}
		}
		else
		{
			size--;
			top_index=size-1;
			return items[size];//Last item located in old size-1 location.
		}
	}	 	  	  	 	    	 	      	 	
	else
	{
		throw out_of_range("Empty stack");
	}
}

template <class T>
const T& Stack<T>::top() const
{
	if(!isEmpty())
		return items[top_index];
	else
	{
		throw out_of_range("Empty stack");
	}
}

template <class T>
void Stack<T>::clear()
{
	delete [] items;
	size = 0;
	capacity = 8;
	items = new T[capacity];
}

template <class T>
bool Stack<T>:: isEmpty() const
{
	if(top_index<0 || size<=0)
		return true;
	else
		return false;
}

template <class T>
size_t Stack<T>::getSize() const
{	 	  	  	 	    	 	      	 	
	return size;
}

template <class T>
size_t Stack<T>::getCapacity() const
{
	return capacity;
}

template <class T>
void Stack<T>::print() const //Print top to bottom
{
	for(int i=size-1;i>=0;i--)
		cout<<items[i]<<endl;
}

template <class T>
void Stack<T>::printReversed() const//Print bottom to top
{
	for(int i=0;i<size;i++)
		cout<<items[i]<<endl;
}
#endif