#include <string>
#include <vector>

using namespace std;



struct Game_data{
    int score;
    int lives;
};

typedef vector<Bricks_data> Bricks_list;

Game_data read_file(string file);
