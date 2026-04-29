#ifndef GAME_H
#define GAME_H

// game.h : class de game
//           version 1.0

#include <fstream>
#include <sstream>

#include "brick.h"
#include "ball.h"
#include "paddle.h"

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
    Game() = delete;
    Game(std::string filename);
    // Game(Game const &old_game);

    int get_score() const;
    int get_lives() const;
    const Paddle_ptr& get_paddle() const;
    const Brick_list& get_brick_list() const;
    const Ball_list& get_ball_list() const;
    std::string get_file() const;

    void add_brick(std::unique_ptr<Brick> ptr);
    void add_ball(Ball& new_ball);
    void update_balls_data();   
    void update_paddle_position(double x);
    void save(const std::string &file_name) const;
    void create_new_ball(double x, double y);

    // void error_and_empty_canvas(string message);

private:
    int score;
    int lives;
    Paddle_ptr paddle_ptr;
    Brick_list brick_list;
    Ball_list ball_list;
    std::string filename;

    void set_score(int new_score);
    void set_lives(int new_lives);
    void set_file(std::string file_name);
    void set_paddle(Paddle_ptr new_paddle_ptr);



    void init(std::string file_name);

    void read_and_check_score(std::istringstream &data, bool& error_occured);
    void read_and_check_lives(std::istringstream &data, bool& error_occured);
    void read_and_check_paddle_data(std::istringstream &data, bool& error_occured);
    void read_and_check_brick_data(std::istringstream &data, unsigned int brick_counter, 
                                                                bool& error_occured);
    void read_and_check_ball_data(std::istringstream &data, unsigned int ball_counter, 
                                                                bool& error_occured);

    int resolve_hit_points_split_brick(double w);
    void reset();


};

#endif
