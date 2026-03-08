#ifndef BALL_H
#define BALL_H

#include <iostream>

using namespace std;

class Point {
    public : 
        Point ()
        : center_x(0.0), center_y(0.0), radius(0.0), delta_x(0.0), delta_y(0.0)
        {}
        Point (double x, double y, double r, double dx, double dy)
        {
          center_x = x;
          center_y = y;
          radius = r;
          delta_x = dx;  
          delta_y = dy;
        }
        Point (double x=0.0, double y=0.0, double r=0.0, double dx=0.0, double dy=0.0)
        {
          center_x = x;
          center_y = y;
          radius = r;
          delta_x = dx;  
          delta_y = dy;
        }
        Point(Point const& nouv_point)
        : center_x(nouv_point.center_x), center_y(nouv_point.center_y), radius(nouv_point.radius), delta_x(nouv_point.delta_x), delta_y(nouv_point.delta_y)
        {}
        void Change_position();
        void Change_delta();

    private :
        double center_x;
        double center_y;
        double radius;
        double delta_x; 
        double delta_y;
};
class Ball {
    public :
        Ball ()
        : associated_point()
        {}
        Ball (double x, double y, double r, double dx, double dy)
        : associated_point(x, y, r, dx, dy)
        {}
        Ball (double x=0.0, double y=0.0, double r=0.0, double dx=0.0, double dy=0.0)
        : associated_point(x, y, r, dx, dy)
        {}
        Ball(Ball const& nouv_ball)
        : associated_point(nouv_ball.associated_point)
        {}
        bool Check_invalid_delta();
        bool Check_ball_outside();
        bool Check_collision_balls();
        bool Check_collision_ball_brick();
        bool Check_collision_paddle_ball();

    private :
        Point associated_point;
        
};


#endif