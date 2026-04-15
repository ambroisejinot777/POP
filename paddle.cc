#include "paddle.h"

using namespace std;

using namespace message;

// CONSTRUCTEURS DE PADDLE

Paddle::Paddle(bool& error_occured, double x, double y, double r)
    : circle(x, y, r)
{
    check_paddle_y_axis(x, y, r, error_occured);
    check_paddle_x_axis(x, y, r, error_occured);
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

void check_paddle_y_axis(double x, double y, double r, bool& error_occured)
{
        if ((y > 0) or ((y + r) <= 0))
        {
            display_error(paddle_outside(x, y), error_occured);
        }
}

void check_paddle_x_axis(double x, double y, double r, bool& error_occured)
{
        if (((x - sqrt(r * r - y * y)) < 0) or
            ((x + sqrt(r * r - y * y)) > arena_size))
        {
            display_error(paddle_outside(x, y), error_occured);
        }
}