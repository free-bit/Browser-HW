#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <iomanip>

using namespace std;

/* forward declerations for overloading operator<< in template*/
template<class T>
class Node;

template<class T>
ostream &operator<<(ostream &out, const Node<T>& n);

/* node class for linked list */
template<class T>
class Node {

    private:
        Node<T> *prev;
        Node<T> *next;
        T data;

    public:
        Node();
        Node(const T& d);

        Node<T>* getNext() const;
        Node<T>* getPrev() const;
        T getData() const;
        T* getDataPtr();
        
        void setNext(Node<T> *newNext); 
        void setPrev(Node<T> *newPrev);
        void setData(const T& data);

        friend ostream &operator<< <> (ostream &out, const Node<T>& n);
};

template<class T>
Node<T>::Node():
prev(NULL),next(NULL),data(T())
{}

template<class T>
Node<T>::Node(const T& d)
{
    data=d;
}

template<class T>
Node<T>* Node<T>::getNext() const
{
    return next;
}

template<class T>
Node<T>* Node<T>::getPrev() const
{
    return prev;
}

template<class T>
T Node<T>::getData() const
{
    return data;
}

template<class T>
T* Node<T>::getDataPtr()
{
    return &data;
}

template<class T>
void Node<T>::setNext(Node<T> *newNext)
{	 	  	  	 	    	 	      	 	
    next=newNext;
}

template<class T>
void Node<T>::setPrev(Node<T> *newPrev)
{
    prev=newPrev;
}

template<class T>
void Node<T>::setData(const T& data)
{
    this->data=data;
}

template<class T>
ostream &operator<<(ostream &out, const Node<T>& n){
    out << setfill('.') << setw(10) << (void*)n.prev 
        <<" <-| "<< (void*)&n <<" |-> " 
        << setfill('.') << setw(10) << (void*)n.next << " : "
        << n.data ; 
    return out;
};

#endif	 	  	  	 	    	 	      	 	
