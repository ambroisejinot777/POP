#include "ball.h"

using namespace std;
using namespace message;

// CONSTRUCTEURS DE BALL

Ball::Ball(double x = 0.0, double y = 0.0, double r = 0.0, double dx = 0.0, double dy = 0.0)
    : center(x, y), delta(dx, dy), radius(r)
{
    check_ball_x_axis(x, y, r);
    check_ball_y_axis(x, y, r);
    check_ball_delta(dx, dy);
}

Ball::Ball(Ball const &old_ball)
    : center(old_ball.center), delta(old_ball.delta), radius(old_ball.radius)
{
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
    if ((sqrt(dx * dx + dy * dy)) > (delta_norm_max))
    {
        error(invalid_delta(dx, dy));
    }
}
