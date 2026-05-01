#ifndef TOOLS_H
#define TOOLS_H

// tools.h : module mathématiques avec des fonctions et des class
//            utilitaires
//            version 1.0 

#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <memory>

#include "graphic.h"

constexpr double epsil_zero(0.0);

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

    void draw(const Cairo::RefPtr<Cairo::Context> &cr, Color color);

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
    void draw(const Cairo::RefPtr<Cairo::Context> &cr, Color color);

private:
    Point center;
    double radius;
};

// ERROR FUNCTION 

void display_error(std::string message, bool& error_occured);

// CHECKING FUNCTIONS

bool circle_circle_intersection(Circle const &c1, Circle const &c2);
bool circle_square_intersection(Circle const &c, Square const &s);
bool square_square_intersection(Square const &s1, Square const &s2);

// BASIC ELEMENTS FUNCTION (avec le premier element correspondant a l'objet en 
// mouvement (la balle))

void circle_arena_segment_collision(); // with arena

void circle_circle_collision(); // with paddle and other ball 

void circle_brick_collision(); // with brick



#endif
