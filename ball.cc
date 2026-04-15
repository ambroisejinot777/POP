#include "ball.h"

using namespace std;

// CONSTRUCTEURS DE BALL

Ball::Ball(bool& error_occured, double x, double y, double r, double dx, double dy)
    : circle(x, y, r), delta(dx, dy)
{
    check_ball_x_axis(x, y, r, error_occured);
    check_ball_y_axis(x, y, r, error_occured);
    check_ball_delta(dx, dy, error_occured);
}

Ball::Ball(Ball const &old_ball)
    : circle(old_ball.circle), delta(old_ball.delta)
{}

double Ball::get_x() const
{
    return circle.get_x();
}

double Ball::get_y() const
{
    return circle.get_y();
}

double Ball::get_radius() const
{
    return circle.get_radius();
}

double Ball::get_dx() const
{
    return delta.get_x();
}

double Ball::get_dy() const
{
    return delta.get_y();
}

Circle Ball::get_circle() const
{
    return circle;
}

// FONCTIONS D'ACTIONS DE BALL
void check_ball_x_axis(double x, double y, double r, bool& error_occured)
{
    if ((x < r) or (x > (arena_size - r)))
    {
        display_error(message::ball_outside(x, y), error_occured);
    }
}

void check_ball_y_axis(double x, double y, double r, bool& error_occured)
{
    if ((y < 0) or (y > (arena_size - r)))
    {
        display_error(message::ball_outside(x, y), error_occured);
    }
}

void check_ball_delta(double dx, double dy, bool& error_occured)
{
    if ((dx * dx + dy * dy) > (delta_norm_max * delta_norm_max))
    {
        display_error(message::invalid_delta(dx, dy), error_occured);
    }
}
