#include <iostream>
#include "ball.h"
#include "message.h"
#include "tools.h"

using namespace std;

void Change_position() {
    associated_point.center_x += associated_point.delta_x;
    associated_point.center_y += associated_point.delta_y;
}
void Change_delta() {
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

bool Check_invalid_delta();
bool Check_ball_outside();
bool Check_collision_balls();
bool Check_collision_ball_brick();
bool Check_collision_paddle_ball();
