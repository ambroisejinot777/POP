#include "brick.h"

// CONSTRUCTORS

Brick::Brick(bool& error_occured, double x, double y, double width, int hit_points, int type)
    : square(x, y, width), hit_points(hit_points), type(type)
{
    check_brick_position(x, y, width, error_occured);
    check_brick_size(width, error_occured);
    check_brick_hit_points(hit_points, error_occured);
    check_brick_type(type, error_occured);
}

// Brick::Brick(Brick const &old_brick)
//     : square(old_brick.square), hit_points(old_brick.hit_points), type(old_brick.type)
//     {}

double Brick::get_x() const 
{
    return square.get_x();
}

double Brick::get_y() const
{
    return square.get_y();
}

Square Brick::get_square() const
{
    return square;
}

// CHECKING FUNCTIONS

void check_brick_position(double x, double y, double width, bool& error_occured)
{
    if ((x + width/2 > arena_size) or
        (x - width / 2 < 0) or
        (y + width / 2 > arena_size) or
        (y - width / 2 < 0))
    {
        display_error(message::brick_outside(x, y));
        error_occured=true;
    }
}

void check_brick_size(double width, bool& error_occured)
{
    if (width < brick_size_min)
    {
        display_error(message::invalid_brick_size(width));
        error_occured=true;
    }
}

void check_brick_hit_points(int hit_points, bool& error_occured)
{
    if (hit_points < 1 or hit_points > 7)
    {
        display_error(message::invalid_hit_points(hit_points));
        error_occured=true;
    }
}

void check_brick_type(int type, bool& error_occured)
{
    if (type < 0 or type > 2)
    {
        display_error(message::invalid_brick_type(type));
        error_occured=true;
    }
}