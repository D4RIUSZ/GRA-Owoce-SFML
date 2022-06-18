#ifndef OWOC_H
#define OWOC_H

#include <SFML/Graphics.hpp>

class Owoc
{
    public:
        Owoc();
        sf::Sprite sprite;
        virtual ~Owoc();
        void ruch(float);
        sf::Vector2f predkosc;
        float przyspieszenie;
        void nadaj(float,sf::Vector2f);
    protected:
    private:


};

class Robak
{
    public:
        Robak();
        sf::Sprite sprite;
        virtual ~Robak();
        void ruch(float);
        sf::Vector2f predkosc;
        float przyspieszenie;
        void nadaj(float,sf::Vector2f);
    protected:
    private:


};
#endif // OWOC_H
