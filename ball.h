#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <iostream>
#include "message.h"
#include "tools.h"

using namespace std;

class Ball
{
public:
    Ball(double x, double y, double r, double dx, double dy);
    Ball(Ball const &old_ball);
    double get_x() const;
    double get_y() const;
    double get_dx() const;
    double get_dy() const;
    double get_radius() const;

private:
    Circle circle;
    Point delta;
};


void check_ball_x_axis(double x, double y, double r);
void check_ball_y_axis(double x, double y, double r);
void check_ball_delta(double dx, double dy);

typedef vector<Ball*> Ball_list;



#endif