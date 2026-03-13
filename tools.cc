#include "tools.h"



// UTILITY CLASSES

// POINT

Point::Point (double x=0.0, double y=0.0)
    :center_x(x), center_y(y){} 
    
Point::Point(Point const& old_point)
    :center_x(old_point.center_x), center_y(old_point.center_y){}

// SQUARE

Square::Square (double x=0.0, double y=0.0, double w=0.0, double h=0.0)
    : square_center(x, y), width(w), height(h){} 

Square::Square (Square const& old_square)
    : square_center(old_square.square_center), width(old_square.width), height(old_square.height){}

// CIRCLE

Circle::Circle(double x=0.0, double y=0.0, double r=0.0)
    :circle_center(x, y), radius(r){} 

Circle::Circle (Circle const& old_circle)
    :circle_center(old_circle.circle_center), radius(old_circle.radius){}


void error(string message){
    cout << message << endl;
    exit(0);
}