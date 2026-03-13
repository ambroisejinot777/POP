#include "tools.h"

// UTILITY CLASSES

// POINT

Point::Point(double x = 0.0, double y = 0.0)
    : center_x(x), center_y(y) {}

Point::Point(Point const &old_point)
    : center_x(old_point.center_x), center_y(old_point.center_y) {}

double Point::get_x() const
{
    return center_x;
}

double Point::get_y() const
{
    return center_y;
}

// SQUARE

Square::Square(double x = 0.0, double y = 0.0, double w = 0.0)
    : square_center(x, y), width(w) {}

Square::Square(Square const &old_square)
    : square_center(old_square.square_center), width(old_square.width) {}

double Square::get_x() const
{
    return square_center.get_x();
}

double Square::get_y() const
{
    return square_center.get_y();
}

double Square::get_width() const
{
    return width;
}

// CIRCLE

Circle::Circle(double x = 0.0, double y = 0.0, double r = 0.0)
    : circle_center(x, y), radius(r) {}

Circle::Circle(Circle const &old_circle)
    : circle_center(old_circle.circle_center), radius(old_circle.radius) {}

double Circle::get_x() const
{
    return circle_center.get_x();
}

double Circle::get_y() const
{
    return circle_center.get_y();
}

double Circle::get_radius() const
{
    return radius;
}

// UTILITY FUNCTIONS

void error(string message)
{
    cout << message;
    exit(1);
}

// INTERSECTION FUNCTIONS
bool circle_circle_intersection(Circle const &c1, Circle const &c2)
{
    double distance = sqrt((c1.get_x() - c2.get_x()) * (c1.get_x() - c2.get_x()) + (c1.get_y() - c2.get_y()) * (c1.get_y() - c2.get_y()));
    if (distance < (c1.get_radius() + c2.get_radius()))
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
    double closest_x = max(s.get_x() - s.get_width() / 2, min(c.get_x(), s.get_x() + s.get_width() / 2));
    double closest_y = max(s.get_y() - s.get_width() / 2, min(c.get_y(), s.get_y() + s.get_width() / 2));
    double distance = sqrt(pow(c.get_x() - closest_x, 2) + pow(c.get_y() - closest_y, 2));
    return distance < c.get_radius();
}

bool square_square_intersection(Square const &s1, Square const &s2)
{
    bool x_overlap = abs(s1.get_x() - s2.get_x()) < (s1.get_width() / 2 + s2.get_width() / 2);
    bool y_overlap = abs(s1.get_y() - s2.get_y()) < (s1.get_width() / 2 + s2.get_width() / 2);
    return x_overlap && y_overlap;
}