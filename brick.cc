// brick.cc : class de Brick et des sous-class de RainbowBrick, BallBrick et SplitBrick
//           version 1.0

#include "brick.h"

using namespace std;
// CONSTRUCTORS

static void draw_brick_recursive(const Cairo::RefPtr<Cairo::Context> &cr,
                                 double x, double y, double w, int level, Color color,
                                 Brick_list& split_brick_list)
{
    if (level <= 0) return;
    switch (level)
    { 
        case 7:
            color = PURPLE; break;
        case 6:
            color = BLUE; break;
        case 5:
            color = CYAN; break;
        case 4:
            color = GREEN; break;
        case 3:
            color = YELLOW; break;
        case 2:
            color = ORANGE; break;
        default:
            color = RED; break;
    }

    if (w >= brick_size_min)
    {
        unique_ptr<Brick> ptr(new RainbowBrick(x, y, w, level, 0));
        split_brick_list.push_back(move(ptr));
        draw_square(cr, x, y, w, color);
    }
    double next_w = (w-split_brick_gap)/2.0;
    double offset = (w+split_brick_gap)/4.0;

    if (next_w >= brick_size_min)
    {
        draw_brick_recursive(cr, x - offset, y + offset, next_w, level + 1, color, split_brick_list);
        draw_brick_recursive(cr, x + offset, y + offset, next_w, level + 1, color, split_brick_list); 
        draw_brick_recursive(cr, x - offset, y - offset, next_w, level + 1, color, split_brick_list);
        draw_brick_recursive(cr, x + offset, y - offset, next_w, level + 1, color, split_brick_list); 
    }
}

Brick::Brick(bool& error_occured, double x, double y, double width, int hit_points,
                                                                     int type)
    : square(x, y, width), type(type), hit_points(hit_points)
{
    check_brick_position(x, y, width, error_occured);
    check_brick_size(width, error_occured);
    check_brick_hit_points(hit_points, error_occured);
    check_brick_type(type, error_occured);

    color = get_color();
}

Brick::Brick(double x, double y, double width, int hit_points, int type)
    : square(x, y, width), type(type), hit_points(hit_points)
{}

 Brick::Brick(Brick const &old_brick)
     : square(old_brick.square), type(old_brick.type), 
                    hit_points(old_brick.hit_points)
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


Color Brick::get_color() const
{
    switch (hit_points)
    {
        case 7:
            return PURPLE;
            break;
        case 6:
            return BLUE;
            break;
        case 5:
            return CYAN;
            break;
        case 4:
            return GREEN;
            break;
        case 3:
            return YELLOW;
            break;
        case 2:
            return ORANGE;
            break;
        default:
            return RED;
            break;
    }
}

bool Brick::hit()
{
    --hit_points;
    if(hit_points<=0) return true;
    return false;
}

// RAINBOWBRICK

RainbowBrick::RainbowBrick(bool& error_occured, double x, double y, double width,
                                                         int hit_points, int type)
    : Brick(error_occured, x, y, width, hit_points, type)
{}

RainbowBrick::RainbowBrick(double x, double y, double width, int hit_points, int type)
    : Brick(x, y, width, hit_points, type) {}

void RainbowBrick::draw(const Cairo::RefPtr<Cairo::Context> &cr) const
{
    get_square().draw(cr, get_color());
}


// BALLBRICK

BallBrick::BallBrick(bool &error_occured, double x, double y, double width, 
                                                    int hit_points, int type)
    : Brick(error_occured, x, y, width, hit_points, type)
{
    hit_points = 1;
}

BallBrick::BallBrick(double x, double y, double width, int hit_points, int type)
    : Brick(x, y, width, hit_points, type)
{
    hit_points = 1;
}

void BallBrick::draw(const Cairo::RefPtr<Cairo::Context> &cr) const
{
    get_square().draw(cr, get_color());
    draw_circle(cr, get_x(), get_y(), new_ball_radius);
}


// SPLITBRICK

SplitBrick::SplitBrick(bool &error_occured, double x, double y, double width, 
                                                    int hit_points, int type)
    : Brick(error_occured, x, y, width, hit_points, type)
{}

SplitBrick::SplitBrick(double x, double y, double width, int hit_points, int type)
    : Brick(x, y, width, hit_points, type)
{}

void SplitBrick::draw(const Cairo::RefPtr<Cairo::Context> &cr) const
{
    Brick_list split_brick_list;
    double x = get_x();
    double y = get_y();
    double w = get_width();
    int level = 1;
    draw_brick_recursive(cr, x, y, w, level, color, split_brick_list);
}



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