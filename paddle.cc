#include <iostream>
#include "paddle.h"
#include "message.h"

using namespace std;

Paddle::Paddle (double x=0.0, double y=0.0, double r=0.0)
        : paddle_center(x, y), radius(r)
        {}
Paddle::Paddle (Paddle const& old_paddle)
        : paddle_center(old_paddle.paddle_center), radius(old_paddle.radius)
        {}