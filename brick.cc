#include "brick.h"
#include "constants.h"

// CONSTRUCTORS

static void draw_brick_recursive(const Cairo::RefPtr<Cairo::Context> &cr,
                                    double x, double y, double w,
                                    int level, Color color)
{
    if (level <= 0)
        return;

    draw_brick(cr, x, y, w, color);

    double new_w = (w-split_brick_gap)/2.0;
    double offset = (w+split_brick_gap)/4.0;

    // switch(level)
    // {
    //     case()
    // }

    draw_cross_recursive(cr, x - offset, y +offset, new_w, level - 1, color);
    draw_cross_recursive(cr, x + offset, y +offset, new_w, level - 1, color); 
    draw_cross_recursive(cr, x - offset, y -offset, new_w, level - 1, color);
    draw_cross_recursive(cr, x + offset, y-offset, new_w, level - 1, color); 
}

Brick::Brick(bool& error_occured, double x, double y, double width, int hit_points, int type)
    : square(x, y, width), hit_points(hit_points), type(type)
{
    check_brick_position(x, y, width, error_occured);
    check_brick_size(width, error_occured);
    check_brick_hit_points(hit_points, error_occured);
    check_brick_type(type, error_occured);

    color = get_color();
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

double Brick::get_width() const
{
    return square.get_width();
}

Square Brick::get_square() const
{
    return square;
}

int Brick::get_type() const
{
    return type;
}

int Brick::get_hitpoints() const
{
    return hit_points;
}

bool Brick::is_destroyed() const
{
    return hit_points <= 0;
}

Color Brick::get_color() const
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

// RAINBOWBRICK

RainbowBrick::RainbowBrick(bool& error_occured, double x, double y, double width, int hit_points, int type)
    : Brick(error_occured, x, y, width, hit_points, type)
{
    check_brick_hit_points(hit_points, error_occured);
}

void RainbowBrick::draw(const Cairo::RefPtr<Cairo::Context> &cr) const
{
    draw_square(cr, get_x(), get_y(), get_width(), get_color());
}

// void RainbowBrick::hit_reaction()
// {
    
// }

// BALLBRICK

BallBrick::BallBrick(bool &error_occured, double x, double y, double width, int hit_points, int type)
    : Brick(error_occured, x, y, width, hit_points, type)
{
    hit_points = 1;
}

void BallBrick::draw(const Cairo::RefPtr<Cairo::Context> &cr) const
{
    draw_square(cr, get_x(), get_y(), get_width(), get_color());
    draw_circle(cr, get_x(), get_y(), new_ball_radius);
}

// void BallBrick::hit_reaction()
// {
    
// }

// SPLITBRICK

SplitBrick::SplitBrick(bool &error_occured, double x, double y, double width, int hit_points, int type)
    : Brick(error_occured, x, y, width, hit_points, type)
{}



void SplitBrick::draw(const Cairo::RefPtr<Cairo::Context> &cr) const
{
    double x = get_x();
    double y = get_y();
    double w = get_width();

    draw_square(cr, x, y, w, get_color());
    draw_cross(cr, x, y, w, get_color());

    int levels = get_hitpoints()-1;
    draw_cross_recursive(cr, x, y, w, levels, RED);
}

// void SplitBrick::hit_reaction()
// {
    
// }


// CHECKING FUNCTIONS

void check_brick_position(double x, double y, double width, bool &error_occured)
{
    if ((x + width/2 > arena_size) or
        (x - width / 2 < 0) or
        (y + width / 2 > arena_size) or
        (y - width / 2 < 0))
    {
        display_error(message::brick_outside(x, y), error_occured);
    }
}

void check_brick_size(double width, bool& error_occured)
{
    if (width < brick_size_min)
    {
        display_error(message::invalid_brick_size(width), error_occured);
    }
}

void check_brick_hit_points(int hit_points, bool& error_occured)
{
    if (hit_points < 1 or hit_points > 7)
    {
        display_error(message::invalid_hit_points(hit_points), error_occured);
    }
}

void check_brick_type(int type, bool& error_occured)
{
    if (type < 0 or type > 2)
    {
        display_error(message::invalid_brick_type(type), error_occured);
    }
}