#include <iostream> 
#include "game.h"

using namespace std;


int main(int argc, char* argv[])
{
    string file_name;
    if (argc < 2) {
        cout << "Usage: ./project file.txt"<<endl;
        return 1;
    }
    else file_name = argv[1];


    start_project(file_name);
    

    return 0;
}


