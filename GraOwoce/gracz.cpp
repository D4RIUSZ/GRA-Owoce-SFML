
#include "gracz.h"

//tworzenie klasy koszyk
Gracz::Gracz()
{
        texture.loadFromFile("data/koszyk1.png");

       sprite.setTexture(texture);


       sprite.setOrigin(32,0);
       sprite.setPosition(325/2,500);

       dokolizji.setSize(sf::Vector2f(50,1));
       dokolizji.setPosition(325/2,510);
       dokolizji.setOrigin(25,0);

       //nadanie domyslnych wartosci koszyka

       status = STOJ;
       frame = 1;       //przechylanie koszyka
       speed = 5.0f;    //predkosc poruszania koszyka
       zwrot = 1;       //zwrot przehylania sie koszyka
   }

   Gracz::~Gracz()
   {

   }

   void Gracz::update(Clock &zegar,Clock &zeg_anim)
   {
       if(status == STOJ)
       {
           frame=0;
           sprite.setRotation(2*frame);
           dokolizji.setRotation(2*frame);
           return;
       }

       float czas=zegar.getElapsedTime().asSeconds();
       czas*=60;

       //Poruszanie się koszykiem
       if(sprite.getPosition().x > 32 && status==LEWO)
       {
           sprite.move(speed*(-1.0f)*czas,0);
           dokolizji.move(speed*(-1.0f)*czas,0);
       }
       if(sprite.getPosition().x < 368 && status==PRAWO)
       {
           sprite.move(speed*(1.0f)*czas,0);
           dokolizji.move(speed*(1.0f)*czas,0);
       }

       //Kołysanie koszyka
       if(zeg_anim.getElapsedTime() > sf::seconds(0.025))
       {
           if(frame <6 && frame > -6)
               zwrot ? frame-- : frame++;
           else
           {
               zwrot=!zwrot;
               zwrot ? frame-- : frame++;
           }
               sprite.setRotation(2*frame);
               dokolizji.setRotation(2*frame);
       }
   }

   //metoda wyswietlajaca koszyk
   void Gracz::draw(sf::RenderTarget &target, sf::RenderStates states) const
   {
       states.transform *= getTransform();
       target.draw(sprite);
   }

   //Ustawianie statusu koszyka

   void Gracz::stop()
   {
       status = STOJ;
       frame = 0;
   }

   void Gracz::przesun_w_lewo()
   {
       status = LEWO;
   }
   void Gracz::przesun_w_prawo()
   {
       status = PRAWO;
   }

   int Gracz::getStatus()
   {
       return status;
   }


