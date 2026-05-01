#ifndef BRICK_H
#define BRICK_H

// brick.h : class de Brick et des sous-class de RainbowBrick, BallBrick et SplitBrick
//           avec des fonction de verification des attributs des bricks
//           version 1.0

#include "message.h"
#include "tools.h"
#include "constants.h"



// BRICK CLASS

class Brick
{

public:
    Brick(bool& error_occured, double x = 0.0, double y = 0.0, double width = 0.0,
                                                int hit_points = 0, int type = 0);
    Brick(double x = 0.0, double y = 0.0, double width = 0.0, int hit_points = 0,
                                                                    int type = 0);
    Brick(Brick const &old_brick);
    virtual ~Brick(){};

    double get_x() const;
    double get_y() const;
    double get_width() const;
    Square get_square() const;
    int get_type() const;
    int get_hitpoints() const;
    Color get_color() const;
    virtual void draw(const Cairo::RefPtr<Cairo::Context> &cr) const = 0;
    bool hit(); // return true if hit_points == 0

private:
    Square square;
    int type;

protected:
    int hit_points;
    Color color;
    

};

typedef std::vector<std::unique_ptr<Brick>> Brick_list;


class RainbowBrick : public Brick
{
public:
    RainbowBrick(bool& error_occured, double x, double y, double width, 
                                            int hit_points, int type);
    RainbowBrick(double x, double y, double width, int hit_points, int type);
    void draw(const Cairo::RefPtr<Cairo::Context> &cr) const override;
};


class BallBrick : public Brick
{
public:
    BallBrick(bool& error_occured, double x, double y, double width, int hitpoints
                                                                        , int type);
    BallBrick(double x, double y, double width, int hitpoints, int type);
    void draw(const Cairo::RefPtr<Cairo::Context> &cr) const override;
};


class SplitBrick : public Brick
{
public:
    SplitBrick(bool &error_occured, double x, double y, double width, int hit_points,
                                                                         int type);
    SplitBrick(double x, double y, double width, int hit_points, int type);
    void draw(const Cairo::RefPtr<Cairo::Context> &cr) const override;
};

// CHECKING FUNCTIONS

void check_brick_position(double x, double y, double width, bool &error_occured);
void check_brick_size(double width, bool &error_occured);
void check_brick_hit_points(int hit_points, bool &error_occured);
void check_brick_type(int type, bool &error_occured);

#endif

