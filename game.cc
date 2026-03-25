#include "game.h"

Game::Game() : paddle(), brick_list({}), ball_list({})
{
}

// GETTER AND SETTER

int Game::get_score() const
{
    return score;
}

int Game::get_lives() const
{
    return lives;
}

Paddle Game::get_paddle() const
{
    return paddle;
}

Brick_list Game::get_brick_list() const
{
    return brick_list;
}

Ball_list Game::get_ball_list() const
{
    return ball_list;
}

void Game::set_score(int new_score)
{
    score = new_score;
}

void Game::set_lives(int new_lives)
{
    lives = new_lives;
}

void Game::set_paddle(Paddle new_paddle)
{
    paddle = new_paddle;
}

void Game::add_brick(Brick new_brick)
{
    brick_list.push_back(new_brick);
}

void Game::add_ball(Ball new_ball)
{
    ball_list.push_back(new_ball);
}

// INIT AND CHECKING FUNCTIONS

void Game::init(string file_name)
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
            read_and_check_score(data);
            reading_state = LIVES;
            break;
        }

        case LIVES:
        {
            read_and_check_lives(data);
            reading_state = PADDLE;
            break;
        }

        case PADDLE:
        {
            read_and_check_paddle_data(data);
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
            read_and_check_brick_data(data, brick_counter);

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
            read_and_check_ball_data(data, ball_counter);

            if (++ball_counter >= nb_ball)
            {
                reading_state = FINISHED;
            }
            break;
        }

        case FINISHED:
        {
            break;
        }
        }
    }
    file.close();
    cout << message::success();
}

void Game::read_and_check_score(istringstream &data)
{
    data >> score;
    if (score < 0)
        error(message::invalid_score(score));
}

void Game::read_and_check_lives(istringstream &data)
{
    data >> lives;
    if (lives < 0)
        error(message::invalid_lives(lives));
}

void Game::read_and_check_paddle_data(istringstream &data)
{
    double paddle_x, paddle_y, paddle_radius;
    data >> paddle_x >> paddle_y >> paddle_radius;
    paddle = Paddle(paddle_x, paddle_y, paddle_radius);
}

void Game::read_and_check_brick_data(istringstream &data, unsigned int brick_counter)
{
    int type, hit_points;
    double brick_x, brick_y, brick_width;
    char left_bracket, right_bracket;
    data >> type >> brick_x >> brick_y >> brick_width >> left_bracket 
         >> hit_points >> right_bracket;
    Brick brick(brick_x, brick_y, brick_width, hit_points, type);

    if (circle_square_intersection(paddle.get_circle(), brick.get_square()))
        error(message::collision_paddle_brick(brick_counter));

    for (size_t i(0); i < brick_list.size(); i++)
    {
        if (square_square_intersection(brick_list[i].get_square(),
                                         brick.get_square()))
            error(message::collision_bricks(i, brick_counter));
    }

    add_brick(brick);
}

void Game::read_and_check_ball_data(istringstream &data, unsigned int ball_counter)
{
    double ball_x, ball_y, ball_radius, ball_dx, ball_dy;
    data >> ball_x >> ball_y >> ball_radius >> ball_dx >> ball_dy;
    Ball ball(ball_x, ball_y, ball_radius, ball_dx, ball_dy);

    if (circle_circle_intersection(ball.get_circle(), paddle.get_circle()))
        error(message::collision_paddle_ball(ball_counter));

    for (size_t i(0); i < ball_list.size(); i++)
    {
        if (circle_circle_intersection(ball_list[i].get_circle(), ball.get_circle()))
            error(message::collision_balls(i, ball_counter));
    }

    for (size_t i(0); i < brick_list.size(); i++)
    {
        if (circle_square_intersection(ball.get_circle(), brick_list[i].get_square()))
            error(message::collision_ball_brick(ball_counter, i));
    }

    add_ball(ball);
}
