#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <sstream>

#include "message.h"
#include "brick.h"
#include "ball.h"
#include "paddle.h"


using namespace std;



enum Reading_state{
    SCORE,
    LIVES,
    PADDLE,
    NB_BRICK,
    BRICKS,
    NB_BALL,
    BALLS,
    FINISHED,
};


// FUNCTIONS //

void start_project(string file_name, Brick_list& brick_list, Ball_list& ball_list, int& score, int& lives);
int check_score(istringstream& data);
int check_lives(istringstream& data);
void read_brick_data(istringstream &data, Brick_list &brick_list);
void check_ball_data(istringstream &data, Ball_list &ball_list, unsigned int ball_counter);


#endif
