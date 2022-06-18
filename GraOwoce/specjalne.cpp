#include "specjalne.h"

//tworzenie latarki
Specjalne::Specjalne()
{
        t1.loadFromFile("data/alfa.png");
        s1.setTexture(t1);
        s1.setPosition(-300,-200);

}

//funkcja zmienia pozycje latarki w zaleznosci od polozenia myszki
void Specjalne::zmien_pozycje(int x,int y)
{
    s1.setPosition(x-750,y-750);
}

//funkcja wyswietla latarke na ekranie

void Specjalne::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(s1);
}
