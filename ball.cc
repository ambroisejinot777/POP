#include "ball.h"

using namespace std;
using namespace message;

// CONSTRUCTEURS DE BALL

Ball::Ball(double x = 0.0, double y = 0.0, double r = 0.0, double dx = 0.0, double dy = 0.0)
    : circle(x, y, r), delta(dx, dy)
{
    check_ball_x_axis(x, y, r);
    check_ball_y_axis(x, y, r);
    check_ball_delta(dx, dy);
}

Ball::Ball(Ball const &old_ball)
    : circle(old_ball.circle), delta(old_ball.delta)
{
}

double Ball::get_x() const
{
    return circle.get_x();
}

double Ball::get_y() const
{
    return circle.get_y();
}

double Ball::get_dx() const
{
    return delta.get_x();
}

double Ball::get_radius() const
{
    return circle.get_radius();
}

double Ball::get_dy() const
{
    return delta.get_y();
}

// FONCTIONS D'ACTIONS DE BALL
void check_ball_x_axis(double x, double y, double r)
{
    if ((x < r) or (x > (arena_size - r)))
    {
        error(ball_outside(x, y));
    }
}

void check_ball_y_axis(double x, double y, double r)
{
    if ((y < 0) or (y > (arena_size - r)))
    {
        error(ball_outside(x, y));
    }
}

void check_ball_delta(double dx, double dy)
{
    if ((dx * dx + dy * dy) > (delta_norm_max * delta_norm_max))
    {
        error(invalid_delta(dx, dy));
    }
}
