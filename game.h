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

void start_project(string file, Brick_list& brick_list, Ball_list& ball_list);
int check_score(istringstream data);
int check_lives(istringstream data);

#endif
