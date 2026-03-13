#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <iostream>


using namespace std;


class Point {
    public : 
    Point (double x, double y);

    Point(Point const& old_point);
    private :
        double center_x;
        double center_y;
};

class Square {
    public : 
    Square (double x, double y, double w, double h);
    Square (Square const& old_square);
        
    private :
        Point square_center;
        double width;
        double height;
};

class Circle {
    public : 
        Circle (double x, double y, double r);
        Circle (Circle const& old_circle);

    private :
        Point circle_center;
        double radius;
};

void error(string message);

bool circle_circle_intersection(Circle const& c1, Circle const& c2);
bool circle_square_intersection(Circle const& c, Square const& s);
bool square_square_intersection(Square const& s1, Square const& s2);


#endif

