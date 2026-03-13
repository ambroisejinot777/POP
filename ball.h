#ifndef BALL_H
#define BALL_H

#include <iostream>
#include "constants.h"

using namespace std;

class Ball {
    public :
        Ball (double x, double y, double r, double dx, double dy);
        Ball(Ball const& old_ball);

    private :
        Point center;
        Point delta;
        double radius;       
};


#endif