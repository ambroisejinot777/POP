#ifndef PADDLE_H
#define PADDLE_H

#include "message.h"
#include "tools.h"
#include "constants.h"

class Paddle
{
public:
    Paddle(bool& error_occured, double x = 50.0, double y = -10.0, double r = 15.0);
    Paddle(Paddle const &old_paddle);
    Circle get_circle() const;
    double get_x() const;
    double get_y() const;
    double get_radius() const;
    void set_x(double x);
    void set_y(double y);
    void update_position(double x, Brick_list const &bricks);
    void draw(const Cairo::RefPtr<Cairo::Context> &cr);
    
private : 
    Circle circle;

    
};

typedef unique_ptr<Paddle> Paddle_ptr; 

// CHECKING FUNCTIONS

double half_paddle_width(double x, double y, double r);
void check_paddle_y_axis(double x, double y, double r, bool& error_occured);
void check_paddle_x_axis(double x, double y, double r, bool& error_occured);

#endif