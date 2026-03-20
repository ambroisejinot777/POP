#include "game.h"


void start_project(string file_name, Brick_list &brick_list, Ball_list &ball_list, int &score, int &lives)
{

    ifstream file(file_name);

    if (file.fail())
    {
        cout << "Cannot open the file: " << file_name << endl;
        return;
    }

    string line;
    Reading_state reading_state(SCORE);
    unsigned int nb_brick;
    unsigned int brick_counter(0);
    unsigned int nb_ball;
    unsigned int ball_counter(0);

    while (getline(file >> ws, line))
    {

        istringstream data(line);

        if (line.empty() or line[0] == '#')
        {
            continue;
        }

        switch (reading_state)
        {

        case SCORE:
        {
            score = check_score(data);
            reading_state = LIVES;
            break;
        }

        case LIVES:
        {
            lives = check_lives(data);
            reading_state = PADDLE;
            break;
        }

        case PADDLE:
        {
            double paddle_x, paddle_y, paddle_radius;
            data >> paddle_x >> paddle_y >> paddle_radius;
            Paddle paddle(paddle_x, paddle_y, paddle_radius);
            reading_state = NB_BRICK;
            break;
        }

        case NB_BRICK:
        {
            data >> nb_brick;
            reading_state = BRICKS;
            break;
        }

        case BRICKS:
        {
            read_and_check_brick_data(data, brick_list, brick_counter);

            if (++brick_counter >= nb_brick)
            {
                reading_state = NB_BALL;
            }
            break;
        }

        case NB_BALL:
        {
            data >> nb_ball;
            reading_state = BALLS;
            break;
        }

        case BALLS:
        {
            read_and_check_ball_data(data, ball_list, ball_counter);

            if (++ball_counter >= nb_ball)
            {
                reading_state = FINISHED;
            }
            break;
        }

        case FINISHED:
        {
            // cout << "Reading part is finished" << endl;
            break;
        }
        }
    }

    file.close();
}

int check_score(istringstream &data)
{
    int score;
    data >> score;
    if (score < 0)
        error(message::invalid_score(score));
    return score;
}

int check_lives(istringstream &data)
{
    int lives;
    data >> lives;
    if (lives < 0)
        error(message::invalid_lives(lives));
    return lives;
}

void read_and_check_brick_data(istringstream &data, Brick_list &brick_list, int brick_counter)
{
    int type, hit_points;
    double brick_x, brick_y, brick_width;
    char left_bracket, right_bracket;
    data >> type >> brick_x >> brick_y >> brick_width >> left_bracket >> hit_points >> right_bracket;
    Brick brick(brick_x, brick_y, brick_width, hit_points, type);

    for (size_t i(0); i < brick_list.size(); i++)
    {
        if (square_square_intersection(brick_list[i].get_square(), brick.get_square()))
            error(message::collision_bricks(i, brick_counter));
    }

    brick_list.push_back(brick);
}

void read_and_check_ball_data(istringstream &data, Ball_list &ball_list, unsigned int ball_counter)
{
    double ball_x, ball_y, ball_radius, ball_dx, ball_dy;
    data >> ball_x >> ball_y >> ball_radius >> ball_dx >> ball_dy;
    Ball ball(ball_x, ball_y, ball_radius, ball_dx, ball_dy);

    for (size_t i(0); i < ball_list.size(); i++)
    {
        if (circle_circle_intersection(ball_list[i].get_circle(), ball.get_circle()))
            error(message::collision_balls(i, ball_counter));
    }

    ball_list.push_back(ball);
}
