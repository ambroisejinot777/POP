#include <iostream>
#include <fstream>
#include <sstream>


#include "game.h"
#include "message.h"
#include "brick.h"
#include "ball.h"
#include "brick.h"



void start_project(string file_name){

    ifstream file(file_name);

    if (file.fail()){
        cout << "Cannot open the file: " << file_name << endl;
        return;
    }
    
    string line;
    Reading_state reading_state(SCORE);
    int nb_brick;
    int brick_counter(1);
    int nb_ball;
    int ball_counter(1);

   

    while(getline(file >> ws, line)){

        istringstream data(line);


        if (line.empty() or line[0] == '#'){
            continue;
        }

        switch(reading_state){

            case SCORE:
                int score;
                data >> score;
                cout << "score: "<< score << endl;
                reading_state = LIVES;
                break;

            case LIVES:
                int nb_lives;
                data >> nb_lives;
                cout << "lives: "<< nb_lives << endl;
                cout << endl;
                reading_state = PADDLE;
                break;
            
            case PADDLE:
                double paddle_x, paddle_y, paddle_radius;
                data >> paddle_x >> paddle_y >> paddle_radius;
                cout << "Paddle x position: "<< paddle_x << ", Paddle y position: "<< paddle_y << ", Paddle radius: "<< paddle_radius << endl;
                cout << endl;
                reading_state = NB_BRICK;
                break;

            case NB_BRICK:
                data >> nb_brick;
                cout << "There is "<< nb_brick << " bricks:"<< endl;
                cout << endl;
                reading_state = BRICKS;
                break;

            case BRICKS:
                int type, hit_points;
                double brick_x, brick_y, brick_size;
                char left_bracket, right_bracket;
                data >> type >> brick_x >> brick_y >> brick_size >> left_bracket >> hit_points >> right_bracket;
                cout << "Brick type: "<< type << ", Brick x position: "<< brick_x << ", Brick y position: "<< brick_y <<
                        ", Brick size: " << brick_size << ", Brick hit points: " << hit_points <<endl;
                if (brick_counter >= nb_brick){
                    reading_state = NB_BALL;
                }
                ++brick_counter;
                break;

            case NB_BALL:
                cout << endl;
                data >> nb_ball;
                cout << "There is "<< nb_ball << " balls:"<< endl;
                cout << endl;
                reading_state = BALLS;
                break;

            case BALLS:
                double ball_x, ball_y, ball_radius, ball_dx, ball_dy;
                data >> ball_x >> ball_y >> ball_radius  >> ball_dx >> ball_dy;
                cout << "Ball x position: "<< ball_x << ", Ball y position: "<< ball_y << ", Ball radius: "<< ball_radius <<
                    ", Ball x speed: " << ball_dx << ", Ball y speed " << ball_dy <<endl; 
                if (ball_counter >= nb_ball){
                    reading_state = FINISHED;
                }
                ++ball_counter;
                break;
            
            case FINISHED:
                cout << "Reading part is finished" << endl;
        }
    }

    file.close();
}
