#ifndef TOOLS_H
#define TOOLS_H


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
    void change_position(Point& associated_point);
    void change_delta(Point& associated_point);
        
    private :
        double center_x;
        double center_y;
};

class Square {
    public : 
        
    private :
        Point square_center;
        double width;
        double height;
};

class Circle {
    public : 
        
    private :
        Point circle_center;
        double radius;
};

int collision_type() ;
void vertical_wall_collision();
void horizontal_wall_collision();
void brick_collision();
void paddle_collision();
void ball_collision();

#endif

