#include "plansza.h"

Plansza::Plansza()
{
    //wczytywanie plików audio i wideo

    t_tlo.loadFromFile("data/tlo1.png");
    t_menu.loadFromFile("data/deska1.png");
    t_zycia.loadFromFile("data/jablko1.png");
    font.loadFromFile("data/Arial.ttf");
    buffer_lost.loadFromFile("data/koniec.ogg");

    //dodawanie dźwięku audio
    sound_lost.setBuffer(buffer_lost);

    //ustawianie danych na oknie gry
    txt_punkty.setFont(font);
    txt_punkty.setCharacterSize(20);
    txt_punkty.setPosition(85,550);
    txt_czas.setFont(font);
    txt_czas.setCharacterSize(20);
    txt_czas.setPosition(330,570);
    txt_przegrana.setFont(font);
    txt_przegrana.setFillColor(sf::Color::Red);
    txt_przegrana.setCharacterSize(40);
    txt_przegrana.setPosition(50,75);
    txt_przegrana.setRotation(30);
    txt_przegrana.setString("KONIEC GRY!");
    tlo.setTexture(t_tlo);
    menu.setTexture(t_menu);
    //wyswietlanie liczby żyć na ekranie
    for(int i=0;i<3;i++)
    {
        zycia[i].setTexture(t_zycia);
        zycia[i].setScale(0.8f,0.8f);
        zycia[i].setPosition(165+i*30,573);
    }
    menu.setPosition(0,550);
    ilosc_zyc=3;
    punkty=0;
    straty=0;
    czas=0;
    txt_punkty.setString(std::to_string(punkty));
    txt_czas.setString(std::to_string(((int)czas)%60));

}



Plansza::~Plansza()
{
    sprawdz_wynik();
}

//zwiększa liczbę punktóW na ekranie
void Plansza::zwieksz_punkty(int ile)
{
    punkty+=ile;
}

void Plansza::update(sf::Clock czass)//ogarnia zegary i cyferki w dolnym panelu
{
    czas+=czass.getElapsedTime().asSeconds();
    std::string minuty,sekundy;
    if(czas/60 < 10)minuty="0"; else minuty="";
    minuty+=std::to_string(((int)czas)/60);
    if(((int)czas)%60<10)sekundy="0"; else sekundy="";
    sekundy+=std::to_string(((int)czas)%60);
    txt_czas.setString(minuty + ":" + sekundy);

    txt_punkty.setString(std::to_string(punkty));

    //if(straty==(4-tryb))
    if(straty==1)
    {
        if(ilosc_zyc>0)ilosc_zyc--;
        straty=0;
    }
    if(ilosc_zyc==0)sprawdz_wynik();

}

//Wczytuje rekord z pliku
void Plansza::wczytaj_rekord()
{
    std::fstream plik;
    plik.open("config/rekord.dat",std::ios::in);
    int liczba[3]={0,0,0};
    for(int i=0; i<3; i++)
        plik>>liczba[i];
    txt_best.setFont(font);
    txt_best.setCharacterSize(20);
    txt_best.setPosition(85,573);
    txt_best.setString(std::to_string(liczba[tryb-1]));
    plik.close();
}
//Funkcja sprawdza czy wynik nie jest większy niż ten co jest w pliku
void Plansza::sprawdz_wynik()
{
    std::fstream plik;
    plik.open("config/rekord.dat",std::ios::in);
    int rekord[3]={0,0,0};
    for(int i=0; i<3; i++)
        plik>>rekord[i];
    plik.close();
    if(punkty>rekord[tryb-1])
    {
        rekord[tryb-1]=punkty;
        plik.open("config/rekord.dat",std::ios::out | std::ios::trunc);
        for(int i=0; i<3; i++)
            plik<<rekord[i]<<" ";
        plik.close();
    }
}

//wyświetla na ekranie punkty,czas,rekord oraz ilość żyć
void Plansza::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(menu);
    target.draw(txt_punkty);
    target.draw(txt_czas);
    target.draw(txt_best);
    //
    for(int i=0; i<ilosc_zyc; i++)
    {
        target.draw(zycia[i]);
    }
    if(ilosc_zyc==0)
    {
        target.draw(txt_przegrana);
    }
}
