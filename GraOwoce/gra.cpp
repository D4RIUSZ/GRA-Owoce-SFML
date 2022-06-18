#include "gra.h"
#include <string>
#include <iostream>


Gra::Gra()
{
    //tworzenie okna i ikony okna
    window->create(VideoMode(400,600),"ZbierzOwocki");
    sf::Image ikona;
    ikona.loadFromFile("data/ikona.png");
    window->setIcon(ikona.getSize().x,ikona.getSize().y,ikona.getPixelsPtr());

    //tworzenie opisu do zakładki opis
    std:string text_omnie;

            text_omnie+= "Wykonal:";
            text_omnie+= '\n';
            text_omnie+= "Dariusz Szymanski";
            text_omnie+= '\n';
            text_omnie+= '\n';
            text_omnie+= "Kierunek";
            text_omnie+= '\n';
            text_omnie+= "Air";
    sf::String tekst(text_omnie);

    //nadanie domyślnego trybu gry
    tryb=1;

    //wczytanie pliku z czcionką Arial
    if(!font.loadFromFile("data/Arial.ttf"))
    {
        std::cout<<"Błąd wczytywania czcionki Arial"<<std::endl;
        return;
    }


    status = MENU;
    przyciemnienie.setFillColor(sf::Color(0,0,0,220));
    przyciemnienie.setSize(sf::Vector2f(400,600));
    txt_tworcy.setFont(font);
    txt_tworcy.setCharacterSize(20);
    txt_tworcy.setPosition(100,100);
    txt_tworcy.setFillColor(sf::Color::White);
    txt_tworcy.setString(tekst);

    //tworzenie zakładek w Menu

    str[0]="Graj";
    str[1]="Wyniki";
    str[2]="O mnie";
    str[3]="Zamknij Gre";

    //Nazwy trybu gier
    strtryb[0]="Easy";
    strtryb[1]="Normal";
    strtryb[2]="Hard";

    //teztury służące do podswietelnia trybu gry
    t_jablko_jasne.loadFromFile("data/jablko1.png");
    t_jablko_ciemne.loadFromFile("data/jablko_ciemne.png");

    //tworzenie zakładki trybu gry
    for (int i=0; i<3;i++)
    {
        jablko_opcji[i].setTexture(t_jablko_ciemne);
        jablko_opcji[i].setOrigin(8,0);
        jablko_opcji[i].setPosition(window->getSize().x/2+((i-1)*40),window->getSize().y/4);
    }
    jablko_opcji[tryb-1].setTexture(t_jablko_jasne);
    opcja.setFont(font);
    opcja.setCharacterSize(25);
    opcja.setString(strtryb[tryb-1]);
    opcja.setPosition(window->getSize().x/2-(opcja.getGlobalBounds().width/2),window->getSize().y/5);

}

Gra::~Gra()
{
}

//metoda uruchamiająca grę z zadanym trybem gry
void Gra::single()
{
    Silnik silnik;
    silnik.uruchomSilnik(window,tryb);
    status=MENU;
}

//metoda która uruchamia sie w mainie i sprawdza jaki Gamestat jest
void Gra::uruchomGre()
{
    while(status!=KONIEC)
    {
        switch(status)
        {
        case MENU:
            menu();
            break;
        case GRA:
            single();
            break;

        }
    }
}

void Gra::menu()
{
    window->setFramerateLimit(60);
    sf::Text tytul("Zbierz Owoce",font,50);
    tytul.setStyle(sf::Text::Bold);
    tytul.setPosition((window->getSize().x)/2-tytul.getGlobalBounds().width/2,20);

    //wyswietlenie napisów w menu
    for(int i =0; i<ile; i++)
    {
        tekst[i].setFont(font);
        tekst[i].setCharacterSize(45);

        tekst[i].setString(str[i]);
        tekst[i].setPosition((window->getSize().x)/2-tekst[i].getGlobalBounds().width/2,230+i*80);
    }
    sf::Clock zegar;


    while(status == MENU || status==O_MNIE || status==STATYSTYKA)
    {
        Vector2f mouse(Mouse::getPosition(wygrana));
        Event event;

        while(window->pollEvent(event))
        {
            // wybór myszką danej zakładki gry
            if((status==O_MNIE || status==STATYSTYKA)&&sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                status=MENU;
            }
            else if ( tekst[0].getGlobalBounds().contains(mouse)&& sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                status= GRA;
            }
            else if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            {
                status = KONIEC;
            }
            else if(tekst[1].getGlobalBounds().contains(mouse) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                status = STATYSTYKA;
                readstatistics();
            }
            else if(tekst[2].getGlobalBounds().contains(mouse) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                status = O_MNIE;
            }
            else if(tekst[3].getGlobalBounds().contains(mouse) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                status = KONIEC;
            }

            for (int i=0; i<ile ; i++)
            {
                //podswietlenie trybu gry w momencie kiedy sie wybierze dany tryb
                if (jablko_opcji[i].getGlobalBounds().contains(mouse)&& sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    jablko_opcji[tryb-1].setTexture(t_jablko_ciemne);
                    tryb=i+1;
                    jablko_opcji[tryb-1].setTexture(t_jablko_jasne);
                    opcja.setString(strtryb[tryb-1]);
                    opcja.setPosition(window->getSize().x/2-(opcja.getGlobalBounds().width/2),window->getSize().y/5);
                }
            }
           }

        // Podswietlenie napisów
        for (int i=0; i<ile; i++)
        {
            if(tekst[i].getGlobalBounds().contains(mouse))
                tekst[i].setFillColor(Color::Cyan);
            else
                tekst[i].setFillColor(Color::White);
        }

        zegar.restart();

        // Wyswietlenie tego w oknie

        window->clear();
        window->draw(menutlo);
        window->draw(tytul);

        for(int i=0; i<ile; i++)
        {
            window->draw(tekst[i]);
        }

        for(int i=0; i<3; i++)
        {
            window->draw(jablko_opcji[i]);
        }
        window->draw(opcja);
        if(status==O_MNIE)
        {
            window->draw(przyciemnienie);
            window->draw(txt_tworcy);
        }
        if(status==STATYSTYKA)
        {
            drawstatistics();
        }

        window->display();
    }
}

void Gra::readstatistics()      //wczytanie pliku rekord
{
    std::fstream plik;
    plik.open("config/rekord.dat",std::ios::in);
    unsigned int record[] = {0,0,0};
    for(int i=0;i<3;i++)
        plik>>record[i];
    plik.close();

    int width = window->getSize().x;
    int height = window->getSize().y;

    for(int i=0;i<16;i++)
    {
        stattxt[i].setFont(font);
        stattxt[i].setCharacterSize(20);
    }
    stattxt[0].setCharacterSize(30);
    stattxt[0].setString("Tabela wynikow");
    stattxt[0].setPosition(width/2 - stattxt[0].getGlobalBounds().width/2,height/11);
    for(int i=0;i<3;i++)
    {
        stattxt[5*i+1].setString(strtryb[i]);
        stattxt[5*i+1].setPosition(width/2 - stattxt[3*i+1].getGlobalBounds().width/2,(height/11)*(3*i+2));
        stattxt[5*i+2].setString("Rekord: ");
        stattxt[5*i+2].setPosition(width/5,(height/11)*(3*i+3));
        stattxt[5*i+3].setString(std::to_string(record[i]));
        stattxt[5*i+3].setPosition(stattxt[5*i+2].getGlobalBounds().left + stattxt[5*i+2].getGlobalBounds().width + 10, (height/11)*(3*i+3));

    }
}

//wyswietlenie wyników w oknie
void Gra::drawstatistics()
{
    window->draw(przyciemnienie);
    for(int i=0;i<16;i++)
    {
        window->draw(stattxt[i]);
    }
}

