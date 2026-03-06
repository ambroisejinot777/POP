#include <iostream>
#include <fstream>
#include <sstream>


#include "game.h"
#include "message.h"
#include "brick.h"
#include "ball.h"
#include "brick.h"



Game_data read_file(string file_name){

    ifstream file(file_name);
    Game_data game_data;

    if (file.fail())
        cout << "Cannot open the file: " << file_name << endl;
    

    string line;
    int value;
    int line_counter(0);
    int nb_bricks;
    int nb_balls;
   

    while(getline(file >> ws, line)){
        line_counter += 1;
        istringstream data(line);

        while(data >> value){

            if(line_counter == 1){
                game_data.score = value;
            }
            else if(line_counter == 2){
                game_data.lives = value;
            }
            else if (line_counter == 3){
                game_data.paddle.x = value;
            }

        }
    }

    file.close();


    return ;
}