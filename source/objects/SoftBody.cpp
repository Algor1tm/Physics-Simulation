#include "../../include/objects/SoftBody.hpp"


SoftBody::Spring::Spring(Ball* b1, Ball* b2)
{
    ball1 = b1;
    ball2 = b2;

    DefaultVector = ball1->getPos() - ball2->getPos();
    DefaultLength = DefaultVector.getModule();
}


void SoftBody::Spring::ApplySelfCollision()
{
    Vector2d dpos = ball1->getPos()- ball2->getPos();

    float m = dpos.getModule();
    float d = ball1->getRadius() + ball2->getRadius() - m - 1;
    if(d >= 0 && m != 0){
        dpos = dpos / (2 * m);

        ball1->AddPos(dpos);
        ball2->AddPos(-dpos);
    }
}


void SoftBody::Spring::ApplyDampingFactor()
{
    Vector2d dpos = ball2->getPos() - ball1->getPos();
    dpos.normalize();

    Vector2d dspeed = ball2->getSpeed() - ball1->getSpeed();
    float D =  Kd * Vector2d::DotProduct(dspeed, dpos);
    Vector2d Damping = D * dpos;

    ball1->AddForce(Damping);
    ball2->AddForce(-Damping);
}


void SoftBody::Spring::ApplyHookesForce()
{
    Vector2d dpos = ball1->getPos() - ball2->getPos();
    float m = dpos.getModule();
    float dx = m - DefaultLength;

    Vector2d F = Ks * dx / m * dpos;

    ball1->AddForce(-F);
    ball2->AddForce(F);
}


void SoftBody::Draw(sf::RenderWindow* wnd)
{
    for(auto& spring: Springs)
        spring->Draw(wnd);

    for(auto& ball: Balls)
        ball->Draw(wnd);
}


void SoftBody::EnableSelectedEfect(int thickness)
{
    for(auto& ball:Balls){
        ball->EnableSelectedEfect(thickness);
        ball->selected = 0;
    }
}

void SoftBody::DisableSelectedEfect()
{
    for(auto& ball:Balls)
        ball->DisableSelectedEfect();
}


void SoftBody::Spring::Draw(sf::RenderWindow* wnd){
    sf::Vertex line[] = {
        sf::Vertex({ball1->getPos().x, ball1->getPos().y}),
        sf::Vertex({ball2->getPos().x, ball2->getPos().y})
    };

    wnd->draw(line, 2, sf::Lines);

}

SoftBody::~SoftBody(){
    for(auto& ball: Balls)
        delete ball;
    for(auto& spring: Springs)
        delete spring;
}

