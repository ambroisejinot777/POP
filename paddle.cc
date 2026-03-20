#include "paddle.h"

using namespace std;

using namespace message;

// CONSTRUCTEURS DE PADDLE

Paddle::Paddle(double x, double y, double r)
    : circle(x, y, r)
{
    check_paddle_y_axis(x, y, r);
    check_paddle_x_axis(x, y, r);
}

Paddle::Paddle(Paddle const &old_paddle)
    : circle(old_paddle.circle)
{}

Circle Paddle::get_circle() const
{
    return circle;
}

double Paddle::get_x() const
{
    return circle.get_x();
}

double Paddle::get_y() const
{
    return circle.get_y();
}
void Paddle::set_x(double x)
{
    circle.set_x(x);
}
void Paddle::set_y(double y)
{
    circle.set_y(y);
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
        if (((x - sqrt(r * r - y * y)) < 0) or
            ((x + sqrt(r * r - y * y)) > arena_size))
        {
                error(paddle_outside(x, y));
        }
}