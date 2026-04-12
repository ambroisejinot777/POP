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
    Game();
    // Game(Game const &old_game);
    void init(string file_name);
    void read_and_check_score(istringstream &data);
    void read_and_check_lives(istringstream &data);
    void read_and_check_paddle_data(istringstream &data);
    void read_and_check_brick_data(istringstream &data, unsigned int brick_counter);
    void read_and_check_ball_data(istringstream &data, unsigned int ball_counter);
    int get_score() const;
    int get_lives() const;
    const Paddle_ptr& get_paddle() const;
    const Brick_list& get_brick_list() const;
    const Ball_list& get_ball_list() const;
    void set_score(int new_score);
    void set_lives(int new_lives);
    void set_paddle(Paddle_ptr new_paddle_ptr);
    void add_brick(Brick new_brick);
    void add_ball(Ball new_ball);
    void empty_lists();

private:
    int score;
    int lives;
    Paddle_ptr paddle_ptr;
    Brick_list brick_list;
    Ball_list ball_list;
};

#endif
