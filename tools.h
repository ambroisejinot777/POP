#ifndef TOOLS_H
#define TOOLS_H


class Point {
    public : 
    Point (double x=0.0, double y=0.0)
        : center_x(x), center_y(y)
        {} 
    Point(Point const& old_point)
        : center_x(old_point.center_x), center_y(old_point.center_y)
        {}
    private :
        double center_x;
        double center_y;
};

class Square {
    public : 
    Square (double x=0.0, double y=0.0, double w=0.0, double h=0.0)
        : square_center(x, y), width(w), height(h)
        {} 
    Square (Square const& old_square)
        : square_center(old_square.square_center), width(old_square.width), height(old_square.height)
        {}
        
    private :
        Point square_center;
        double width;
        double height;
};

class Circle {
    public : 
    Circle (double x=0.0, double y=0.0, double r=0.0)
        : circle_center(x, y), radius(r)
        {} 
    Circle (Circle const& old_circle)
        : circle_center(old_circle.circle_center), radius(old_circle.radius)
        {}
        
    private :
        Point circle_center;
        double radius;
};

bool circle_circle_intersection(Circle const& c1, Circle const& c2);
bool circle_square_intersection(Circle const& c, Square const& s);
bool square_square_intersection(Square const& s1, Square const& s2);

int collision_type() ;
void vertical_wall_collision();
void horizontal_wall_collision();
void brick_collision();
void paddle_collision();
void ball_collision();

#endif

