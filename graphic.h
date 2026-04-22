#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "graphic_gui.h"

enum Color
{
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    PURPLE,
    BLACK,
    GREY,
    WHITE,
};

void draw_square(const Cairo::RefPtr<Cairo::Context> &cr, double x, double y, 
                                                        double w, Color color, bool fill = true);
void draw_circle(const Cairo::RefPtr<Cairo::Context> &cr, double x, double y, 
                                                double r, Color color = BLACK);

void draw_arc(const Cairo::RefPtr<Cairo::Context> &cr, double x, double y, double r,
                                                       double teta_min, double teta_max,
                                                        Color color = BLACK);

#endif
