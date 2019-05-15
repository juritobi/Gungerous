#ifndef COLISIONES_H
#define COLISIONES_H

#include "Game.h"
#include "Map.h"
#include "App.h"



class Colisiones
{
    public:
        static Colisiones* getColisiones();

        bool entorno();


        void palanca();
        void importalte();
        void pup();

        void camaramove();
        void espadaenemigo();
        void limpiar();
        void enemigo();




    private:
        static Colisiones* colisiones;
        Colisiones();
        sf::Clock reloj;
        sf::Clock reloj2;

        Game* mGame;


};

#endif // COLISIONES_H
