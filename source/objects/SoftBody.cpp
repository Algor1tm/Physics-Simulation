#include "../../include/objects/SoftBody.hpp"


SoftBody::SoftBody()
    : MovAble(), Selectable(), numOfBalls_(0)
{

}


void SoftBody::Move(float time)
{
    for (auto& ball : Balls)
        ball->Move(time);
}


void SoftBody::Move(const Vector2d& distance)
{
    for (auto& ball : Balls)
        ball->Move(distance);
}


bool SoftBody::isNear(Ball* ball)
{
    Vector2d pos = ball->getPos();
    float radius = ball->getRadius();
    Vector2d maxp = getMaxPoint();
    Vector2d minp = getMinPoint();
    return pos.x <= maxp.x + radius && pos.y <= maxp.y + radius && \
           pos.x >= minp.x - radius && pos.y >= minp.y - radius;
}


void SoftBody::drawSpeed(sf::RenderWindow* window)
{
    Vector2d speed;
    for (auto& ball : Balls)
        speed += ball->getSpeed();
    speed = speed / (float)numOfBalls_;
    Vector2d pos = getCenter();

    Vector2d vec = 7 * 7 * speed + pos;
    Vector2d nvec = speed.getNormalized();
    float width = 4;
    Vector2d w = (2.f * width / (float)tan(M_PI / 6)) * nvec;
    Vector2d normal = { pos.y - vec.y, vec.x - pos.x };
    normal.normalize();

    sf::ConvexShape Arrow;
    Arrow.setFillColor({ 50, 200, 50 });

    Arrow.setPointCount(4);
    Arrow.setPoint(0, pos - width * normal);
    Arrow.setPoint(1, pos + width * normal);
    Arrow.setPoint(2, vec - w + width * normal);
    Arrow.setPoint(3, vec - w - width * normal);
    window->draw(Arrow);

    Arrow.setPointCount(3);
    Arrow.setPoint(0, vec - w - 2 * width * normal);
    Arrow.setPoint(1, vec - w + 2 * width * normal);
    Arrow.setPoint(2, vec);
    window->draw(Arrow);
}


void SoftBody::Draw(sf::RenderWindow* window)
{
    for (auto& spring : Springs)
        spring->Draw(window);

    for (auto& ball : Balls)
        ball->Draw(window);

    if (selected_)
        drawSpeed(window);
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


void SoftBody::OnRightMouseMove(const Vector2d& mousePos)
{
    for(auto& ball: Balls)
        ball->AddSpeed(0.03f * (mousePos - ball->getPos()) - ball->getSpeed());
}


void SoftBody::OnSelect(int thickness)
{
    for (auto& ball : Balls) 
    {
        ball->OnSelect(selectThickness_);
        ball->DrawSpeed = false;
    }
    selected_ = true;
}


void SoftBody::OnDeselect(int thickness)
{
    for (auto& ball : Balls)
        ball->OnDeselect(selectThickness_);

    selected_ = false;
}


SoftBody::~SoftBody()
{
    for (auto& ball : Balls)
        delete ball;
    for (auto& spring : Springs)
        delete spring;
}

