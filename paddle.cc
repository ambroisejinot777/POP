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

void Paddle::update_position(double new_x, Brick_list const &bricks)
{
    double min_x = half_paddle_width(get_x(), get_y(), get_radius());
    double max_x = arena_size - half_paddle_width(get_x(), get_y(), get_radius());
    
    if(new_x<min_x) set_x(min_x);
    else if (new_x > max_x) set_x(max_x);

    Circle temp_circle;
    temp_circle.set_x(new_x);
    temp_circle.set_y(get_y());
    temp_circle.set_radius(get_radius());

    for (const auto& brick: bricks)
    {
        if (circle_square_intersection(temp_circle, brick->get_square())) return;
    }


    et_x(new_x);
}

void Paddle::draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
    draw_circle(cr, get_x(), get_y(), get_radius());
    draw_circle(cr, get_x(), get_y(), get_radius()-paddle_thickness, WHITE);
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
        if ((x-half_paddle_width(x, y, r) < 0) or
            ((x + half_paddle_width(x, y, r)) > arena_size))
        {
            display_error(paddle_outside(x, y), error_occured);
        }
}