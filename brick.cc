#include "brick.h"

// CONSTRUCTORS

Brick::Brick(double x = 0.0, double y = 0.0, double width = 0.0, int hit_points = 0, Brick_type type = DEFAULT)
    : square(x, y, width), hit_points(hit_points), type(type)
{
    if (width < brick_size_min)
    {
        error(message::invalid_brick_size(width));
    }
    if ((x + width / 2 > arena_size) or
        (x - width / 2 < 0) or
        (y + width / 2 > arena_size) or
        (y - width / 2 < 0))
    {
        error(message::brick_outside(x, y));
    }
    if (hit_points > 0 and hit_points < 8)
    {
        error(message::invalid_hit_points(hit_points));
    }
}

Brick::Brick(Brick const &old_brick)
    : square(old_brick.square), hit_points(old_brick.hit_points), type(old_brick.type) {}