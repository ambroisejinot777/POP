// game.cc : class de game
//           version 1.0

#include "game.h"

using namespace std;

// PUBLIC FUNCTIONS

Game::Game(string filename): score(0), lives(0), paddle_ptr(nullptr)
{
    init(filename);
}

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

string Game::get_file() const
{
    return filename;
}

bool Game::get_error() const
{
    return error_occured;
}

double Game::get_mouse_x() const
{
    return mouse_x;
}

void Game::set_mouse_x(double new_x)
{
    mouse_x = new_x;
}

void Game::add_brick(unique_ptr<Brick> ptr)
{
    brick_list.push_back(move(ptr));
}

void Game::add_ball(Ball& new_ball)
{
    unique_ptr<Ball> ptr (new Ball(new_ball));
    ball_list.push_back(move(ptr));
}

void Game::update_paddle_position(double new_x)
{
    if(paddle_ptr == nullptr) return;

    double current_x = paddle_ptr->get_x();
    double delta = new_x - current_x;
    if (delta > delta_norm_max)  new_x = current_x + delta_norm_max;
    if (delta < -delta_norm_max) new_x = current_x - delta_norm_max;

    double min_x = half_paddle_width(paddle_ptr->get_x(), paddle_ptr->get_y(), 
                                                            paddle_ptr->get_radius());
    double max_x = arena_size - half_paddle_width(paddle_ptr->get_x(), 
                                    paddle_ptr->get_y(), paddle_ptr->get_radius());
    
    if(new_x<min_x) 
    {
        paddle_ptr->set_x(min_x);
        return;
    }
    else if (new_x > max_x)
    {
        paddle_ptr->set_x(max_x);
        return;
    }

    Circle temp_circle;
    temp_circle.set_x(new_x);
    temp_circle.set_y(paddle_ptr->get_y());
    temp_circle.set_radius(paddle_ptr->get_radius());

    for (const auto& brick: brick_list)
    {
        if (circle_square_intersection(temp_circle, brick->get_square())) return;
    }

    paddle_ptr->set_last_dx(new_x - paddle_ptr->get_x());
    paddle_ptr->set_x(new_x);
}

bool Game::has_collision(const unique_ptr<Ball>& ball, int ball_idx)
{
    // Bord gauche
    if (ball->get_x() - ball->get_radius() < epsil_zero)
        return true;

    // Bord droit
    if (ball->get_x() + ball->get_radius() > arena_size - epsil_zero)
        return true;

    // Bord supérieur
    if (ball->get_y() + ball->get_radius() > arena_size - epsil_zero)
        return true;

    // Briques
    for (const auto& brick : brick_list)
        if (circle_square_intersection(ball->get_circle(), brick->get_square()))
            return true;

    // Raquette
    if (paddle_ptr &&
        circle_circle_intersection(ball->get_circle(), paddle_ptr->get_circle()))
        return true;

    // Autres balles
    for (int j = 0; j < (int)ball_list.size(); j++)
    {
        if (j == ball_idx) continue;
        if (circle_circle_intersection(ball->get_circle(),
                                       ball_list[j]->get_circle()))
            return true;
    }

    return false;
}

void Game::wall_ball_bounce(const std::unique_ptr<Ball>& ball)
{
    double dx = ball->get_dx();
    double dy = ball->get_dy();


    bool left  = (ball->get_x() - ball->get_radius()) < epsil_zero;
    bool right = (ball->get_x() + ball->get_radius()) > arena_size - epsil_zero;
    bool top   = (ball->get_y() + ball->get_radius()) > arena_size - epsil_zero;

    if (left || right || top)
    {
        // Cas coin
        if ((left || right) && top)
        {
            double dist_x = left ? ball->get_x() : (arena_size - ball->get_x());
            double dist_y = arena_size - ball->get_y();
            if (dist_x < dist_y) top = false;
            else left = right = false;
        }
        if (left || right) dx = -dx;
        if (top)           dy = -dy;
        ball->set_dx(dx);
        ball->set_dy(dy);
    }
}

void Game::brick_ball_bounce(const std::unique_ptr<Ball>& ball)
{
    double dx = ball->get_dx();
    double dy = ball->get_dy();
    for (const auto& brick : brick_list)
    {
        if (circle_square_intersection(ball->get_circle(), brick->get_square()))
        {
            // Différence entre centres
            double diff_x = ball->get_x() - brick->get_x();
            double diff_y = ball->get_y() - brick->get_y();

            // Différence bornée
            double half = brick->get_width() / 2.0;
            double clamped_x = max(-half, min(diff_x, half));
            double clamped_y = max(-half, min(diff_y, half));

            // Direction nominale
            double nx = diff_x - clamped_x;
            double ny = diff_y - clamped_y;
            double len = sqrt(nx*nx + ny*ny);
            if (len < epsil_zero) 
            {
                nx = 1.0 / sqrt(2);
                ny = 1.0 / sqrt(2);
            } 
            else 
            {
                nx /= len;
                ny /= len;
            }

            // vnew = v - 2*vn
            double vn = dx*nx + dy*ny;
            if (vn > delta_norm_max) vn = delta_norm_max;
            dx = dx - 2.0*vn*nx;
            dy = dy - 2.0*vn*ny;
            ball->set_dx(dx);
            ball->set_dy(dy);


            ball_brick_reaction(ball, brick);
            return ;
        }
    }
    return ;
}

void Game::paddle_ball_bounce(const unique_ptr<Ball>& ball)
{
    double dx = ball->get_dx();
    double dy = ball->get_dy();

    if (paddle_ptr &&
        circle_circle_intersection(ball->get_circle(), paddle_ptr->get_circle()))
    {
        double nx = ball->get_x() - paddle_ptr->get_x();
        double ny = ball->get_y() - paddle_ptr->get_y();
        double len = sqrt(nx*nx + ny*ny);
        if (len < epsil_zero) return;
        nx /= len;
        ny /= len;

        double vn_ball = dx*nx + dy*ny;


        double vn_paddle = paddle_ptr->get_last_dx() * nx; // dy raquette = 0

        double impulse = (-vn_ball + vn_paddle) * 2.0;
        dx += impulse * nx;
        dy += impulse * ny;

        double norm = sqrt(dx*dx + dy*dy);
        if (norm > delta_norm_max)
        {
            dx = dx / norm * delta_norm_max;
            dy = dy / norm * delta_norm_max;
        }
        ball->set_dx(dx);
        ball->set_dy(dy);
    }
}

void Game::ball_ball_bounce(const unique_ptr<Ball>& ball, unsigned int ball_idx)
{
    double dx = ball->get_dx();
    double dy = ball->get_dy();
    for (int j = 0; j < (int)ball_list.size(); j++)
    {
        if (j == ball_idx) continue;
        if (circle_circle_intersection(ball->get_circle(),
                                       ball_list[j]->get_circle()))
        {
            // Direction : centre balle vers centre autre balle
            double nx = ball_list[j]->get_x() - ball->get_x();
            double ny = ball_list[j]->get_y() - ball->get_y();
            double len = sqrt(nx*nx + ny*ny);
            if (len < epsil_zero) return;
            nx /= len;
            ny /= len;

            // Vitesses nominales
            double vn  = dx*nx + dy*ny;
            double vn2 = ball_list[j]->get_dx()*nx + ball_list[j]->get_dy()*ny;

            // Masses proportionnelles à r²
            double r1sq = ball->get_radius() * ball->get_radius();
            double r2sq = ball_list[j]->get_radius() * ball_list[j]->get_radius();

            // impulsion = (-vn + vn_autre) * 2*r_autre² / (r² + r_autre²)
            double impulse = (-vn + vn2) * (2.0*r2sq) / (r1sq + r2sq);
            dx += impulse * nx;
            dy += impulse * ny;

            // Bridage à delta_norm_max
            double norm = sqrt(dx*dx + dy*dy);
            if (norm > delta_norm_max)
            {
                dx = dx / norm * delta_norm_max;
                dy = dy / norm * delta_norm_max;
            }
            ball->set_dx(dx);
            ball->set_dy(dy);
            return;
        }
    }
}

void Game::apply_bounce(const unique_ptr<Ball>& ball, unsigned int ball_idx)
{
    // Bords  ///probleme avce les coins
    wall_ball_bounce(ball);

    // Briques /// probleme des balls disparaissent
    brick_ball_bounce(ball);

    // Paddle /// probleme vraiment tres moche
    paddle_ball_bounce(ball);

    // Balls /// verifier car pas sur dutout
    ball_ball_bounce(ball, ball_idx);

}

void Game::save(const string &file_name) const
{
    ofstream file(file_name);
    if (!file.is_open()) return;

    // Score
    file << "# score\n" << score << "\n\n";

    // Lives
    file << "# lives\n" << lives << "\n\n";

    // Paddle
    file << "# paddle\n";
    if (paddle_ptr) file << paddle_ptr->get_x() << " " << paddle_ptr->get_y() << " "
                                                << paddle_ptr->get_radius() << "\n\n";
    // Bricks
    file << "# bricks\n"<< brick_list.size() << "\n";
    for (const auto &brick : brick_list)
    {
        file << brick->get_type() << " " << brick->get_x() << " "
             << brick->get_y() << " " << brick->get_width();
        // hit_points uniquement pour RainbowBrick (type 0)
        if (brick->get_type() == 0) file << " " << brick->get_hitpoints();
        
        file << "\n";
    }
    file << "\n";

    // Balls
    file << "# balls\n";
    file << ball_list.size() << "\n";
    for (const auto &ball : ball_list)
    {
        file << ball->get_x() << " " << ball->get_y() << " "
             << ball->get_radius() << " " << ball->get_dx() << " " 
             << ball->get_dy() << "\n";
    }
    file.close();
}

void Game::create_new_ball(double x, double y)
{
    if (!paddle_ptr) return;
    double ball_x(get_paddle()->get_x());
    double ball_y(get_paddle()->get_y() + get_paddle()->get_radius() +  
                                            new_ball_radius + epsil_zero);

    double dir_x = x - ball_x;
    double dir_y = y - ball_y;
    double norm = sqrt(dir_x * dir_x + dir_y * dir_y);

    double dx = (abs(norm) >= epsil_zero) ? (dir_x / norm) * new_ball_delta_norm : 0;
    double dy = (abs(norm) >= epsil_zero) ? (dir_y / norm) * new_ball_delta_norm : 
                                                                new_ball_delta_norm;
    
    Ball new_ball(ball_x, ball_y, new_ball_radius, dx, dy);
    add_ball(new_ball);
}

void Game::delete_ball(int index)
{
    ball_list.erase(ball_list.begin() + index);
}

void Game::ball_brick_reaction(const unique_ptr<Ball>& ball_ptr, const unique_ptr<Brick>& brick_ptr)
{
    // add ball reaction

    brick_ptr->hit();
}

void Game::update()
{
    if (status != ONGOING) return;
    unsigned int index(0);
    vector<int> to_delete;

    for (const auto &ball: ball_list)
    {
        ball->update_position();
        if(ball->get_y() < 0) 
        {
            to_delete.push_back(index);
            ++index;
            continue;
        }
        
        unsigned int nb_rebonds(0);
        while(has_collision(ball, index))
        {
            apply_bounce(ball, index);   
            ball->undo_position();   
            ball->update_position();     
            nb_rebonds++;
            if (nb_rebonds >= nb_bounce_max) break;
        }
        ++index;
    }
    // delete all the to_delete balls
    for(int i(to_delete.size()-1); i>=0; i-- ) delete_ball(to_delete[i]);

    update_paddle_position(get_mouse_x());

    index = 0;
    for (const auto &ball : ball_list)
    {
        if (circle_circle_intersection(ball->get_circle(),
                                       paddle_ptr->get_circle()))
        {
            ball->undo_position();
            ball->update_position();

            unsigned int nb_rebonds(0);
            while(has_collision(ball, index))
            {
                apply_bounce(ball, index); 
                ball->undo_position();      
                ball->update_position();   
                nb_rebonds++;
                if (nb_rebonds >= nb_bounce_max) break;
            }
        }
        ++index;
    }

    if(ball_list.size() == 0 and lives == 0) status = LOST;
    if(brick_list.size() == 0) status == WON;
}


// PRIVATE AND CHECKING FUNCTIONS

void Game::set_score(int new_score)
{
    score = new_score;
}

void Game::set_lives(int new_lives)
{
    lives = new_lives;
}

void Game::set_file(string file_name) 
{
    filename = file_name;
}

void Game::set_paddle(Paddle_ptr new_paddle_ptr)
{
    paddle_ptr = move(new_paddle_ptr);
}

void Game::init(string file_name)
{
    ifstream file(file_name);
    if (file_name != "" and file.fail())
    {
        cout << "Didn't find the file: " << file_name << endl;
        return;
    }
    set_file(file_name);

    string line;
    Reading_state reading_state(SCORE);
    unsigned int nb_brick;
    unsigned int brick_counter(0);
    unsigned int nb_ball;
    unsigned int ball_counter(0);
    error_occured=false;

    while (getline(file >> ws, line))
    {
        istringstream data(line);
        if (line.empty() or line[0] == '#')
            continue;

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
                if (++ball_counter >= nb_ball) reading_state = FINISHED;
                break;
            }
            case FINISHED:
                break;
        }
        if (error_occured)
        {
            reset();
            return;
        }
    }
    file.close();
    if (file_name != "") cout << message::success();
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
    paddle_ptr = unique_ptr<Paddle>(new Paddle(error_occured, paddle_x, paddle_y, 
                                                                    paddle_radius));
}

void Game::read_and_check_brick_data(istringstream &data, unsigned int brick_counter,
                                                                 bool& error_occured)
{
    int type, hit_points;
    double brick_x, brick_y, brick_width;
    data >> type >> brick_x >> brick_y >> brick_width;
    unique_ptr<Brick> brick_ptr(nullptr);

    if (type == 1)
    {
        hit_points = 1;
        brick_ptr = unique_ptr<Brick>(new BallBrick(error_occured, brick_x, brick_y,
                                                    brick_width, hit_points, type));
    }
    else if (type ==2)
    {
        hit_points=resolve_hit_points_split_brick(brick_width);
        brick_ptr = unique_ptr<Brick>(new SplitBrick(error_occured, brick_x, brick_y, 
                                                    brick_width, hit_points, type));
    }
    else
    {
        data >> hit_points;
        brick_ptr = unique_ptr<Brick>(new RainbowBrick(error_occured, brick_x, 
                                        brick_y, brick_width, hit_points, type));
    }

    if (circle_square_intersection(paddle_ptr->get_circle(), brick_ptr->get_square()))
        display_error(message::collision_paddle_brick(brick_counter), error_occured);
    
    for (size_t i(0); i < brick_list.size(); i++)
    {
        if (square_square_intersection(brick_list[i]->get_square(),
                                         brick_ptr->get_square()))
            display_error(message::collision_bricks(i, brick_counter), error_occured);
    }

    add_brick(move(brick_ptr));
}

void Game::read_and_check_ball_data(istringstream &data, unsigned int ball_counter, 
                                                                bool& error_occured)
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
        if (circle_square_intersection(ball.get_circle(), 
                            brick_list[i]->get_square()))
        {
            display_error(message::collision_ball_brick(ball_counter, i), 
                                                            error_occured);
        }
    }

    add_ball(ball);
}



int Game::resolve_hit_points_split_brick(double w)
{
    double brick_width(w);
    int hit_points(1);

    while (brick_width >= brick_size_min)
    {
        brick_width = (brick_width - split_brick_gap)/2;
        ++hit_points;
    }
    return hit_points;
}

void Game::reset()
{
    score = 0;
    lives = 0;
    paddle_ptr = nullptr;
    brick_list.clear();
    ball_list.clear();
}
