#ifndef __LINE_HPP__
#define __LINE_HPP__

#include "Point.hpp"
#include <memory>
#include <iostream>

class Line {

public:

    Line();

    Line(const std::array<Point, 2>& points);
    Line(std::array<Point, 2>&& points);
    Line(const std::array<Point, 2>& points, int thickness);
    Line(std::array<Point, 2>&& points, int thickness);

    Line(const Point& p1, const Point& p2);
    Line(Point&& p1, Point&& p2);
    Line(const Point& p1, const Point& p2, int thickness);
    Line(Point&& p1, Point&& p2, int thickness);

    Line(int x1, int y1, int x2, int y2);
    Line(int x1, int y1, int x2, int y2, int thickness);

    ~Line();



    void set_line(Point p1, Point p2);

    void set_parameters(double a, double b);

    std::array<double, 2> get_parameters();

    double get_slope();

    std::array<Point, 2> get_points();

    void set_points(std::array<Point, 2> points);

    void calculate_parameters();

    Point get_p0();

    Point get_p1();

    Line get_x_projected();
    Line get_y_projected();

    int get_thickness();

    void set_p0(Point p);

    void set_p1(Point p);

    void set_thickness(int thickness);

    void redefine_parameters();

    bool is_within(Point& p);

    bool beyond_scope(Point &p);

    std::array<double, 4> get_coord();

    Point intersect(Line l);

    double length();

    Point inLine(double ratio );

    void draw(std::shared_ptr<SDL_Renderer> renderer);
    void draw_shadow(std::shared_ptr<SDL_Renderer> renderer);

private:
    std::array<Point, 2> points;

    // paramètres de l'équation de la droite 
    double a;
    double b;
    int thickness = 1;
};

#endif