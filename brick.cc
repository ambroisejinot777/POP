#include "brick.h"

// CONSTRUCTORS

Brick::Brick(double x = 0.0, double y = 0.0, double width = 0.0, int hit_points = 0, int type = 0)
    : square(x, y, width), hit_points(hit_points), type(type)
{
    check_brick_position(x, y, width);
    check_brick_size(width);
    check_brick_hit_points(hit_points);
    check_brick_type(type);
}

Brick::Brick(Brick const &old_brick)
    : square(old_brick.square), hit_points(old_brick.hit_points), type(old_brick.type) {}

// CHECKING FUNCTIONS

void check_brick_position(double x, double y, double width)
{
    if ((x + width/2 > arena_size) or
        (x - width / 2 < 0) or
        (y + width / 2 > arena_size) or
        (y - width / 2 < 0))
    {
        error(message::brick_outside(x, y));
    }
}

void check_brick_size(double width)
{
    if (width < brick_size_min)
        error(message::invalid_brick_size(width));
}

void check_brick_hit_points(int hit_points)
{
    if (hit_points < 1 and hit_points > 7)
    {
        error(message::invalid_hit_points(hit_points));
    }
}

void check_brick_type(int type)
{
    if (type < 0 or type > 3)
        error(message::invalid_brick_type(type));
}