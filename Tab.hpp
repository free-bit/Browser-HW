#ifndef _TAB_H_
#define _TAB_H_

#include <iostream>
#include <string>
#include "Stack.hpp"

using namespace std;

class Tab{

    private:
        string page;
        Stack<string> prevPages;
        Stack<string> nextPages;

    public:
    	Tab();
    	Tab(const Tab &rhs);
    	Tab & operator=(const Tab &rhs);

    	string & getURL();
    	void showURL();
    	void openURL(string & newURL);
    	void forward();
        void backward();
        void displayDetails();//Previously visited urls in the tab
        friend ostream& operator<<(ostream &out,Tab &rhs);
};


#endif	 	  	  	 	    	 	      	 	
