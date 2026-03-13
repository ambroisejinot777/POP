#include <iostream>
#include <cmath>
#include "ball.h"
#include "message.h"
#include "tools.h"

using namespace std;
using namespace message;

// CONSTRUCTEURS DE BALL

Ball::Ball(double x = 0.0, double y = 0.0, double r = 0.0, double dx = 0.0, double dy = 0.0)
    : center(x, y), delta(dx, dy), radius(r)
{
    if ((x < r) and (x > (arena_size - r)))
    {
        error(ball_outside(x, y));
    }

    if ((y < 0) and (y > (arena_size - r)))
    {
        error(ball_outside(x, y));
    }

    if ((sqrt(dx * dx + dy * dy)) > (delta_norm_max))
    {
        error(invalid_delta(dx, dy));
    }
}

Ball::Ball(Ball const &old_ball)
    : center(old_ball.center), delta(old_ball.delta), radius(old_ball.radius)
{
}

// FONCTIONS D'ACTIONS DE BALL
