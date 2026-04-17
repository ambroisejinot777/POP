#include "tools.h"

// UTILITY CLASSES

// POINT

Point::Point(double x, double y)
    : x(x), y(y) {}

Point::Point(Point const &old_point)
    : x(old_point.x), y(old_point.y) {}

double Point::get_x() const
{
    return x;
}

double Point::get_y() const
{
    return y;
}

void Point::set_x(double x)
{
    this->x = x;
}

void Point::set_y(double y)
{
    this->y = y;
}

// SQUARE

Square::Square(double x, double y, double w)
    : center(x, y), width(w) {}

Square::Square(Square const &old_square)
    : center(old_square.center), width(old_square.width) {}

double Square::get_x() const
{
    return center.get_x();
}

double Square::get_y() const
{
    return center.get_y();
}

double Square::get_width() const
{
    return width;
}

void Square::set_x(double x)
{
    center.set_x(x);
}

void Square::set_y(double y)
{
    center.set_y(y);
}

void Square::set_width(double w)
{
    width = w;
}

// CIRCLE

Circle::Circle(double x, double y, double r)
    : center(x, y), radius(r) {}

Circle::Circle(Circle const &old_circle)
    : center(old_circle.center), radius(old_circle.radius) {}

double Circle::get_x() const
{
    return center.get_x();
}

double Circle::get_y() const
{
    return center.get_y();
}

double Circle::get_radius() const
{
    return radius;
}

void Circle::set_x(double x)
{
    center.set_x(x);
}

void Circle::set_y(double y)
{
    center.set_y(y);
}

void Circle::set_radius(double r)
{
    radius = r;
}

// UTILITY FUNCTIONS

void display_error(string message, bool& error_occured)
{
    cout << message;
    error_occured=true;
}

// INTERSECTION FUNCTIONS
bool circle_circle_intersection(Circle const &c1, Circle const &c2)
{
    double distance = sqrt((c1.get_x() - c2.get_x()) * (c1.get_x() - c2.get_x()) +
                           (c1.get_y() - c2.get_y()) * (c1.get_y() - c2.get_y()));
    if ((distance - (c1.get_radius() + c2.get_radius())) < epsil_zero)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool circle_square_intersection(Circle const &c, Square const &s)
{
    double closest_x = max(s.get_x() - s.get_width() / 2,
             min(c.get_x(), s.get_x() + s.get_width() / 2));
    double closest_y = max(s.get_y() - s.get_width() / 2,
             min(c.get_y(), s.get_y() + s.get_width() / 2));

    double distance_x = c.get_x() - closest_x;
    double distance_y = c.get_y() - closest_y;

    double distance_squared = (distance_x * distance_x) + (distance_y * distance_y);
    bool check = (distance_squared - (c.get_radius() * c.get_radius())) < epsil_zero;
    return check;
}

bool square_square_intersection(Square const &s1, Square const &s2)
{
    double x_overlap = abs(s1.get_x() - s2.get_x()) - (s1.get_width() / 2 +
                                                       s2.get_width() / 2);
    double y_overlap = abs(s1.get_y() - s2.get_y()) - (s1.get_width() / 2 +
                                                       s2.get_width() / 2);
    if (x_overlap < epsil_zero and y_overlap < epsil_zero)
    {
        return true;
    }
    return false;
}