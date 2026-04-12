#include "game.h"

using namespace std;


int main(int argc, char *argv[])
{
    string file_name("");
    if (argc > 1)
    {
        file_name = argv[1];
    }

    Game game;

    if(!file_name.empty())
        game.init(file_name);

    return 0;
}
