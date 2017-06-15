#include <iostream>
#include <cstdlib>
#include <ctime>
#include "LinkedList.hpp"

using namespace std;

class Rational{
    public:
        Rational(int num=0, int den=1){
            numer = num;
            denom = den;
        };
        friend ostream &operator<<(ostream &out, const Rational& r){
            out << r.numer << "/" << r.denom;
            return out;
        };
    private:
        int numer;
        int denom;
};

void testConstructor(){

    LinkedList<int> l;
    l.print();
    cout << l.getSize() << endl;
    cout << l.isEmpty() << endl;
}

void testAllocation(){

    LinkedList<int> list;
    cout << list.isEmpty() << endl;
    for (int i = 0; i < 20; ++i){
        list.pushBack(1100+i+1);
        if (i%5 == 4)
            cout << list.getSize() << endl;
    }
    cout << list.isEmpty() << endl;
    list.print();

    cout << list.getFront() << endl;
    cout << list.getFront().getData() << endl;
    cout << list.getBack() << endl;
    cout << list.getBack().getData() << endl;

    cout << list.getNodeAt(1) << endl;
    cout << list.getNodeAt(1).getData() << endl;
    cout << list.getNodeAt(2) << endl;
    cout << list.getNodeAt(2).getData() << endl;
    cout << list.getNodeAt(10) << endl;
    cout << list.getNodeAt(10).getData() << endl;

    cout << list.getNodePtrAt(1) << endl;
    cout << list.getNodePtrAt(2) << endl;
    cout << list.getNodePtrAt(10) << endl;

    try{
        cout << list.getNodeAt(-1) << endl;
    }
    catch(const exception& e){
        cout << "exception handled" << endl;
        cerr << e.what() << endl;
    }
    try{
        cout << list.getNodeAt(20) << endl;
    }
    catch(const exception& e){
        cout << "exception handled" << endl;
        cerr << e.what() << endl;
    }
}

void testInsertErase(){

    LinkedList<Rational> list;

    cout << "insert" << endl;
    list.insertAt(0, Rational(1,2));
    list.insertAt(1, Rational(2,4));
    list.insertAt(0, Rational(3,6));
    list.insertAt(3, Rational(4,8));
    cout << "size:" << list.getSize() << endl;
    list.print();
    cout << endl;
    cout << "insert" << endl;
    Node<Rational>* p3 = list.getNodePtrAt(0);
    Node<Rational>* p4 = list.getNodePtrAt(3);
    list.insertAt(list.getSize(), Rational(5,10));
    list.insertAt(0, Rational(6,12));
    cout << "size:" << list.getSize() << endl;
    list.print();
    cout << endl;
    
    cout << "pointers" << endl;
    cout << *p3 << endl;
    cout << *p4 << endl;
    cout << endl;

    cout << "insert" << endl;
    list.insert(p3, Rational(7,14));
    list.insert(p4, Rational(8,16));
    cout << "size:" << list.getSize() << endl;
    list.print();
    cout << endl;

    cout << "pointers" << endl;
    cout << *p3 << endl;
    cout << *p4 << endl;
    cout << endl;

    cout << "erase" << endl;
    list.eraseFrom(3);
    list.eraseFrom(3);
    cout << "size:" << list.getSize() << endl;
    list.print();
    cout << endl;
    cout << "erase" << endl;
    list.erase(p3);
    list.erase(p4);
    cout << "size:" << list.getSize() << endl;
    list.print();
    cout << endl;
    cout << "clear" << endl;
    list.clear();
    cout << "size:" << list.getSize() << endl;
    list.print();
    cout << endl;

}


void testPushPop(){

    LinkedList<int> list;

    list.pushFront(4);
    list.pushBack(5);
    list.pushFront(3);
    list.pushBack(6);
    list.print();
    cout << endl;
    list.pushBack(7);
    list.pushFront(2);
    list.pushBack(8);
    list.pushFront(1);
    cout << "size:" << list.getSize() << endl;
    list.print();
    cout << endl;

    list.popFront();
    list.print();
    cout << endl;
    list.popFront();
    list.print();
    cout << endl;

    list.popBack();
    list.print();
    cout << endl;
    list.popBack();
    cout << "size:" << list.getSize() << endl;
    list.print();
    cout << endl;

    list.popBack();
    list.popBack();
    list.popBack();
    cout << "size:" << list.getSize() << endl;
    list.print();
    cout << endl;
    list.popFront();
    cout << "size:" << list.getSize() << endl;
    list.print();
    cout << endl;
}


int main(int argc, char* argv[]){

    cout << endl <<endl << "TEST 1" << endl;
    testConstructor();

    cout << endl << "TEST 2" << endl;
    testAllocation();

    cout << endl << "TEST 3" << endl;
    testInsertErase();

    cout << endl << "TEST 4" << endl;
    testPushPop();

    return 0;
}