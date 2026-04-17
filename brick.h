#ifndef BRICK_H
#define BRICK_H

#include "message.h"
#include "tools.h"
#include "graphic.h"

// BRICK CLASS
class Brick;
typedef vector<unique_ptr<Brick>> Brick_list;

class Brick
{

public:
    Brick(bool& error_occured, double x = 0.0, double y = 0.0, double width = 0.0,
         int hit_points = 0, int type = 0, Color color_brick);
    Brick(Brick const &old_brick);

    double get_x() const;
    double get_y() const;
    Square get_square() const;

    int get_hitpoints() const;
    bool is_destroyed() const;
    Color get_color() const;

    virtual void hit_reaction() = 0;

private:
    Square square;
    int hit_points;
    int type;
    Color color;
};

class RainbowBrick : public Brick
{
public:
    RainbowBrick(bool& error_occured, double x, double y, double width, int hit_points, int type, Color color_brick);
    void hit_reaction() override;
};

class BallBrick : public Brick
{
    BallBrick(bool& error_occured, double x, double y, double width, int hitpoints, int type, Color color_brick, double new_ball_radius);
    void hit_reaction() override;
    double get_new_ball_radius() const;

private:
    double new_ball_radius;
};

class SplitBrick : public Brick
{
    SplitBrick(double x, double y, double width, int hit_points);
    void hit_reaction() override;
};


// CHECKING FUNCTIONS

void check_brick_position(double x, double y, double width, bool& error_occured);
void check_brick_size(double width, bool& error_occured);
void check_brick_hit_points(int hit_points, bool& error_occured);
void check_brick_type(int type, bool& error_occured);

#endif

