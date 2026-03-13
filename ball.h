#ifndef BALL_H
#define BALL_H

#include <iostream>
#include "constants.h"

using namespace std;

class Ball {
    public :
        Ball (double x=0.0, double y=0.0, double r=0.0, double dx=0.0, double dy=0.0);
        Ball(Ball const& old_ball);
        bool check_invalid_delta();
        bool check_ball_outside();
        bool check_collision_balls();
        bool check_collision_ball_brick();
        bool check_collision_paddle_ball();

    private :
        Point ball_center;
        Point ball_delta;
        double ball_radius;       
};


#endif