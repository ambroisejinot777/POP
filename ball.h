#ifndef BALL_H
#define BALL_H

#include <iostream>
#include "constants.h"

using namespace std;

class Ball {
    public :
        Ball ()
        : 
        {}
        Ball (double x=0.0, double y=0.0, double r=0.0, double dx=0.0, double dy=0.0)
        : Ball_center(x, y), Ball_delta(dx, dy), Ball_radius(r)
        {}
        Ball(Ball const& old_ball)
        : Ball_center(old_ball.Ball_center), Ball_delta(old_ball.Ball_delta), Ball_radius(old_ball.Ball_radius)
        {}
        bool check_invalid_delta();
        bool check_ball_outside();
        bool check_collision_balls();
        bool check_collision_ball_brick();
        bool check_collision_paddle_ball();

    private :
        Point Ball_center;
        Point Ball_delta;
        double Ball_radius;       
};


#endif