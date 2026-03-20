#ifndef GAME_H
#define GAME_H

#include <fstream>
#include <sstream>

#include "message.h"
#include "brick.h"
#include "ball.h"
#include "paddle.h"

using namespace std;

enum Reading_state
{
    SCORE,
    LIVES,
    PADDLE,
    NB_BRICK,
    BRICKS,
    NB_BALL,
    BALLS,
    FINISHED,
};

class Game
{
public:
    Game() = default;
    void start(string file_name);
    Game(Game const &old_game);
    int get_score() const;
    int get_lives() const;
    Paddle get_paddle() const;
    Brick_list get_brick_list() const;
    Ball_list get_ball_list() const;

private:
    int score;
    int lives;
    Paddle paddle;
    Brick_list brick_list;
    Ball_list ball_list;
};

// FUNCTIONS //

void start_project(string file_name);
int check_score(istringstream &data);
int check_lives(istringstream &data);
void read_and_check_brick_data(istringstream &data, Brick_list &brick_list, int brick_counter);
void read_and_check_ball_data(istringstream &data, Ball_list &ball_list, unsigned int ball_counter);

#endif
