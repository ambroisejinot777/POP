#include "paddle.h"

using namespace std;

using namespace message;

// CONSTRUCTEURS DE PADDLE

Paddle::Paddle(double x, double y, double r)
    : paddle_circle(x, y, r)
{
        check_paddle_y_axis(x, y, r);
        check_paddle_x_axis(x, y, r);
}

Paddle::Paddle(Paddle const &old_paddle)
    : paddle_circle(old_paddle.paddle_circle)
{}

Circle Paddle::get_circle() const
{
        return paddle_circle;
}

// FONCTIONS DE VERIFICATION DE SAISIE POUR PADDLE

void check_paddle_y_axis(double x, double y, double r)
{
        if ((y > 0) or ((y + r) <= 0))
        {
                error(paddle_outside(x, y));
        }
}

void check_paddle_x_axis(double x, double y, double r)
{
        if (((x - sqrt(r * r - y * y)) < 0) or ((x + sqrt(r * r - y * y)) > arena_size))
        {
                error(paddle_outside(x, y));
        }
}