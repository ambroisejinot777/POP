#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <iostream>
#include <cmath>

#include "message.h"
#include "tools.h"

using namespace std;

class Ball
{
public:
    Ball(double x, double y, double r, double dx, double dy);
    Ball(Ball const &old_ball);

private:
    Point center;
    Point delta;
    double radius;
};

void check_x_axis(double x, double y, double r);
void check_y_axis(double x, double y, double r);
void check_delta(double dx, double dy);

#endif