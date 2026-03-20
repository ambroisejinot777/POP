#include "game.h"

using namespace std;

// PROTOTYPES

string check_input_arguments(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    string file_name = check_input_arguments(argc, argv);
    start_project(file_name);

    return 0;
}

string check_input_arguments(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Usage: ./project file.txt" << endl;
        exit(1);
    }
    return argv[1];
}
