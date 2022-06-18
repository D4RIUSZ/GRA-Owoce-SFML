#ifndef MENUTLO_H
#define MENUTLO_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <cstdlib>
#include <iostream>

class MenuTlo: public sf::Drawable, sf::Transformable
{
    public:
        sf::Texture t_menu;
        sf::Sprite menu;
        MenuTlo();
        virtual ~MenuTlo();
    private:
        //metoda wyswietlająca Tlo Menu
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif // MENUTLO_H
