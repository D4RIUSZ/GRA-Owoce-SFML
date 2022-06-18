#include "particle.h"

Particle::Particle()
{
    czas_zycia=0;
}

Particle::~Particle()
{
}

//Poruszanie obiektami w czasie

void Particle::update(float grawitacja, float czas)
{
    static const float mnoznik=10;
    czas_zycia+=czas;
    predkosc.y+=grawitacja*czas*mnoznik*mnoznik;
    sprite.move(predkosc.x*czas*mnoznik, predkosc.y*czas*mnoznik);
    sprite.setRotation((atan2(predkosc.y,predkosc.x)*180/3.14)-90);

}
