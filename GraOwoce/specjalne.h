#ifndef SPECJALNE_H
#define SPECJALNE_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>


class Specjalne :public sf::Drawable, sf::Transformable
{
public:
    sf::Texture t1;
    sf::Sprite s1;
    void zmien_pozycje(int x,int y);
    Specjalne();
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif // SPECJALNE_H
