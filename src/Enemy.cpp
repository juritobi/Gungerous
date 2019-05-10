#include "../include/Enemy.h"
#include "../include/AssetManager.h"
#include "../include/App.h"


Enemy::Enemy(sf::Vector2u vec, Player* player, int vida, int type,sf::Vector2f pos)//comento cosas para probar que funciona, cuando ya esté se descomentan las dos
:animar(0.1f,sf::Vector2u(4,4),"enem")
,animar2(0.15f,sf::Vector2u(8,3),"enem2")
,direccion(sf::Vector2f(0,0))
{
    sala=0;
    cd=(((double)rand()) / ((double)RAND_MAX))+1;
    this->type=type;
    firstState.pos=sf::Vector2f(pos.x,pos.y);
    firstState.hitbox=&hitb;
    lastState=firstState;
    speed=100.f;
    this->player = player;
    this->vida = vida;
    derecha = true;
    if(type==0){
    body.setTexture(&AssetManager::getAssetManager()->GetTexture("enem"));
    fila = 0;
    body.setSize(sf::Vector2f(100.0f, 100.0f));
    }
    else{
    body.setTexture(&AssetManager::getAssetManager()->GetTexture("enem2"));
    fila = 0;
    body.setSize(sf::Vector2f(120.0f, 120.0f));
    }


    //body.setTextureRect(sf::IntRect(100, 100, 100, 100));
    body.setOrigin(body.getSize()/2.0f);
    body.setPosition(pos);

    hitb.setSize(sf::Vector2f(70.0f, 35.0f));
    hitb.setOrigin(hitb.getSize()/2.0f);
    hitb.setPosition(body.getPosition());

}

void Enemy::update(){
    direccion=player->getPosition() - body.getPosition();
    direccion=App::getApp()->normalizar(direccion);
    Animar();


    if(sala==player->getsala())
    {
        if(type==0)
        Mover();

        if(type==1 && delay.getElapsedTime().asSeconds()>cd){
        disparar();
        delay.restart();
        }
    }

}

void Enemy::Mover()//mueve al enemigo hacia el player
{


    sf::Time elapsedTime = App::getApp()->getElapsedTime();

    firstState=lastState;

    sf::Vector2f movement(0.f, 0.f);

    movement=direccion*speed;




    lastState.pos += movement * elapsedTime.asSeconds();
    lastState.hitbox->setPosition(lastState.pos+sf::Vector2f(-15.0f,-5.0f));


}


void Enemy::disparar()
{

Proyectil *bala= new Proyectil(hitb.getPosition(), player);
balas.push_back(bala);


}

void Enemy::Animar()
{
    //hitb.setPosition(body.getPosition()+sf::Vector2f(-35.0f,-30.0f));

    sf::Vector2f posicion(player->getBody().getPosition()-body.getPosition());

    if(posicion.x!=.0f || posicion.y!=0.0f)
    posicion=App::getApp()->normalizar(direccion);


     derecha=true;

     if(type==0){
     animar.animar(fila, App::getApp()->getElapsedTime(), derecha, false);
     fila=0;
     body.setTextureRect(animar.uvRect);
     }
     else{
     fila=2;
     animar2.animar(fila, App::getApp()->getElapsedTime(), derecha, false);
     body.setTextureRect(animar2.uvRect);
     }
}

void Enemy::renderMove(float tick){

    body.setPosition(firstState.pos.x*(1-tick)+lastState.pos.x*tick,firstState.pos.y*(1-tick)+lastState.pos.y*tick);
    hitb.setPosition(body.getPosition()+sf::Vector2f(0.f,-15.0f));
}

void Enemy::hitted(){

    sf::Vector2f vec = sf::Vector2f(body.getPosition()-player->getPosition());
    vec= App::getApp()->normalizar(vec);
    lastState.pos=lastState.pos+vec*speed;
    if(vida>0)
    vida = vida-1;

    if(vida == 0)
    body.setFillColor(sf::Color::Red);



}

std::vector<Proyectil*> Enemy::getbalas()
{
return balas;
}

sf::RectangleShape Enemy::getbody()//obtener el body
{
    return body;
}
sf::RectangleShape Enemy::getHitbox()//obtener el body
{
    return hitb;
}

void Enemy::setsala(int i)
{
sala=i;
}

sf::Clock * Enemy::getclock()
{
return &delay;
}

