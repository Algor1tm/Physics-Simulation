#include "../../include/objects/Ball.hpp"


Ball::Ball(const Vector2d& StartPos, const Vector2d& StartSpeed, float Rad, float density, const sf::Color& clr)
{
    Pos = StartPos;
    Speed = StartSpeed;
    Density = density;
    Force = {0, 0};
    Radius = Rad;
    Mass = Radius * Radius * Radius * Density;

    DrawShape.setRadius(Rad);
    DrawShape.setPointCount(100);
    DrawShape.setPosition(Pos.x - Radius, Pos.y - Radius);
    DrawShape.setFillColor(clr);

    selected = 0;

}

void Ball::DrawSpeed(sf::RenderWindow* wnd){
    Vector2d vec = 7 * Speed + Pos;
    Vector2d nvec = 1 / Speed.getModule() * Speed;
    float width;
    if(Speed.getModule() < 5)
        width = 3.f;
    else
        width = 4.f;
    Vector2d w = (2.f * width / (float)tan(M_PI / 6)) * nvec;
    Vector2d normal = {Pos.y - vec.y, vec.x - Pos.x};
    normal.normalize();

    sf::ConvexShape Arrow;
    Arrow.setFillColor({50, 200, 50});

    Arrow.setPointCount(4);
    Arrow.setPoint(0, Pos -  width * normal);
    Arrow.setPoint(1, Pos + width * normal);
    Arrow.setPoint(2, vec - w + width * normal);
    Arrow.setPoint(3, vec - w - width * normal);
    wnd->draw(Arrow);

    Arrow.setPointCount(3);
    Arrow.setPoint(0, vec - w - 2 * width * normal);
    Arrow.setPoint(1, vec - w + 2 * width * normal);
    Arrow.setPoint(2, vec);
    wnd->draw(Arrow);

}


void Ball::Draw(sf::RenderWindow* wnd){
    DrawShape.setPosition(Pos.x - Radius, Pos.y - Radius);

    wnd->draw(DrawShape);

    if(selected)
        DrawSpeed(wnd);
}


void Ball::DisableSelectedEfect(){
    Pos -= Vector2d(DrawShape.getOutlineThickness(), DrawShape.getOutlineThickness());

    DrawShape.setRadius(Radius);
    DrawShape.setOutlineThickness(0);
    DrawShape.setOutlineColor(DrawShape.getFillColor());

    selected = 0;
}

void Ball::EnableSelectedEfect(int thickness){
    float thickf = (float)thickness;
    DrawShape.setRadius(Radius - thickf);
    DrawShape.setOutlineThickness(thickf);
    DrawShape.setOutlineColor({0, 255, 0});

    Pos += Vector2d(thickf, thickf);

    selected = 1;
}

