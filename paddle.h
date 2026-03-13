#ifndef PADDLE_H
#define PADDLE_H

#include "message.h"
#include "tools.h"
#include "constants.h"

class Paddle
{
public:
    Paddle(double x, double y, double r);
    Paddle(Paddle const &old_paddle);

private:
    Point paddle_center;
    double radius;
};

void check_y_axis(double x, double y, double r);
void check_x_axis(double x, double y, double r);

#endif