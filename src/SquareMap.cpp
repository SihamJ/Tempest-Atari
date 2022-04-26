#include "../headers/SquareMap.hpp"


SquareMap::SquareMap(){};

SquareMap::SquareMap(long double ratio, Color c)
    : Tube("Square", c)
{
    this->ratio = ratio;
    this->height = 5 * HEIGHT / 7;
    this->width = 2 * WIDTH / 5;
    this->center = Point(WIDTH/2, HEIGHT * (1-ratio) );
    this->nbHall = 16;
}

SquareMap::~SquareMap(){}

void SquareMap::set_inner_square(){

    long double xstep = this->width / 24.;
    long double ystep = this->height / 24.;

    double long h = this->center.get_y() - (height * (1-ratio)) / 6.;
    double long w = WIDTH /2. + ( this->width / 2. ) / 6.;

    Point p0 = Point( this->center.get_x() , h);
    Point p1 = Point( this->center.get_x() + xstep, h);
    Point p2 = Point( w, h );
    Point p3 = Point( w, h + ystep);
    Point p4 = Point( w, h + 2*ystep);
    Point p5 = Point( w, h + 3*ystep);
    Point p6 = Point( w, h + 4*ystep);
    Point p7 = Point( this->center.get_x() + xstep, h + 4*ystep);
    Point p8 = Point( this->center.get_x(), h + 4*ystep);
    Point p9 = Point( this->center.get_x() - xstep, h + 4*ystep);
    Point p10 = Point( this->center.get_x() - 2 * xstep, h + 4*ystep);
    Point p11 = Point( this->center.get_x() - 2 * xstep, h + 3*ystep);
    Point p12 = Point( this->center.get_x() - 2 * xstep, h + 2*ystep);
    Point p13 = Point( this->center.get_x() - 2 * xstep, h + ystep);
    Point p14 = Point( this->center.get_x() - 2 * xstep, h );
    Point p15 = Point( this->center.get_x() - xstep, h );

    inner_square.push_back(p0);
    inner_square.push_back(p1);
    inner_square.push_back(p2);
    inner_square.push_back(p3);
    inner_square.push_back(p4);
    inner_square.push_back(p5);
    inner_square.push_back(p6);
    inner_square.push_back(p7);
    inner_square.push_back(p8);
    inner_square.push_back(p9);
    inner_square.push_back(p10);
    inner_square.push_back(p11);
    inner_square.push_back(p12);
    inner_square.push_back(p13);
    inner_square.push_back(p14);
    inner_square.push_back(p15);
    inner_square.push_back(p0);

}

void SquareMap::set_outer_square(){

    long double xstep = this->width / 4.;
    long double ystep = this->height / 4.;

    double long h = this->center.get_y() - (height * (1-ratio));
    double long w = WIDTH /2. + this->width / 2.;

    Point p0 = Point( this->center.get_x() , h);
    Point p1 = Point( this->center.get_x() + xstep, h);
    Point p2 = Point( w, h );
    Point p3 = Point( w, h + ystep);
    Point p4 = Point( w, h + 2*ystep);
    Point p5 = Point( w, h + 3*ystep);
    Point p6 = Point( w, h + 4*ystep);
    Point p7 = Point( this->center.get_x() + xstep, h + 4*ystep);
    Point p8 = Point( this->center.get_x(), h + 4*ystep);
    Point p9 = Point( this->center.get_x() - xstep, h + 4*ystep);
    Point p10 = Point( this->center.get_x() - 2 * xstep, h + 4*ystep);
    Point p11 = Point( this->center.get_x() - 2 * xstep, h + 3*ystep);
    Point p12 = Point( this->center.get_x() - 2 * xstep, h + 2*ystep);
    Point p13 = Point( this->center.get_x() - 2 * xstep, h + ystep);
    Point p14 = Point( this->center.get_x() - 2 * xstep, h );
    Point p15 = Point( this->center.get_x() - xstep, h );

    outer_square.push_back(p0);
    outer_square.push_back(p1);
    outer_square.push_back(p2);
    outer_square.push_back(p3);
    outer_square.push_back(p4);
    outer_square.push_back(p5);
    outer_square.push_back(p6);
    outer_square.push_back(p7);
    outer_square.push_back(p8);
    outer_square.push_back(p9);
    outer_square.push_back(p10);
    outer_square.push_back(p11);
    outer_square.push_back(p12);
    outer_square.push_back(p13);
    outer_square.push_back(p14);
    outer_square.push_back(p15);
    outer_square.push_back(p0);
}

void SquareMap::build_map(){
    this->set_inner_square();
    this->set_outer_square();

    for(int i = 0; i <= 16; i++){
            Tunel h = Tunel(outer_square.at(i), outer_square.at((i+1)%outer_square.size()), 
                                            inner_square.at(i), inner_square.at((i+1)%inner_square.size()), 2);
            h.set_angle();
            h.set_nb_hall(i);
            this->add_Hall(h);
        }

}