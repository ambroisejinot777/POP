#include <iostream>
#include "ball.h"
#include "message.h"
#include "tools.h"

using namespace std;

// CONSTRUCTEURS DE BALL

Ball::Ball(double x=0.0, double y=0.0, double r=0.0, double dx=0.0, double dy=0.0)
        : ball_center(x, y), ball_delta(dx, dy), ball_radius(r)
        {}

Ball::Ball(Ball const& old_ball)
        : ball_center(old_ball.ball_center), ball_delta(old_ball.ball_delta), ball_radius(old_ball.ball_radius)
        {}

// FONCTIONS DE VERIFICATION DE SAISIE POUR BALL



// FONCTIONS D'ACTIONS DE BALL

void change_position() {
        // code to change the position of the ball based on its current delta
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

bool check_invalid_delta();
bool check_ball_outside();
bool check_collision_balls();
bool check_collision_ball_brick();
bool check_collision_paddle_ball();
