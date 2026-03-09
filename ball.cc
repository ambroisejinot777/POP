#include <iostream>
#include "ball.h"
#include "message.h"
#include "tools.h"

using namespace std;

void Ball::change_position() {
    associated_point.center_x += associated_point.delta_x;
    associated_point.center_y += associated_point.delta_y;
}
void change_delta() {
    switch (collision_type()) {
        case 1: // collision with a vertical wall
            vertical_wall_collision();
            break;
        case 2: // collision with a horizontal wall
            horizontal_wall_collision();
            break;
        case 3: // collision with a brick
            brick_collision();
            break;
        case 4: // collision with the paddle
            paddle_collision();
            break;
        case 5: // collision with another ball
            ball_collision();
            break;
        default:
            break; // no collision, do nothing
    }
}

bool Ball::check_invalid_delta();
bool Ball::check_ball_outside();
bool Ball::check_collision_balls();
bool Ball::check_collision_ball_brick();
bool Ball::check_collision_paddle_ball();
