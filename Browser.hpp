#ifndef _BROWSER_H_
#define _BROWSER_H_

#include <string>
#include "LinkedList.hpp"
#include "Stack.hpp"
#include "Tab.hpp"
#include <cstdlib>

class Browser{

    private:
        /*Private data*/
        Tab* selected;//Pointer to data/inside of Tab
        Node<Tab>* selectedTab;//Pointer to Tab node in the list
        int indexSelectedTab;
        LinkedList<Tab> pages;
        Stack<Tab> closedPages;
        Stack<int> closedIndex;
        /*Private member functions*/
        int countDelim(string str);

    public:
        Browser();
        Browser(const Browser &rhs);
        Browser & operator=(const Browser &rhs);
        ~Browser();
        int search(Node<Tab>* TabToSearch);
        void handleTask(string task);
        void openTab(string URL="");//Insert Tab at the end, default URL is empty
        void openAfterTab(string URL="");//Insert Tab after current Tab.
        void closeTab(int pos);//Erase Tab. Save it to Stack.
        void moveTab(int from, int to);
        void selectTab(int pos);
        void reopenTab();
        void display();//Currently viewed/selected tab, opened and closed tabs in the window
        Tab getSelected();
        Tab* getSelectedPtr();
        int getIndex() const;
};

#endif	 	  	  	 	    	 	      	 	
