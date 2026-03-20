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
    Game(Game const &old_game);
    void init(string file_name);
    int check_score(istringstream &data);
    int check_lives(istringstream &data);
    void read_and_check_brick_data(istringstream &data, Brick_list &brick_list, int brick_counter);
    void read_and_check_ball_data(istringstream &data, Ball_list &ball_list, unsigned int ball_counter);
    int get_score() const;
    int get_lives() const;
    Paddle get_paddle() const;
    Brick_list get_brick_list() const;
    Ball_list get_ball_list() const;
    void set_score(int new_score);
    void set_lives(int new_lives);
    void set_paddle(Paddle new_paddle);
    void add_brick_list(Brick new_brick);
    void add_ball_list(Ball new_ball);

private:
    int score;
    int lives;
    Paddle paddle;
    Brick_list brick_list;
    Ball_list ball_list;
};

#endif
