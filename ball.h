#ifndef BALL_H
#define BALL_H

#include <iostream>
#include "constants.h"

using namespace std;

class Point {
    public : 
        Point ()
        : center_x(0.0), center_y(0.0), radius(0.0), delta_x(0.0), delta_y(0.0)
        {}
        Point (double x, double y, double r, double dx, double dy)
        {
          if (x >= 0 && x <= arena_size) {
            center_x = x;
          }
          else {
            cout << message::ball_outside(x, y) << endl;
          }
          if (y >= 0 && y <= arena_size) {
            center_y = y;
          }
          else {
            cout << message::ball_outside(x, y) << endl;
          }
          if (r == 1.)  {
            radius = r;
          }
          else {
            cout << "Rayon de balle mauvais" << endl;
          }
          delta_x = dx;  
          delta_y = dy;
        }
        Point (double x=0.0, double y=0.0, double r=0.0, double dx=0.0, double dy=0.0)
        : center_x(x), center_y(y), radius(r), delta_x(dx), delta_y(dy)
        {
            if (x >= 0 && x <= 1) {
                center_x = x;
            }
            else {
                cout << message::ball_outside(x, y) << endl;
            }
            if (y >= 0 && y <= arena_size) {
                center_y = y;
            }
            else {
                cout << message::ball_outside(x, y) << endl;
            }
            if (r == 1.)  {
                radius = r;
            }
            else {
                cout << "Rayon de balle mauvais" << endl;
            }
            delta_x = dx;  
            delta_y = dy;
        }
        Point(Point const& old_point)
        : center_x(old_point.center_x), center_y(old_point.center_y), radius(old_point.radius), delta_x(old_point.delta_x), delta_y(old_point.delta_y)
        {}
        void change_position();
        void change_delta();

    private :
        Point Ball_center;
        Point Ball_delta;
        double Ball_radius;
        
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
        Ball(Ball const& old_ball)
        : associated_point(old_ball.associated_point)
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