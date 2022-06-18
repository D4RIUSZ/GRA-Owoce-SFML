#ifndef GRACZ_H
#define GRACZ_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Gracz: public sf::Drawable, sf::Transformable
{
public:
    Gracz();
    virtual ~Gracz();

    enum Status     //status jaki jest koszyk
    {
        PRAWO,
        LEWO,
        STOJ
    };

    int getStatus();
    void update(Clock &zegar,Clock &zeg_anim);
    void stop();
    void przesun_w_prawo();
    void przesun_w_lewo();
    void rusz_koszyk(int pozycja);
    sf::Sprite sprite;
    sf::RectangleShape dokolizji;
protected:
    int klatka_animacji;
private:
    sf::Texture texture;
    sf::Texture t_kolizji;
    Status status;
    float speed;
    float frame;
    bool zwrot;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const; //metoda wyswietlająca koszyk na ekranie
};

#endif // GRACZ_H
