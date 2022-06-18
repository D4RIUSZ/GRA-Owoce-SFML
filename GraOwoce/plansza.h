#ifndef PLANSZA_H
#define PLANSZA_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>

class Plansza: public sf::Drawable, sf::Transformable
{
    public:
        int tryb;
        Plansza();
        void update(sf::Clock);
        virtual ~Plansza();
        void zwieksz_punkty(int);
        int straty;
        short ilosc_zyc;
        sf::Sprite tlo;
        void wczytaj_rekord();
        sf::Sound sound_lost;           //klasa pozwalająca dodać dźwięki
        sf::SoundBuffer buffer_lost;
    protected:
    private:
        void sprawdz_wynik();
        void updatestatistics();
        int punkty;

        float czas;

        sf::Text txt_punkty, txt_czas, txt_przegrana, txt_best;
        sf::Font font;
        sf::Texture t_tlo, t_menu, t_zycia;
        sf::Sprite menu, zycia[3];
        //metoda pozwalająca wyświetlać wyniki na dole ekranu
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

};

#endif // PLANSZA_H
