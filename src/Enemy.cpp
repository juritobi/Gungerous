#include "../include/Enemy.h"
#include "../include/AssetManager.h"
#include "../include/App.h"


Enemy::Enemy(sf::Vector2u vec, Player* player, int* vida)//comento cosas para probar que funciona, cuando ya esté se descomentan las dos
:animar(0.1f,sf::Vector2u(4,4),"enem")
,direccion(sf::Vector2f(0,0))
{
    this->vec.x = vec.x;
    this->vec.y = vec.y;
    this->player = player;
    this->vida = vida;

    fila = 0;
    derecha = true;

    body.setTexture(&AssetManager::getAssetManager()->GetTexture("enem"));
    body.setSize(sf::Vector2f(100.0f, 100.0f));
    //body.setTextureRect(sf::IntRect(100, 100, 100, 100));
    body.setOrigin(body.getSize()/2.0f);
    body.setPosition(512.0f, 128.0f);

    hitb.setSize(sf::Vector2f(70.0f, 35.0f));
    hitb.setPosition(body.getPosition());
}

void Enemy::update(){
    Perseguir();
    Animar();
    //Mover();
}

sf::Vector2f Enemy::Perseguir()//se normaliza la dirección por la que tiene que perseguir
{

    direccion=player->getPosition() - body.getPosition();
    /*float normalizar = sqrt((direccion.x * direccion.x) + (direccion.y * direccion.y));
    sf::Vector2f normalizado(direccion.x/normalizar, direccion.y/normalizar);*/

}

void Enemy::Mover(float x, float y)//mueve al enemigo hacia el player
{

    body.setPosition(body.getPosition().x + x, body.getPosition().y + y);
    *vida = *vida - 1;

    if(*vida==0)
    {

        std::cout<<"muerto"<<std::endl;
        body.setFillColor(sf::Color::Red);


    }

}

void Enemy::Animar()
{
    hitb.setPosition(body.getPosition()+sf::Vector2f(-35.0f,-30.0f));

    sf::Vector2f posicion(player->getBody().getPosition()-body.getPosition());

    if(posicion.x!=.0f || posicion.y!=0.0f)
    posicion=Perseguir();


     fila=0;
     derecha=true;


     animar.animar(fila, App::getApp()->getElapsedTime(), derecha, true);
     body.setTextureRect(animar.uvRect);
     body.move(velocidad*posicion);
}

sf::RectangleShape Enemy::getbody()//obtener el body
{

    return body;

}

