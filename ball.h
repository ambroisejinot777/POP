#include <iostream>

using namespace std;

class Point {
    public : 
        void Change_position();
        void Change_delta();

    private :
        double center_x;
        double center_y;
        double radius;
        double delta; 
};
class Ball {
    public : 
        bool Check_invalid_delta();
        bool Check_ball_outside();
        bool Check_collision_balls();
        bool Check_collision_ball_brick();
        bool Check_collision_paddle_ball();

    private :
        
};