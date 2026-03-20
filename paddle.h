#ifndef PADDLE_H
#define PADDLE_H

#include "message.h"
#include "tools.h"
#include "constants.h"

class Paddle
{
public:
    Paddle(double x = 0.0, double y = 0.0, double r = 0.0);
    Paddle(Paddle const &old_paddle);
    Circle get_circle() const;
    double get_x() const;
    double get_y() const;
    void set_x(double x);
    void set_y(double y);
private:
    Circle circle;
};

// CHECKING FUNCTIONS

void check_paddle_y_axis(double x, double y, double r);
void check_paddle_x_axis(double x, double y, double r);

#endif