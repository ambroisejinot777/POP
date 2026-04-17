#ifndef GRAPHIC_GUI_H
#define GRAPHIC_GUI_H

#include <gtkmm/drawingarea.h>
#include "graphic.h"

void graphic_set_context(const Cairo::RefPtr<Cairo::Context> &cr);
void draw_brick(const Cairo::RefPtr<Cairo::Context> &cr, double x, double y, double w, Color color, int type_brick);
void draw_ball(const Cairo::RefPtr<Cairo::Context> &cr, double x, double y, double r);
void draw_paddle(const Cairo::RefPtr<Cairo::Context> &cr, double x, double y, double r);


#endif
