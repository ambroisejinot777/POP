#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <iostream>
#include "message.h"
#include "tools.h"

using namespace std;

class Ball
{
public:
    Ball(bool& error_occured, double x = 0.0, double y = 0.0, double r = 0.0,
         double dx = 0.0, double dy = 0.0);
    Ball(Ball const &old_ball);
    double get_x() const;
    double get_y() const;
    double get_dx() const;
    double get_dy() const;
    double get_radius() const;
    Circle get_circle() const;
    void update_position();
    void draw(const Cairo::RefPtr<Cairo::Context> &cr) const;

private:
    Circle circle;
    Point delta;
};


typedef vector<unique_ptr<Ball>> Ball_list;

// CHECKING FUNCTIONS

void check_ball_x_axis(double x, double y, double r, bool& error_occured);
void check_ball_y_axis(double x, double y, double r, bool& error_occured);
void check_ball_delta(double dx, double dy, bool& error_occured);





#endif