#include "silnik.h"
#include <SFML/Graphics.hpp>


Silnik::Silnik()
{
}

Silnik::~Silnik()
{}


void Silnik::uruchomSilnik(RenderWindow *window, int tryb)
{
    this->tryb = tryb;
    //przekazuje klasie plansza jaki tryb został wybrany
    plansza.tryb = this->tryb;
    //wczytywanie rekordu
    plansza.wczytaj_rekord();
    bool menu = false;
    window->setFramerateLimit(60);
    sf::Clock zegar;
    sf::Clock zeg_anim;


    while(!menu)
    {
        Event event;


        while(window->pollEvent(event))
        {
            //gdy zamkniemy okno gry wracamy do menu
            if(event.type == Event::Closed || (event.type==Event::KeyReleased && event.key.code == Keyboard::Escape))
                menu = true;

            //poruszanie się koszykiem
                if(event.type == Event::KeyReleased)
                {
                    if((event.key.code == Keyboard::Right )&& gracz.getStatus() != 1)
                        gracz.stop();
                    if((event.key.code == Keyboard::Left) && gracz.getStatus() != 0)
                        gracz.stop();
                }

                if(event.type == Event::KeyPressed)
                {
                    if((event.key.code == Keyboard::D || event.key.code == Keyboard::Right))
                    {
                        gracz.przesun_w_prawo();
                    }
                    if((event.key.code == Keyboard::A || event.key.code == Keyboard::Left))
                    {
                        gracz.przesun_w_lewo();
                    }
                }
                //gdy jest uruchomiony tryb 3 do klasy special jest podawana pozycja myszki aby móc poruszać się obrazem z przezroczystością
                //który przypomina efekt latarki
                if (tryb==3)
                {
                    if(event.type == sf::Event::MouseMoved)
                    {
                        special.zmien_pozycje(sf::Mouse::getPosition(*window).x,sf::Mouse::getPosition(*window).y);
                    }
                }

            }

        //gdy ilość żyć jest większa niż 0 na planszy poruszają się obiekty
        if(plansza.ilosc_zyc>0)
        {
            kolizja();
            gracz.update(zegar,zeg_anim);
            spadanie.update(zegar,tryb);
            plansza.update(zegar);
        }

        if(plansza.ilosc_zyc==0)
        {
            kolizja();
        }

        zegar.restart();
        if(zeg_anim.getElapsedTime() > sf::seconds(0.025))
        {
            zeg_anim.restart();
        }
        window->clear();
        window->draw(plansza.tlo);
        window->draw(spadanie);
        window->draw(gracz);
        if (tryb==3)
        {
            window->draw(special);
        }
        window->draw(plansza);
        window->display();

    }
}

void Silnik::kolizja()
{
    if(!spadanie.owoc.empty())
        for(unsigned int i=0;i<spadanie.owoc.size();i++)
        {
            //gdy owoc dotknie koszyka , to na tablicy jest zwiększana liczba punktów oraz obiekt zostaje usunięty
            if(gracz.dokolizji.getGlobalBounds().intersects( spadanie.owoc[i].sprite.getGlobalBounds() ))
            {
                spadanie.zlap(i);
                plansza.zwieksz_punkty(1);
            }
            //gdy robak dotknie koszyka , to na tablicy jest zmniejszona liczba punktów, liczba żyć zmniejszy sie
            //oraz obiekt zostaje usunięty
            if (tryb==2)
            {
                if(gracz.dokolizji.getGlobalBounds().intersects( spadanie.robak[i].sprite.getGlobalBounds() ))
                {
                    spadanie.zlap_r(i);
                    plansza.straty++;
                    plansza.zwieksz_punkty(-1);
                }
            }
            //jeżeli owoc zostanie pominięty, liczba punktów zmniejszy się oraz liczba żyć zmniejszy się oraz owoc zostaje usunięty
            if(spadanie.owoc[i].sprite.getPosition().y>620)
            {
                spadanie.usun(i);
                plansza.straty++;
                plansza.zwieksz_punkty(-1);
            }
            //jeżeli obak zostanie pominięty,robak zostaje usunięty
            if(tryb==2)
            {
                if(spadanie.robak[i].sprite.getPosition().y>620)
                {
                    spadanie.usunr(i);
                }
            }

        }
    //gdy iklosc zyc jest rowna zero, zostanie odtworzona raz melodia końca gry
    if (plansza.ilosc_zyc==0)
    {
        dzwiek=1;
    }
    if (dzwiek==1 && rdzwiek==1)
    {
        spadanie.lost();
        rdzwiek=0;
    }
}
