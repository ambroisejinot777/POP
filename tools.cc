// tools.cc : module mathématiques avec des fonctions et des class
//            utilitaires
//            version 1.0 

#include "tools.h"

using namespace std;

// UTILITY CLASSES

// POINT

Point::Point(double x, double y)
    : x(x), y(y) {}

Point::Point(Point const &old_point)
    : x(old_point.x), y(old_point.y) {}

double Point::get_x() const
{
    return x;
}

double Point::get_y() const
{
    return y;
}

void Point::set_x(double x)
{
    this->x = x;
}

void Point::set_y(double y)
{
    this->y = y;
}

// SQUARE

Square::Square(double x, double y, double w)
    : center(x, y), width(w) {}

Square::Square(Square const &old_square)
    : center(old_square.center), width(old_square.width) {}

double Square::get_x() const
{
    return center.get_x();
}

double Square::get_y() const
{
    return center.get_y();
}

double Square::get_width() const
{
    return width;
}

void Square::set_x(double x)
{
    center.set_x(x);
}

void Square::set_y(double y)
{
    center.set_y(y);
}

void Square::set_width(double w)
{
    width = w;
}

void Square::draw(const Cairo::RefPtr<Cairo::Context> &cr, Color color)
{
    draw_square(cr, get_x(), get_y(), width, color);
}

// CIRCLE

Circle::Circle(double x, double y, double r)
    : center(x, y), radius(r) {}

Circle::Circle(Circle const &old_circle)
    : center(old_circle.center), radius(old_circle.radius) {}

double Circle::get_x() const
{
    return center.get_x();
}

double Circle::get_y() const
{
    return center.get_y();
}

double Circle::get_radius() const
{
    return radius;
}

void Circle::set_x(double x)
{
    center.set_x(x);
}

void Circle::set_y(double y)
{
    center.set_y(y);
}

void Circle::set_radius(double r)
{
    radius = r;
}

void Circle::draw(const Cairo::RefPtr<Cairo::Context> &cr, Color color)
{
    draw_circle(cr, get_x(), get_y(), radius, color);
}

// UTILITY FUNCTIONS

void display_error(string message, bool& error_occured)
{
    cout << message;
    error_occured=true;
}

double compute_norm(Point& point)
{
    double x(point.get_x());
    double y(point.get_y());
    return sqrt(x*x+y*y);
}

double dot_product(Point const& a, Point const& b)
{
    return a.get_x() * b.get_x() + a.get_y() * b.get_y();
}


// INTERSECTION FUNCTIONS
bool circle_circle_intersection(Circle const &c1, Circle const &c2)
{
    double distance = sqrt((c1.get_x() - c2.get_x()) * (c1.get_x() - c2.get_x()) +
                           (c1.get_y() - c2.get_y()) * (c1.get_y() - c2.get_y()));
    if ((distance - (c1.get_radius() + c2.get_radius())) < epsil_zero)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool circle_square_intersection(Circle const &c, Square const &s)
{
    double closest_x = max(s.get_x() - s.get_width() / 2,
             min(c.get_x(), s.get_x() + s.get_width() / 2));
    double closest_y = max(s.get_y() - s.get_width() / 2,
             min(c.get_y(), s.get_y() + s.get_width() / 2));

    double distance_x = c.get_x() - closest_x;
    double distance_y = c.get_y() - closest_y;

    double distance_squared = (distance_x * distance_x) + (distance_y * distance_y);
    bool check = (distance_squared - (c.get_radius() * c.get_radius())) 
                                                    < epsil_zero * epsil_zero;
    return check;
}

bool square_square_intersection(Square const &s1, Square const &s2)
{
    double x_overlap = abs(s1.get_x() - s2.get_x()) - (s1.get_width() / 2 +
                                                       s2.get_width() / 2);
    double y_overlap = abs(s1.get_y() - s2.get_y()) - (s1.get_width() / 2 +
                                                       s2.get_width() / 2);
    if (x_overlap < 0 and y_overlap < 0)
    {
        return true;
    }
    return false;
}



























// FONCTIONS DE CALCULS

// ── 4.1.2 : Collision cercle / cercle (ou raquette si radius2 = 0)
// Formule : impulsion = (-vn + v_autre_n) * (2 * r2² / (r² + r2²))
// Si radius2 == 0 → masse infinie (raquette) → facteur = 2

double circle_circle_impulse(Circle const& c1, double dx1, double dy1,
                             Circle const& c2, double dx2, double dy2, bool isPaddle)
{
    double delta_x = c2.get_x() - c1.get_x();
    double delta_y = c2.get_y() - c1.get_y();
    double dist    = sqrt(delta_x * delta_x + delta_y * delta_y);

    double nx = delta_x / dist;
    double ny = delta_y / dist;

    double vn1 = dx1 * nx + dy1 * ny;
    double vn2 = dx2 * nx + dy2 * ny;

    double r2 = c2.get_radius();
    double r1 = c1.get_radius();

    double mass_factor = isPaddle ? 2.0 : (2.0 * r2 * r2) / (r1 * r1 + r2 * r2);

    return (-vn1 + vn2) * mass_factor;
}

// double circle_circle_newdeltax(double dx,  double dy,  double radius,
//                                double dx2, double dy2, double radius2,
//                                double nx,  double ny)
// {
//     return dx + circle_circle_impulse(dx, dy, radius,
//                                       dx2, dy2, radius2, nx, ny) * nx;
// }

// double circle_circle_newdeltay(double dx,  double dy,  double radius,
//                                double dx2, double dy2, double radius2,
//                                double nx,  double ny)
// {
//     return dy + circle_circle_impulse(dx, dy, radius,
//                                       dx2, dy2, radius2, nx, ny) * ny;
// }

// ── 4.1.1 : Collision cercle / segment, arena, point
// Formule : réflexion pure  v_new = v − 2·(v·n)·n

double circle_segment_newdeltax(double dx, double dy,
                                double nx, double ny)
{
    double vn = dx * nx + dy * ny;
    return dx - 2.0 * vn * nx;
}

double circle_segment_newdeltay(double dx, double dy,
                                double nx, double ny)
{
    double vn = dx * nx + dy * ny;
    return dy - 2.0 * vn * ny;
}

void get_brick_collision_normal(double ball_x, double ball_y,
                                double brick_x, double brick_y, double brick_width,
                                double& nx, double& ny)
{
    double diff_x = ball_x - brick_x;
    double diff_y = ball_y - brick_y;

    double half = brick_width / 2.0;

    double clamped_x = std::max(-half, std::min(diff_x, half));
    double clamped_y = std::max(-half, std::min(diff_y, half));

    double nom_x = diff_x - clamped_x;
    double nom_y = diff_y - clamped_y;

    double norm = std::sqrt(nom_x * nom_x + nom_y * nom_y);
    if (norm == 0.0) { nx = 0.0; ny = 0.0; return; }

    nx = nom_x / norm;
    ny = nom_y / norm;
}


