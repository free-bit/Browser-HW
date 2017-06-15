#include <iostream>
#include <fstream>

#include "Browser.hpp"

int main(int argc, char *argv[]){    

    Browser browser = Browser();
    ifstream tasks(argv[1]);
    for (string line; getline(tasks, line); ){
        cout << ">>> " << line << endl;
        browser.handleTask(line);
        cout << endl;
    }
    tasks.close();
    return 0;
}
