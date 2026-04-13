#ifndef BRICK_H
#define BRICK_H

#include "message.h"
#include "tools.h"

// BRICK CLASS

class Brick
{

public:
    Brick(bool& error_occured, double x = 0.0, double y = 0.0, double width = 0.0,
         int hit_points = 0, int type = 0);
    // Brick(Brick const &old_brick) = 0;
    double get_x() const;
    double get_y() const;
    Square get_square() const;

private:
    Square square;
    int hit_points;
    int type;
};

typedef vector<unique_ptr<Brick>>  Brick_list;


// CHECKING FUNCTIONS

void check_brick_position(double x, double y, double width, bool& error_occured);
void check_brick_size(double width, bool& error_occured);
void check_brick_hit_points(int hit_points, bool& error_occured);
void check_brick_type(int type, bool& error_occured);

#endif