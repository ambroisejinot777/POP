#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <iostream>
#include <cmath>
#include <vector>

#include "constants.h"

using namespace std;

class Point
{
public:
    Point(double x = 0.0, double y = 0.0);
    Point(Point const &old_point);
    double get_x() const;
    double get_y() const;

private:
    double center_x;
    double center_y;
};

class Square 
{
public:
    Square(double x = 0.0, double y = 0.0, double w = 0.0);
    Square(Square const &old_square);
    double get_x() const;
    double get_y() const;
    double get_width() const;

private:
    Point square_center;
    double width;
};

class Circle
{
public:
    Circle(double x = 0.0, double y = 0.0, double r = 0.0);
    Circle(Circle const &old_circle);
    double get_x() const;
    double get_y() const;
    double get_radius() const;

private:
    Point circle_center;
    double radius;
};

void error(string message);

bool circle_circle_intersection(Circle const &c1, Circle const &c2);
bool circle_square_intersection(Circle const &c, Square const &s);
bool square_square_intersection(Square const &s1, Square const &s2);

#endif
