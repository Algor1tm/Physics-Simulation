#include "../../include/objects/Ball.hpp"


Ball::Ball(const Vector2d& StartPos, const Vector2d& StartSpeed, float Rad, float density, const sf::Color& clr):
    RigidBody{StartPos, StartSpeed, Rad * Rad * Rad * density }, Density{density}, Radius{Rad}, selected{false}
{
    DrawShape.setRadius(Rad);
    DrawShape.setPointCount(100);
    DrawShape.setPosition(StartPos.x - Radius, StartPos.y - Radius);
    DrawShape.setFillColor(clr);
}


void Ball::DrawSpeed(sf::RenderWindow* wnd)
{
    Vector2d speed = getSpeed();
    Vector2d pos = getPos();
    Vector2d vec = 7 * speed + pos;
    Vector2d nvec = speed.getNormalized();
    float width;
    if(speed.getModule() < 5)
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
    DrawShape.setPosition(pos.x - Radius, pos.y - Radius);

    wnd->draw(DrawShape);

    if(selected)
        DrawSpeed(wnd);
}


void Ball::DisableSelectedEfect()
{
    AddPos(-Vector2d(DrawShape.getOutlineThickness(), DrawShape.getOutlineThickness()));

    DrawShape.setRadius(Radius);
    DrawShape.setOutlineThickness(0);
    DrawShape.setOutlineColor(DrawShape.getFillColor());

    selected = 0;
}


void Ball::EnableSelectedEfect(int thickness)
{
    float thickf = (float)thickness;
    DrawShape.setRadius(Radius - thickf);
    DrawShape.setOutlineThickness(thickf);
    DrawShape.setOutlineColor({0, 255, 0});

    AddPos(Vector2d(thickf, thickf));

    selected = 1;
}

