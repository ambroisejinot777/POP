#ifndef PADDLE_H
#define PADDLE_H
#include <iostream>
#include "tools.h"

class Paddle {
    public :
        Paddle (double x, double y, double r);
        Paddle (Paddle const& old_paddle);
        
    private :
        Point paddle_center;
        double radius;       
};



#endif