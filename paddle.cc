// paddle.h : class paddle avec des fnoction de verification des ses attributs
//            version 1.0 

#include <cmath>

#include "paddle.h"

using namespace message;
using namespace std;

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

double Paddle::get_radius() const
{
    return circle.get_radius();
}

void Paddle::set_x(double x)
{
    circle.set_x(x);
}
void Paddle::set_y(double y)
{
    circle.set_y(y);
}


void Paddle::draw(const Cairo::RefPtr<Cairo::Context> &cr) const
{
    double teta = acos(abs(get_y())/get_radius());
    double teta_min(M_PI/2-teta);
    double teta_max(M_PI/2+teta);
    cr->set_line_width(paddle_thickness);
    draw_arc(cr, get_x(), get_y(), get_radius()-paddle_thickness/2, teta_min, teta_max);
}


// FONCTIONS DE VERIFICATION DE SAISIE POUR PADDLE

double half_paddle_width(double x, double y, double r)
{
    return sqrt(r * r - y * y);
}

void check_paddle_y_axis(double x, double y, double r, bool &error_occured)
{
        if ((y > 0) or ((y + r) <= 0))
        {
            display_error(paddle_outside(x, y), error_occured);
        }
}

void check_paddle_x_axis(double x, double y, double r, bool& error_occured)
{
        if ((x-half_paddle_width(x, y, r) < epsil_zero) or
            ((x + half_paddle_width(x, y, r)) > arena_size-epsil_zero))
        {
            display_error(paddle_outside(x, y), error_occured);
        }
}