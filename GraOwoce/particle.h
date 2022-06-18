#ifndef PARTICLE_H
#define PARTICLE_H
#include <SFML/Graphics.hpp>
#include <math.h>

class Particle
{
    public:
        sf::Sprite sprite;
        sf::Vector2f predkosc;
        float orientacja,czas_zycia;
        void update(float,float);
        void Sprawdzaj(int);
        Particle();
        virtual ~Particle();
    protected:
    private:
};

#endif // PARTICLE_H
