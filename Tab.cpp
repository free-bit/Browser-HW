#include "Tab.hpp"

Tab::Tab():
page(""),prevPages(Stack<string>()),nextPages(Stack<string>())
{

}
Tab::Tab(const Tab &rhs)
{
	*this=rhs;
}

Tab & Tab::operator=(const Tab &rhs)
{
	this->page=rhs.page;
	this->prevPages=rhs.prevPages;
	this->nextPages=rhs.nextPages;
	return *this;
}

string & Tab::getURL()
{
	return page;
}

void Tab::openURL(string & newURL)
{
	if(page!=newURL)//If same URL is not entered.
	{
		if(page!="")
			prevPages.push(page);
		page=newURL;
		nextPages.clear();//No next pages after open operation.
	}
}

void Tab::showURL()
{	 	  	  	 	    	 	      	 	
	cout<<page<<endl;
}

void Tab::forward()
{
	if(!nextPages.isEmpty())//If there are links in forward
	{
		prevPages.push(page);
		page=nextPages.pop();
	}
}

void Tab::backward()
{
	if(!prevPages.isEmpty())//If there are links in backward
	{
		nextPages.push(page);
		page=prevPages.pop();
	}
}

void Tab::displayDetails()
{
	nextPages.printReversed();
	cout<<"> ";
	showURL();
	prevPages.print();
}

ostream& operator<<(ostream &out,Tab &rhs)
{
	out<<rhs.page;
	return out;
}	 	  	  	 	    	 	      	 	
