#ifndef PADDLE_H
#define PADDLE_H
#include <iostream>
#include "tools.h"

class Paddle {
    public :
        Paddle (double x=0.0, double y=0.0, double r=0.0)
        : paddle_center(x, y), radius(r)
        {}
        Paddle (Paddle const& old_paddle)
        : paddle_center(old_paddle.paddle_center), radius(old_paddle.radius)
        {}
        
    private :
        Point paddle_center;
        double radius;       
};



#endif