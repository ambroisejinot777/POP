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

