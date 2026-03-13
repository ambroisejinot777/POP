#ifndef GAME_H
#define GAME_H

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

void start_project(string file);

#endif
