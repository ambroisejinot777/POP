#ifndef PADDLE_H
#define PADDLE_H
#include <iostream>
#include "tools.h"

class Paddle {
    public :
        Paddle (double x=0.0, double y=0.0, double r=0.0);
        Paddle (Paddle const& old_paddle);
        
    private :
        Point paddle_center;
        double radius;       
};



#endif