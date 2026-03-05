#include <iostream> 
#include <fstream>
#include "game.h"

using namespace std;



int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Usage: ./project"<< argv[1] <<endl;
        return 1;
    }

    ifstream file(argv[1]);

    if (!file) {
        cout << "Impossible d'ouvrir le fichier"<<endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        cout << line << std::endl;
    }

    file.close();
}