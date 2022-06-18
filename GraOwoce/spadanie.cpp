#include "spadanie.h"
#include <string>
#include <iostream>


Spadanie::Spadanie()
{
    //wczytywanoie textur owocóW
    srand(time(NULL));
    t_robak.loadFromFile("data/robak1.png");
    lisc.loadFromFile("data/lisc1.png");
    t_owocki.loadFromFile("data/Owocki33.png");
    //wczytywanie dźwięku
    buffer.loadFromFile("data/szelest.ogg");
    buffer_r.loadFromFile("data/szwiercz.ogg");
    buffer_lost.loadFromFile("data/koniec.ogg");

    wczytaj_ustawienia();
    licznik_czasu=0;
    sound.setBuffer(buffer);
    sound_r.setBuffer(buffer_r);
    sound_lost.setBuffer(buffer_lost);
    OwocBazowy.nadaj(przyspieszenie,predkosc);
    RobakBazowy.nadaj(przyspieszenie,predkosc);
    particle1.sprite.setTexture(lisc);
    particle1.sprite.setScale(0.5f,0.5f);
    particle1.sprite.setOrigin(8,10);
}

Spadanie::~Spadanie()
{

}

//wczytywanie ustawień z pliku
void Spadanie::wczytaj_ustawienia()
{
    std::fstream plik;
    std::string tmp;
    plik.open("config/config.dat", std::ios::in);
    plik>>tmp; plik>>ogranicznik;
    plik>>tmp; plik>>szybkosc_generowania;
    plik>>tmp; plik>>zakres_przyspieszenia;
    plik>>tmp; float pred; plik>>pred;
    plik>>tmp; plik>>przyspieszenie;
    plik>>tmp; plik>>skala_przyspieszenia;
    plik>>tmp; plik>>dzwiek;
    plik.close();
    predkosc=sf::Vector2f(0,pred);
    przyspieszenie/=skala_przyspieszenia;
}


void Spadanie::update(sf::Clock zegar, int trybgry)
{

    static int ileOwocow=0;
    float czas=zegar.getElapsedTime().asSeconds();
    licznik_czasu+=czas;
    //spadanie obiektów
    if(!owoc.empty())
    {
        for(unsigned int i=0;i<owoc.size();i++)
        {
            owoc[i].ruch(czas);
        }
    }
    if(!robak.empty())
    {
        for(unsigned int i=0;i<robak.size();i++)
        {
            robak[i].ruch(czas);
        }
    }
//nadawanie predkosci lisciom
    if(!particle.empty())
    {
        for(unsigned int i=0;i<particle.size();i++)
        {
            particle[i].update(przyspieszenie,czas);
            if(particle[i].sprite.getPosition().y>600)particle.erase(particle.begin()+i);
        }
    }
    //generowanie obiektóW w zależności od trybu gry
    if(trybgry == 1)
    {
        if(licznik_czasu>szybkosc_generowania)
        {
            generuj_owoca();
            if(szybkosc_generowania>ogranicznik)szybkosc_generowania-=0.005;
            licznik_czasu=0;
            ileOwocow++;
        }
    }
    if (trybgry==2)
    {
        if(licznik_czasu>szybkosc_generowania)
        {
            generuj_owoca();
            generuj_robaka();
            if(szybkosc_generowania>ogranicznik)szybkosc_generowania-=0.005;
            licznik_czasu=0;
            ileOwocow++;
        }
    }
    if(trybgry == 3)
        if(licznik_czasu>szybkosc_generowania)
        {
            generuj_owoca();
            if(szybkosc_generowania>ogranicznik)szybkosc_generowania-=0.005;
            licznik_czasu=0;
            ileOwocow++;
        }
}

//generowanie efektu liści
void Spadanie::generuj_efekt(sf::Vector2f pozycja_bazowa,float moc)
{
    moc*=0.075;
    moc+=5;
    for(int i=0;i<(std::rand()%7)+3;i++)
    {
        particle.push_back(particle1);
        particle.back().sprite.setPosition(pozycja_bazowa);
        particle.back().sprite.move(0,10);
        particle.back().predkosc=sf::Vector2f(i*-((std::rand()%300)/100)-2,i*((std::rand()%500)/100)-moc);
    }
    for(int i=0;i<(std::rand()%7)+3;i++)
    {
        particle.push_back(particle1);
        particle.back().sprite.setPosition(pozycja_bazowa);
        particle.back().sprite.move(0,10);
        particle.back().predkosc=sf::Vector2f(i*((std::rand()%300)/100)+2,i*((std::rand()%500)/100)-moc);
    }

}

//generowanie spadania owoca
void Spadanie::generuj_owoca()
{
    owoc.push_back(OwocBazowy);
    float przys=(std::rand()%zakres_przyspieszenia);
    przys=przys/skala_przyspieszenia;
    int random1 = std::rand()%6;
    int random2 = std::rand()%3;
    owoc.back().sprite.setTexture(t_owocki);

    owoc.back().sprite.setTextureRect(sf::IntRect(random1*625.f,random2*625.f,625,625));
    owoc.back().sprite.setScale(0.125,0.125);
    short poz=(std::rand()%350)+10;
    owoc.back().sprite.setPosition(poz,0);
}

//generowanie spadania robaka
void Spadanie::generuj_robaka()
{
    robak.push_back(RobakBazowy);
    float przys=(std::rand()%zakres_przyspieszenia);
    przys=przys/skala_przyspieszenia;
    robak.back().przyspieszenie+=przys;
    robak.back().sprite.setTexture(t_robak);
    robak.back().sprite.setScale(0.7,0.7);
    short poz=0;
    poz=(std::rand()%368)+10;
    robak.back().sprite.setPosition(poz,0);
}

//funkcja wywoływana po złapaniu owoca
void Spadanie::zlap(int a)
{
    generuj_efekt(owoc[a].sprite.getPosition(),owoc[a].predkosc.y);
    owoc.erase(owoc.begin()+a);
    if(dzwiek)sound.play();
}

//funkcja wywoływana po złapaniu robaka
void Spadanie::zlap_r(int a)
{
    robak.erase(robak.begin()+a);
    if(dzwiek)sound_r.play();
}

//funkcja wywoływana po pominięciu owoca
void Spadanie::usun(int a)
{
    owoc.erase(owoc.begin()+a);
}
//funkcja wywoływana po pominięciu robaka
void Spadanie::usunr(int a)
{
    robak.erase(robak.begin()+a);
}

//funkcja wyświetlająca owoce i robaki na ekranie
void Spadanie::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    if(!owoc.empty())
        for(unsigned int i=0;i<owoc.size();i++)
        {
            target.draw(owoc[i].sprite);
        }
    if(!owoc.empty())
        for(unsigned int i=0;i<robak.size();i++)
        {

            target.draw(robak[i].sprite);
        }

    if(!particle.empty())
        for(unsigned int i=0;i<particle.size();i++)
        {
            target.draw(particle[i].sprite);
        }
}
//funkcja która odtwarza dźwięk gdy będzie koniec gry
void Spadanie::lost()
{
    if(dzwiek)sound_lost.play();
}

