#include "game.h"

Game::Game(string filename): score(0), lives(0), paddle_ptr(nullptr)
{
    init(filename);
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

const Paddle_ptr& Game::get_paddle() const
{
    return paddle_ptr;
}

const Brick_list& Game::get_brick_list() const
{
    return brick_list;
}

const Ball_list& Game::get_ball_list() const
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

void Game::set_paddle(Paddle_ptr new_paddle_ptr)
{
    paddle_ptr = move(new_paddle_ptr);
}

void Game::add_brick(Brick& new_brick)
{
    unique_ptr<Brick> ptr (new Brick(new_brick));
    brick_list.push_back(move(ptr));
}

void Game::add_ball(Ball& new_ball)
{
    unique_ptr<Ball> ptr (new Ball(new_ball));
    ball_list.push_back(move(ptr));
}

// INIT AND CHECKING FUNCTIONS

void Game::init(string file_name)
{

    ifstream file(file_name);

    if (file.fail())
    {
        cout << "Didn't find the file: " << file_name << endl;
        return;
    }

    string line;
    Reading_state reading_state(SCORE);
    unsigned int nb_brick;
    unsigned int brick_counter(0);
    unsigned int nb_ball;
    unsigned int ball_counter(0);

    bool error_occured(false);

    while (getline(file >> ws, line))
    {
        if (error_occured)
            return;

        istringstream data(line);

        if (line.empty() or line[0] == '#')
        {
            continue;
        }

        switch (reading_state)
        {

        case SCORE:
        {
            read_and_check_score(data, error_occured);
            reading_state = LIVES;
            break;
        }

        case LIVES:
        {
            read_and_check_lives(data, error_occured);
            reading_state = PADDLE;

            break;
        }

        case PADDLE:
        {
            read_and_check_paddle_data(data, error_occured);
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
            read_and_check_brick_data(data, brick_counter, error_occured);

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
            read_and_check_ball_data(data, ball_counter, error_occured);

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

void Game::read_and_check_score(istringstream &data, bool& error_occured)
{
    data >> score;
    
    if (score < 0)
    {
        display_error(message::invalid_score(score), error_occured);
    }
    
}

void Game::read_and_check_lives(istringstream &data, bool& error_occured)
{
    data >> lives;
    if (lives < 0)
    {
        display_error(message::invalid_lives(lives), error_occured);
    }
}

void Game::read_and_check_paddle_data(istringstream &data, bool& error_occured)
{
    double paddle_x, paddle_y, paddle_radius;
    data >> paddle_x >> paddle_y >> paddle_radius;
    paddle_ptr = make_unique<Paddle>(Paddle(error_occured, paddle_x, paddle_y, paddle_radius));
}

void Game::read_and_check_brick_data(istringstream &data, unsigned int brick_counter, bool& error_occured)
{
    int type, hit_points;
    double brick_x, brick_y, brick_width;
    data >> type >> brick_x >> brick_y >> brick_width;

    if (type == 1)
    {
        hit_points = 1;
    }
    else if (type ==2)
    {
        hit_points=resolve_hit_points_split_brick(brick_width);
    }
    else
    {
        data >> hit_points;
    }

    Brick brick(error_occured, brick_x, brick_y, brick_width, hit_points, type);

    if (circle_square_intersection(paddle_ptr->get_circle(), brick.get_square()))
    {
        display_error(message::collision_paddle_brick(brick_counter), error_occured);
    }
    for (size_t i(0); i < brick_list.size(); i++)
    {
        if (square_square_intersection(brick_list[i]->get_square(),
                                         brick.get_square()))
        {
            display_error(message::collision_bricks(i, brick_counter), error_occured);
        }
    }

    add_brick(brick);
}

void Game::read_and_check_ball_data(istringstream &data, unsigned int ball_counter, bool& error_occured)
{
    double ball_x, ball_y, ball_radius, ball_dx, ball_dy;
    data >> ball_x >> ball_y >> ball_radius >> ball_dx >> ball_dy;
    Ball ball(error_occured, ball_x, ball_y, ball_radius, ball_dx, ball_dy);

    if (circle_circle_intersection(ball.get_circle(), paddle_ptr->get_circle()))
    {
        display_error(message::collision_paddle_ball(ball_counter), error_occured);
    }

    for (size_t i(0); i < ball_list.size(); i++)
    {
        if (circle_circle_intersection(ball_list[i]->get_circle(), ball.get_circle()))
        {
            display_error(message::collision_balls(i, ball_counter), error_occured);
        }
    }

    for (size_t i(0); i < brick_list.size(); i++)
    {
        if (circle_square_intersection(ball.get_circle(), brick_list[i]->get_square()))
        {
            display_error(message::collision_ball_brick(ball_counter, i), error_occured);
        }
    }

    add_ball(ball);
}

void Game::update_balls_data()
{
    for (const auto& ball: ball_list)
    {
        ball->update_position();
    }
}

int Game::resolve_hit_points_split_brick(double w)
{
    int brick_width(w);
    int hit_points(1);

    while (brick_width >= brick_size_min)
    {
        brick_width = (brick_width - split_brick_gap)/2;
        ++hit_points;
    }
    return hit_points;
}

