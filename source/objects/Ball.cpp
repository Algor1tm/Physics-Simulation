#include "../../include/objects/Ball.hpp"


Ball::Ball(const Vector2d& StartPos, const Vector2d& StartSpeed, float Rad, float density, const sf::Color& color):
    RigidBody{ StartPos, StartSpeed, Rad * Rad * Rad * density }, 
    density_{density}, radius_{Rad}, DrawSpeed(false)
{
    toDraw_.setRadius(Rad);
    toDraw_.setPointCount(100);
    toDraw_.setPosition(StartPos.x - radius_, StartPos.y - radius_);
    toDraw_.setFillColor(color);
}


inline void Ball::OnLeftMouseMove(const Vector2d& mousePos)
{ 
    Move(mousePos - getPos()); 
}


inline void Ball::OnRightMouseMove(const Vector2d& mousePos)
{ 
    AddSpeed(0.2f * (mousePos - getPos()) - getSpeed()); 
}


inline bool Ball::isInside(const Vector2d& mousePos)
{
    return Vector2d::Distance(getPos(), mousePos) < radius_;
}


void Ball::OnSelect(int thickness)
{
    float thickf = (float)thickness;
    toDraw_.setRadius(radius_ - thickf);
    toDraw_.setOutlineThickness(thickf);
    toDraw_.setOutlineColor({ 0, 255, 0 });

    AddPos(Vector2d(thickf, thickf));

    DrawSpeed = selected_ = true;
}


void Ball::OnDeselect(int thickness)
{
    AddPos(-Vector2d(toDraw_.getOutlineThickness(), toDraw_.getOutlineThickness()));

    toDraw_.setRadius(radius_);
    toDraw_.setOutlineThickness(0);
    toDraw_.setOutlineColor(toDraw_.getFillColor());

    DrawSpeed = selected_ = false;
}


void Ball::drawSpeed(sf::RenderWindow* wnd)
{
    Vector2d speed = getSpeed();
    Vector2d pos = getPos();
    Vector2d vec = 7 * speed + pos;
    Vector2d nvec = speed.getNormalized();
    float width;
    if(speed.getLength() < 5)
        width = 3.f;
    else
        width = 4.f;
    Vector2d w = (2.f * width / (float)tan(M_PI / 6)) * nvec;
    Vector2d normal = {pos.y - vec.y, vec.x - pos.x};
    normal.normalize();

    sf::ConvexShape Arrow;
    Arrow.setFillColor({50, 200, 50});

    Arrow.setPointCount(4);
    Arrow.setPoint(0, pos -  width * normal);
    Arrow.setPoint(1, pos + width * normal);
    Arrow.setPoint(2, vec - w + width * normal);
    Arrow.setPoint(3, vec - w - width * normal);
    wnd->draw(Arrow);

    Arrow.setPointCount(3);
    Arrow.setPoint(0, vec - w - 2 * width * normal);
    Arrow.setPoint(1, vec - w + 2 * width * normal);
    Arrow.setPoint(2, vec);
    wnd->draw(Arrow);
}


void Ball::Draw(sf::RenderWindow* wnd)
{
    Vector2d pos = getPos();
    toDraw_.setPosition(pos.x - radius_, pos.y - radius_);

    wnd->draw(toDraw_);
     
    if(DrawSpeed)
        drawSpeed(wnd);
}
