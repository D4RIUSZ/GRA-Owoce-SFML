#ifndef SILNIK_H
#define SILNIK_H
#include "gracz.h"
#include "plansza.h"
#include "spadanie.h"
#include "specjalne.h"


using namespace sf;
class Silnik
{
public:
    Silnik();
    virtual ~Silnik();
    void kolizja();
    void uruchomSilnik(RenderWindow *window,int tryb);

private:
    Gracz gracz;
    Plansza plansza;
    Spadanie spadanie;
    Specjalne special;
    int tryb;
    int dzwiek;
    int rdzwiek=1;
};

#endif // SILNIK_H
