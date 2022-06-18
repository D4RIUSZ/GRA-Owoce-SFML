#ifndef SPADANIE_H
#define SPADANIE_H

#include <SFML/Audio.hpp>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "owoc.h"
#include "particle.h"

class Spadanie: public sf::Drawable, sf::Transformable
{
    public:
        std::vector <Owoc> owoc;
        std::vector <Robak> robak;
        std::vector <Particle>  particle;
        std::vector <sf::Sprite> owocki1;
        sf::Vector2f pozycje[3];
        Spadanie();
        virtual ~Spadanie();
        float licznik_czasu,szybkosc_generowania;
        void generuj_owoca();
        void generuj_robaka();
        void generuj_efekt(sf::Vector2f, float);
        void update(sf::Clock,int);
        void zlap(int);
        void zlap_r(int);
        void usun(int);
        void usunr(int);
        void lost();
        int bonusy;
        bool dzwiek;
        sf::Sound sound, sound_r, sound_lost;
        sf::SoundBuffer buffer,buffer_r, buffer_lost;
    protected:
    private:
        void wczytaj_ustawienia();
        int zakres_przyspieszenia;
        float ogranicznik, przyspieszenie;
        int skala_przyspieszenia;
        sf::Vector2f predkosc;
        sf::Texture t_robak,lisc,t_owocki;
        Owoc OwocBazowy;
        Robak RobakBazowy;
        Particle particle1;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif // SPADANIE_H
