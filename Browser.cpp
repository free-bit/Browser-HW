#include "Browser.hpp"
Browser::Browser():
selected(NULL),selectedTab(NULL),indexSelectedTab(-1),pages(LinkedList<Tab>()),closedPages(Stack<Tab>()),closedIndex(Stack<int>())
{}
Browser::Browser(const Browser &rhs)
{
    *this=rhs;
}
Browser & Browser::operator=(const Browser &rhs)
{
    if(this!=&rhs)
    {
        this->pages = rhs.pages;
        this->closedPages = rhs.closedPages;
        this->closedIndex = rhs.closedIndex;
        this->indexSelectedTab = rhs.indexSelectedTab;
        this->selectedTab = pages.getNodePtrAt(indexSelectedTab);
        this->selected = selectedTab->getDataPtr();
    }
    return *this;
}
       

Browser::~Browser()
{
	selected=NULL;
	selectedTab=NULL;
}

int Browser::search(Node<Tab>* TabToSearch)
{
    if(!pages.isEmpty())
    {
        Node<Tab>* tmp = &(pages.getFront());
        for(int i=0;i<pages.getSize();i++)
        {	 	  	  	 	    	 	      	 	
            if(tmp==TabToSearch)
            {
                return i;
            }
            tmp=tmp->getNext();
        }
    }
    return -1;//Indicates not found.
}
/*Helper function for handleTask*/
int Browser::countDelim(string str)
{
    char delim=' ';
	int count=0;
	for(int i=0;i<str.length();i++)
	{
		if(str[i]==delim)
		{
			count++;
		}
	}
	return count;
}

void Browser::handleTask(string task)
{
    int numberOfDelim = countDelim(task), len=task.length();
    string op;
    if(numberOfDelim == 0)
    {
    	op.assign(task);//Exclude delim
        if(op == "reopen_closed_tab")
        {
        	reopenTab();
        }

        else if(op == "display")
        {	 	  	  	 	    	 	      	 	
        	display();
        }
        else if(op == "display_tab_details")
        {
        	selected->displayDetails();
        }
        else if(op == "close_selected_tab")
        {
			closeTab(indexSelectedTab);
        }
        else if(op == "back")
        {
        	selected->backward();
        }
        else if(op == "forward")
        {
        	selected->forward();
        }
    }
    else if(numberOfDelim == 1)
    {
    	int i = task.find_first_of(" ");
    	op.assign(task,0,i);//Exclude delim
        if(op == "open_new_page")
        {
        	string url;
            url.assign(task,i+1,len-i-1);//length of arg len-1-(i+1)+1
            openTab(url);
        }
        else if(op == "open_link")
        {
        	string url;
            url.assign(task,i+1,len-i-1);
            selected->openURL(url);
        }
        else if(op == "open_link_in_new_tab")
        {
        	string url;
            url.assign(task,i+1,len-i-1);
            openAfterTab(url);
        }
        else if(op == "close_tab")
        {
        	int j;
        	string index;
        	index.assign(task,i+1,len-i-1);
        	j=atoi(index.c_str());
        	closeTab(j);
        }
        else if(op == "select_tab")
        {
        	int j;
        	string index;
        	index.assign(task,i+1,len-i-1);
        	j=atoi(index.c_str());
        	selectTab(j);
        }
    }

    else if(numberOfDelim==2)
    {
    	string from, to;
    	int i = task.find_first_of(" ");
    	op.assign(task,0,i);//Exclude delim
    	
    	if(op == "move_tab")
    	{
    		int j = task.find_last_of(" "),From,To;
    		from.assign(task,i+1,j-i-1);
    		to.assign(task,j+1,len-j-1);
    		From = atoi(from.c_str());
    		To = atoi(to.c_str());
    		moveTab(From,To);
    	}	 	  	  	 	    	 	      	 	
	}
}

void Browser::openTab(string URL)
{
	/*Able to open both empty tab and a tab with a URL*/
    Tab *newTab = new Tab;
    newTab->openURL(URL);//Default behavior is empty URL.
    pages.pushBack(*newTab);//newTab is a Tab data. With pushback Node<Tab> will be inserted.

    /*Select newTab*/
    selectedTab = &(pages.getBack());//Address of Tab node at the back is assigned to selectedTab
    indexSelectedTab = pages.getSize()-1;//Insertion is at the end.
    selected = selectedTab->getDataPtr();//Newest Tab is selected.
}

void Browser::openAfterTab(string URL)
{
	Tab *newTab = new Tab;
    newTab->openURL(URL);//Default behavior is empty URL.
    pages.insertAt(indexSelectedTab+1,*newTab);//newTab is a Tab data. With insert Node<Tab> will be inserted.
    /*Select newTab*/
    indexSelectedTab = indexSelectedTab+1;//Insertion is after the previous tab.
    selectedTab = pages.getNodePtrAt(indexSelectedTab);//Address of Tab node at the position is assigned to selectedTab
    selected = selectedTab->getDataPtr();//Newest Tab is selected.

    
}

void Browser::closeTab(int pos)//void eraseFrom(int pos); Node<T>& LinkedList<T>::getNodeAt(int pos) const;
{
    if(pos!=indexSelectedTab && pos<pages.getSize())
    {	 	  	  	 	    	 	      	 	
    	Node<Tab> *ptr = pages.getNodePtrAt(pos);
    	if(ptr)
    	{
    		if(pos<indexSelectedTab)
    			indexSelectedTab--;
    		closedPages.push(ptr->getData());
	    	pages.erase(ptr);
	    	closedIndex.push(pos);
    	}
    }
    else
    {
    	Node<Tab> *ToBeErased = selectedTab;
    	if(selectedTab)//If selectedTab exists
    	{
	    	if(selectedTab->getNext())//If next tab exists.
	    	{
		    	//Go right index remains the same.
		    	selectedTab = pages.getNodePtrAt(indexSelectedTab+1);//Next tab is selected
		    	selected = selectedTab->getDataPtr();
	    	}
	    	else if(selectedTab->getPrev())//If prev tab exists.
	    	{
	    		indexSelectedTab-=1;//Previous tab is selected
	    		selectedTab = pages.getNodePtrAt(indexSelectedTab);
	    		selected = selectedTab->getDataPtr();
	    	}
	    	else
	    	{
	    		indexSelectedTab=-1;
	    		selectedTab=NULL;
	    		selected=NULL;

	    	}
	    	closedPages.push(ToBeErased->getData());
	    	pages.erase(ToBeErased);
	    	closedIndex.push(pos);
    	}	 	  	  	 	    	 	      	 	
    }
}

void Browser::moveTab(int from, int to)
{
    int size=pages.getSize();
    if(from!=to && to<size && from<size && from>=0 && to>=0)
    {
    	selectedTab = pages.getNodePtrAt(from);//Node<Tab> * adjusted
    	selected = selectedTab->getDataPtr();//Tab * adjusted
        if(from<to)
        {  
            pages.insertAt(to+1,*selected);//Tab is moved
            pages.eraseFrom(from);
        }
        else
        {
            pages.insertAt(to,*selected);
            pages.eraseFrom(from+1);
        }
        selectTab(to);
    }
}
void Browser::selectTab(int pos)
{
	selectedTab = pages.getNodePtrAt(pos);
	selected = selectedTab->getDataPtr();
	indexSelectedTab = pos;
}

void Browser::reopenTab()
{
	int index = closedIndex.pop();
	Tab data = closedPages.pop();
	pages.insertAt(index,data);
	selectTab(index);
}	 	  	  	 	    	 	      	 	

Tab Browser::getSelected()
{
    return *selected;//Get the tab itself not the pointer
}

Tab* Browser::getSelectedPtr()
{
    return selected;//Get the tab pointer
}

int Browser::getIndex() const
{
    return indexSelectedTab;
}

void Browser::display()
{
	Node<Tab>* curr=&(pages.getFront());
	int size=pages.getSize();
	cout<<"CURRENT TAB: "<<(indexSelectedTab<0 ? 0 : indexSelectedTab)<<endl;
	if(selected)
		selected->showURL();
	cout<<"OPEN TABS: "<<size<<endl;
	while(!pages.isEmpty())
	{
		if(curr==&(pages.getBack()))
		{
			curr->getDataPtr()->showURL();
			break;
		}
		curr->getDataPtr()->showURL();
		curr=curr->getNext();
	}
	cout<<"CLOSED TABS: "<<closedPages.getSize()<<endl;
	closedPages.print();
}	 	  	  	 	    	 	      	 	