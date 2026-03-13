#include "game.h"

void start_project(string file_name)
{

    ifstream file(file_name);

    if (file.fail())
    {
        cout << "Cannot open the file: " << file_name << endl;
        return;
    }

    string line;
    Reading_state reading_state(SCORE);
    int nb_brick;
    int brick_counter(1);
    int nb_ball;
    int ball_counter(1);

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
            int score = check_score(data);
            reading_state = LIVES;
            break;
        }

        case LIVES:
        {
            int lives = check_lives(data);
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
            int type, hit_points;
            double brick_x, brick_y, brick_width;
            char left_bracket, right_bracket;
            data >> type >> brick_x >> brick_y >> brick_width >> left_bracket >> hit_points >> right_bracket;

            Brick brick(brick_x, brick_y, brick_width, hit_points, type);

            if (brick_counter >= nb_brick)
            {
                reading_state = NB_BALL;
            }
            ++brick_counter;
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
            double ball_x, ball_y, ball_radius, ball_dx, ball_dy;
            data >> ball_x >> ball_y >> ball_radius >> ball_dx >> ball_dy;

            Ball ball(ball_x, ball_y, ball_radius, ball_dx, ball_dy);

            if (ball_counter >= nb_ball)
            {
                reading_state = FINISHED;
            }
            ++ball_counter;
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

int check_score(istringstream data)
{
    int score;
    data >> score;
    if (score < 0)
        error(message::invalid_score(score));
    return score;
}

int check_lives(istringstream data)
{
    int lives;
    data >> lives;
    if (lives < 0)
        error(message::invalid_lives(lives));
    return lives;
}