#include <iostream>
#include "ball.h"
#include "message.h"

using namespace std;

void Change_position();
void Change_delta(); 

bool Check_invalid_delta();
bool Check_ball_outside();
bool Check_collision_balls();
bool Check_collision_ball_brick();
bool Check_collision_paddle_ball();
