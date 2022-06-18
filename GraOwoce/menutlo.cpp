#include "MenuTlo.h"

//tworzenie Tła oraz wczytanie obrazka tła
MenuTlo::MenuTlo()
{
    srand(time(NULL));
    t_menu.loadFromFile("data/menutlo1.png");
    menu.setTexture(t_menu);

}

MenuTlo::~MenuTlo()
{
}

//metoda wyswietlająca Tlo Menu
void MenuTlo::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(menu);
}
