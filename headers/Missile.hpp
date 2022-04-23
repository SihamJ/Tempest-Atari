#ifndef __MISSILE_HPP__
#define __MISSILE_HPP__

#include "Point.hpp"
#include "Line.hpp"
#include "Tunel.hpp"

class Missile {
    public:
        Missile();
        ~Missile();

        //constructeur
        Missile(const Tunel& h);
        Missile(const Tunel&& h);

        int get_width();

        int get_height();

        int get_x();

        int get_y();

        Point get_pos();

        bool get_closer();

        bool intersect(Line l);

        Tunel get_hall();

        void draw(std::shared_ptr<SDL_Renderer> renderer);

    private:

        // couloir auquel appartient l'ennemi
        Tunel hall;

        Point dest;
        Point start;
        Point pos;

        // taille initial de l'image
        const int init_width = 40;
        const int init_height = 40;

        // taille à changer pr agrandir ou rétrécir l'image de l'ennemi
        int width = 40;
        int height = 40;
        int angle = 0;

};



#endif