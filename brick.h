#ifndef BRICK_H
#define BRICK_H

#include "message.h"
#include "tools.h"

enum Brick_type
{
    DEFAULT,
    RAINBOW_BRICK,
    BALL_BRICK
};

class Brick
{

public:
    Brick(double x, double y, double width, int hit_points, Brick_type type);
    Brick(Brick const &old_brick);

private:
    Square square;
    int hit_points;
    Brick_type type;
};

#endif