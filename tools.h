#ifndef TOOLS_H
#define TOOLS_H


class Point {
    public : 
        
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

