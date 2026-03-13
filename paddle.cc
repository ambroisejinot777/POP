#include "paddle.h"




using namespace std;

using namespace message;

// CONSTRUCTEURS DE PADDLE

Paddle::Paddle(double x = 0.0, double y = 0.0, double r = 0.0)
    : paddle_center(x, y), radius(r)
{
        if ((y > 0) or ((y + r) <= 0))
        {
                error(paddle_outside(x, y));
        }

        if ((y < 0) and (y > (arena_size - r)))
        {
                error(paddle_outside(x, y));
        }
}

Paddle::Paddle(Paddle const &old_paddle)
    : paddle_center(old_paddle.paddle_center), radius(old_paddle.radius)
{
}

// FONCTIONS DE VERIFICATION DE SAISIE POUR PADDLE
