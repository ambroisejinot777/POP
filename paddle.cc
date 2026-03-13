#include "paddle.h"

using namespace std;

using namespace message;

// CONSTRUCTEURS DE PADDLE

Paddle::Paddle(double x = 0.0, double y = 0.0, double r = 0.0)
    : paddle_center(x, y), radius(r)
{
        check_y_axis(x, y, r);
        check_x_axis(x, y, r);
}

Paddle::Paddle(Paddle const &old_paddle)
    : paddle_center(old_paddle.paddle_center), radius(old_paddle.radius)
{
}

// FONCTIONS DE VERIFICATION DE SAISIE POUR PADDLE

void check_y_axis(double x, double y, double r)
{
        if ((y > 0) or ((y + r) <= 0))
        {
                error(paddle_outside(x, y));
        }
}

void check_x_axis(double x, double y, double r)
{
        if (((x - sqrt(r * r - y * y)) < 0) or ((x + sqrt(r * r - y * y)) > arena_size))
        {
                error(paddle_outside(x, y));
        }
}