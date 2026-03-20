#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <iostream>
#include <cmath>
#include <vector>

#include "constants.h"

using namespace std;

// POINT

class Point
{
public:
    Point(double x = 0.0, double y = 0.0);
    Point(Point const &old_point);
    double get_x() const;
    double get_y() const;
    void set_x(double x);
    void set_y(double y);

private:
    double x;
    double y;
};

// SQUARE

class Square
{
public:
    Square(double x = 0.0, double y = 0.0, double w = 0.0);
    Square(Square const &old_square);
    double get_x() const;
    double get_y() const;
    double get_width() const;
    void set_x(double x);
    void set_y(double y);
    void set_width(double w);

private:
    Point center;
    double width;
};

// CIRCLE

class Circle
{
public:
    Circle(double x = 0.0, double y = 0.0, double r = 0.0);
    Circle(Circle const &old_circle);
    double get_x() const;
    double get_y() const;
    double get_radius() const;
    void set_x(double x);
    void set_y(double y);
    void set_radius(double r);

private:
    Point center;
    double radius;
};

void error(string message);

// CHECKING FUNCTIONS

bool circle_circle_intersection(Circle const &c1, Circle const &c2);
bool circle_square_intersection(Circle const &c, Square const &s);
bool square_square_intersection(Square const &s1, Square const &s2);

#endif
