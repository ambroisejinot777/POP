#include "graphic.h"
#include "constants.h"
#include <cmath>

using namespace std;

void set_color(Color color);


static const Cairo::RefPtr<Cairo::Context> *ptcr(nullptr);

// graphic.h
void graphic_set_context(const Cairo::RefPtr<Cairo::Context> &cr)
{
    ptcr = &cr;
}

void draw_square(const Cairo::RefPtr<Cairo::Context> &cr, double x, double y, 
                                                    double w, Color color, bool fill)
{
    set_color(color);
    cr->rectangle(x - w/2, y - w/2, w, w);

    if (fill) 
    {
        cr->fill();
    }
    else 
    {
        cr->stroke();
    }
}

void draw_circle(const Cairo::RefPtr<Cairo::Context> &cr, double x, double y, 
                                                        double r, Color color)
{
    set_color(color);
    cr->arc(x, y, r, 0, 2 * M_PI);
    cr->fill();

}


void draw_arc(const Cairo::RefPtr<Cairo::Context> &cr, double x, double y, double r,
                                    double teta_min, double teta_max, Color color)
{
    set_color(color);
    cr->arc(x, y, r, teta_min, teta_max);
    cr->stroke();
}



// local functions
void set_color(Color color)
{
    double r(0.), g(0.), b(0.);

    switch (color)
    {
        case RED:
            r = 1.0;
            break;
        case ORANGE:
            r = 1.0;
            g = 0.5;
            break;
        case YELLOW:
            r = 1.0;
            g = 1.0;
            break;
        case GREEN:
            g = 1.0;
            break;
        case CYAN:
            g = 1.0;
            b = 1.0;
            break;
        case BLUE:
            b = 1.0;
            break;
        case PURPLE:
            r = 0.5;
            b = 1.0;
            break;
        case BLACK:
            r = g = b = 0.0;
            break;
        case GREY:
            r = g = b = 0.5;
            break;
        case WHITE:
            r = g = b = 1.0;
            break;
        default:
            break;
    }
    (*ptcr)->set_source_rgb(r, g, b);
}

void draw_ball(const Cairo::RefPtr<Cairo::Context> &cr, double x, double y, double r)
{
    cr->arc(x, y, r, 0, 2 * M_PI);
    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->fill();
}

void draw_paddle(const Cairo::RefPtr<Cairo::Context> &cr, double x, double y, 
                                                                    double r)
{
    cr->arc(x, y, r, 0, 2 * M_PI);
    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->fill();
    cr->arc(x, y, 0.95 * r, 0, 2 * M_PI);
    cr->set_source_rgb(1.0, 1.0, 1.0);
    cr->fill();
}