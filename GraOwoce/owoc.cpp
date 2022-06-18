#include "owoc.h"

Owoc::Owoc()
{
}

Owoc::~Owoc()
{
}

//nadawanie obiektowi przyspieszenia i predkosci
void Owoc::nadaj(float przys, sf::Vector2f predk)
{
    predkosc=predk;
    przyspieszenie=przys;
}

//przekazanie predkosci i przyspieszenia do funkcji
void Owoc::ruch(float czas)
{
    predkosc.y+=predkosc.y*przyspieszenie*czas;
    sprite.move(predkosc*czas);
}

Robak::Robak()
{
}

Robak::~Robak()
{
}

//nadawanie obiektowi przyspieszenia i predkosci
void Robak::nadaj(float przys, sf::Vector2f predk)
{
    predkosc=predk;
    przyspieszenie=przys;
}

//przekazanie predkosci i przyspieszenia do funkcji
void Robak::ruch(float czas)
{
    predkosc.y+=predkosc.y*przyspieszenie*czas;
    sprite.move(predkosc*czas);
}
