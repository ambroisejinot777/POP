#ifndef TOOLS_H
#define TOOLS_H


class Point {
    public : 
    Point ()
        : center_x(0.0), center_y(0.0)
        {}
        Point (double x, double y)
        {}
    Point (double x=0.0, double y=0.0)
        : center_x(x), center_y(y)
        {} 
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

