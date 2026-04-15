#include "brick.h"

// CONSTRUCTORS

Brick::Brick(double x, double y, double width, int hit_points, int type)
    : square(x, y, width), hit_points(hit_points), type(type)
{
    check_brick_position(x, y, width);
    check_brick_size(width);
    check_brick_hit_points(hit_points);
    check_brick_type(type);
}

Brick::Brick(Brick const &old_brick)
    : square(old_brick.square), hit_points(old_brick.hit_points), type(old_brick.type)
    {}

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
    switch (hit_points)
    {
    case 7:
        return PURPLE;
    case 6:
        return BLUE;
    case 5:
        return CYAN;
    case 4:
        return GREEN;
    case 3:
        return YELLOW;
    case 2:
        return ORANGE;
    default:
        return RED;
    }
}

// ════════════════════════════════════════════════════════════════
// Vérifications
// ════════════════════════════════════════════════════════════════

void check_brick_position(double x, double y, double width, bool& error_occured)
{
    if (x + width / 2 > arena_size || x - width / 2 < 0 ||
        y + width / 2 > arena_size || y - width / 2 < 0)
        display_error(message::brick_outside(x, y));
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
    if (hit_points < 1 || hit_points > 7)
        display_error(message::invalid_hit_points(hit_points));
    }
}

void check_brick_type(int type, bool& error_occured)
{
    if (type < 0 or type > 2)
        display_error(message::invalid_brick_type(type));
        error_occured=true;
    }
}

// ════════════════════════════════════════════════════════════════
// Factory
// ════════════════════════════════════════════════════════════════

unique_ptr<Brick> make_brick(int type, double x, double y,
                             double width, int hit_points)
{
    check_brick_type(type);
    switch (type)
    {
    case 0:
        return make_unique<RainbowBrick>(x, y, width, hit_points);
    case 1:
        return make_unique<BallBrick>(x, y, width, hit_points);
    case 2:
        return make_unique<SplitBrick>(x, y, width, hit_points);
    default:
        return nullptr;
    }
}