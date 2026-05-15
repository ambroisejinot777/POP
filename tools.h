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

constexpr double epsil_zero(0.125);

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

// UTILITY FUNCTIONS

void display_error(std::string message, bool& error_occured);
double compute_norm(Point& point);
double dot_product(Point const& a, Point const& b);

// INTERSECTION FUNCTIONS

bool circle_circle_intersection(Circle const &c1, Circle const &c2);
bool circle_square_intersection(Circle const &c, Square const &s);
bool square_square_intersection(Square const &s1, Square const &s2);

















// BASIC ELEMENTS FUNCTION (avec le premier element correspondant a l'objet en 
// mouvement (la balle))

double circle_circle_impulse(Circle const& c1, double dx1, double dy1,
                             Circle const& c2, double dx2, double dy2,
                             bool isPaddle = false);

double circle_circle_newdeltax(double dx,  double dy,  double radius,
                               double dx2, double dy2, double radius2,
                               double nx,  double ny);

double circle_circle_newdeltay(double dx,  double dy,  double radius,
                               double dx2, double dy2, double radius2,
                               double nx,  double ny);

double circle_segment_point_newdeltax(double dx, double dy,
                                double nx, double ny);

double circle_segment_point_newdeltay(double dx, double dy,
                                double nx, double ny);


void get_brick_collision_normal(double ball_x, double ball_y,
                                double brick_x, double brick_y, double brick_width,
                                double& nx, double& ny);










                                    

#endif
