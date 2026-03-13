#include "brick.h"
#include "message.h"

// CONSTRUCTORS

Brick::Brick(double x = 0.0, double y = 0.0, double width = 0.0, int hit_points = 0, Brick_type type = DEFAULT)
    : square(x, y, width), hit_points(hit_points), type(type) {}

Brick::Brick(Brick const &old_brick)
    : square(old_brick.square), hit_points(old_brick.hit_points), type(old_brick.type) {}