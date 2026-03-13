#ifndef BRICK_H
#define BRICK_H

#include "message.h"
#include "tools.h"

// BRICK CLASS

class Brick
{

public:
    Brick(double x, double y, double width, int hit_points, int type);
    Brick(Brick const &old_brick);

private:
    Square square;
    int hit_points;
    int type;
};

// CHECKING FUNCTIONS

void check_brick_position(double x, double y);
void check_brick_size(double width);
void check_brick_hit_points(int hit_points);
void check_brick_type(int type);

#endif