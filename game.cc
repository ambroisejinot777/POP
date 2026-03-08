#include <iostream>
#include <fstream>
#include <sstream>


#include "game.h"
#include "message.h"
#include "brick.h"
#include "ball.h"
#include "brick.h"



void read_file(string file_name){

    ifstream file(file_name);

    if (file.fail()){
        cout << "Cannot open the file: " << file_name << endl;
        return;
    }
    
    string line;
    int line_counter(0);
    int nb_ball;
    int nb_brick;

   

    while(getline(file >> ws, line)){

        istringstream data(line);


        if (line.empty() or line[0] == '#'){
            continue;
        }
        line_counter++;

        if(line_counter == 1){
            int score;
            data >> score;
            cout << "score: "<< score << endl;
        }

        else if(line_counter == 2){
            int nb_lives;
            data >> nb_lives;
            cout << "lives: "<< nb_lives << endl;
            cout << endl;
        }

        else if (line_counter == 3){
            double x, y, radius;
            data >> x >> y >> radius;
            cout << "Paddle x position: "<< x << ", Paddle y position: "<< y << ", Paddle radius: "<< radius << endl;
            cout << endl;
        }

        else if (line_counter == 4){
            data >> nb_brick;
            cout << "There is "<< nb_brick << " bricks:"<< endl;
            cout << endl;
        }
        else if ((line_counter >= 5) && (line_counter <= 4 + nb_brick)){
            int type, hit_points;
            double x, y, size;
            char left_bracket, right_bracket;
            data >> type >> x >> y >> size >> left_bracket >> hit_points >> right_bracket;
            cout << "Brick x position: "<< x << ", Brick y position: "<< y << ", Brick type: "<< type<<
                 ", Brick size: " << size << ", Brick hit points: " << hit_points <<endl;
        }
        else if (line_counter == 5 + nb_brick){
            cout << endl;
            data >> nb_ball;
            cout << "There is "<< nb_ball << " balls:"<< endl;
            cout << endl;
        }
        else if ((line_counter > 5 + nb_brick) && (line_counter <= 5 + nb_brick + nb_ball)){
            double x, y, radius, dx, dy;
            data >> x >> y >> radius  >> dx >> dy;
            cout << "Ball x position: "<< x << ", Ball y position: "<< y << ", Ball radius: "<< radius <<
                 ", Ball x speed: " << dx << ", Ball y speed " << dy <<endl;
        }
    }

    file.close();
}
