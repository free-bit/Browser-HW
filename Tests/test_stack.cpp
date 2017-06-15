#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Stack.hpp"

using namespace std;

class Rational{
    public:
        Rational(int num = 0, int den = 1): numer(num), denom(den) {};
        friend ostream &operator<<(ostream &out, const Rational& r){
            out << r.numer << "/" << r.denom;
            return out;
        };
    private:
        int numer;
        int denom;
};


void testConstructor(){
    Stack<int> s = Stack<int>();

    Stack<int> s2 = Stack<int>(13);

    s.print();
    cout << s.getCapacity() << endl;
    cout << s.getSize() << endl;

    s2.print();
    cout << s2.getCapacity() << endl;
    cout << s2.getSize() << endl;
}

void testAllocation(){

    Stack<int> s = Stack<int>();
    int pSize = s.getSize();
    int pCapacity = s.getCapacity();
    cout << pSize << "\t" << pCapacity << endl;
    for (int i = 0; i < 200; ++i){
        s.push(i+1);
        if (pCapacity != s.getCapacity()){
            cout << pSize << "\t" << pCapacity << endl;
            cout << s.getSize() << "\t" << s.getCapacity() << endl;
            pCapacity = s.getCapacity();
        }
        pSize = s.getSize();
    }
    cout << s.top() << endl;
    for (int i = 0; i < 200; ++i){
        s.pop();
        if (pCapacity != s.getCapacity()){
            cout << pSize << "\t" << pCapacity << endl;
            cout << s.getSize() << "\t" << s.getCapacity() << endl;
            pCapacity = s.getCapacity();
        }
        pSize = s.getSize();
    }
    try{
        cout << s.top() << endl;
    }
    catch(const exception& ex){
        cout << "exception handled" << endl;
        cerr << ex.what() << endl;
    }
}

void testPrint(){
    srand (time(NULL));
    Stack<Rational> s = Stack<Rational>();
    cout << s.isEmpty() << endl;
    for (int i = 0; i < 20; ++i){
        s.push(Rational(rand()%10, rand()%10));
    }
    cout << s.isEmpty() << endl;
    cout << s.getSize() << "\t" << s.getCapacity() << endl << endl;
    s.print();
}

void testCopy(){
    srand (time(NULL));
    Stack<Rational> s = Stack<Rational>();
    cout << s.isEmpty() << endl;
    for (int i = 0; i < 5; ++i){
        s.push(Rational(rand()%10, rand()%10));
    }
    s.print();
    Stack<Rational> s2 = s;
    s2.print();
    Stack<Rational> s3;
    s3 = s2;
    s3.print();
}

int main(int argc, char* argv[]){

    cout << endl << "TEST 1" << endl;
    testConstructor();

    cout << endl << "TEST 2" << endl;
    testAllocation();

    cout << endl << "TEST 3" << endl;
    testPrint();

    cout << endl << "TEST 4" << endl;
    testCopy();

    return 0;
}