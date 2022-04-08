#include "../../include/objects/SoftBody.hpp"


void SoftBody::Move(double time)
{
    for (auto& ball : Balls)
        ball->Move(time);
}


void SoftBody::Move(const Vector2d& distance)
{
    for (auto& ball : Balls)
        ball->Move(distance);
}


void SoftBody::Draw(sf::RenderWindow* wnd)
{
    for (auto& spring : Springs)
        spring->Draw(wnd);

    for (auto& ball : Balls)
        ball->Draw(wnd);
}


bool SoftBody::isInside(const Vector2d& mousePos)
{
    Vector2d maxp = getMaxPoint();
    Vector2d minp = getMinPoint();

    return mousePos.x >= minp.x && mousePos.y >= minp.y && \
        mousePos.x <= maxp.x && mousePos.y <= maxp.y;
}


void SoftBody::OnLeftMouseMove(const Vector2d& mousePos)
{
    Move(mousePos - getCenter());
}


void SoftBody::OnSelect(int thickness)
{
    for (auto& ball : Balls) {
        ball->OnSelect(selectThickness_);
        ball->DrawSpeed = false;
    }
}


void SoftBody::OnDeselect(int thickness)
{
    for (auto& ball : Balls)
        ball->OnDeselect(selectThickness_);
}


SoftBody::~SoftBody()
{
    for (auto& ball : Balls)
        delete ball;
    for (auto& spring : Springs)
        delete spring;
}




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


void SoftBody::Spring::Draw(sf::RenderWindow* wnd)
{
    sf::Vertex line[] = {
        sf::Vertex({ball1->getPos().x, ball1->getPos().y}),
        sf::Vertex({ball2->getPos().x, ball2->getPos().y})
    };

    wnd->draw(line, 2, sf::Lines);
}


