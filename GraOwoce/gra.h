#ifndef GRA_H
#define GRA_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <Windows.h>
#include "silnik.h"
#include "MenuTlo.h"

using namespace std;
using namespace sf;

class Gra
{
public:
    MenuTlo menutlo;                    //tworzenie klasy menu tło
    RenderWindow wygrana;               //tworzenie okna wygrana
    RenderWindow *window=&wygrana;
    Gra();                              //konstruktor klasy gra
    virtual ~Gra();                     //destruktor klasy gra
    void uruchomGre();                  //metody uruchamijące gre
    void single();
    int tryb;                           //tworzenie zmiennej aby móc określić tryb gry
protected:
    enum GameStat {MENU,GRA,STATYSTYKA,O_MNIE,KONIEC};
    GameStat status;                       //tworzenie zmiennej Enum aby móc wywołać
                                           //daną opcje w menu
private:
    Font font;                          //metody pozwalające wyświetlić rekordy z poszczególnych trybów gier
    void drawstatistics();
    void readstatistics();
    void menu();
    sf::RectangleShape o_mnie,przyciemnienie;       //tworzenie zakładki gdzie wyświetlać się bedą rekordy oraz
    sf::Text txt_tworcy;                            //dane tworcy
    const int ile = 4;                              //zmienna która pomaga użyć podświetlenia w menu w grze
    string str[4];                                  //string zawierający jaką zakładkę ma wyświetlić w menu
    string strtryb[3];                              // zawierający jaki ma tryb odpalić
    sf::Sprite jablko_opcji[3];                     // do podswietlenia wyboru grafiki trybu gry
    sf::Sprite tlo;                                 // tlo
    sf::Texture t_tlo;                              // do wczytania textury tla
    sf::Text stattxt[16];                           // do wyswietlania rekordów
    sf::Text opcja;                                 //  Do wyswietlenia trybu gry
    sf::Text tekst[4];                              //do wyswietlenia zakladki o mnie
    sf::Texture t_jablko_jasne, t_jablko_ciemne;    // do podswietlenia trybu gry
};

#endif // GRA_H
