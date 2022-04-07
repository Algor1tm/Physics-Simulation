#pragma once

#include <SFML/Graphics.hpp>

#include "PhysicalObjects.hpp"
#include "../core/Vector2d.hpp"
#include "../core/Settings.hpp"


class Ball: public MovAble, public DrawAble{
private:
    Vector2d Speed;
    Vector2d Pos;
    Vector2d Force;
    float Mass;
    float Density;
    float Radius;

    sf::CircleShape DrawShape;

    void DrawSpeed(sf::RenderWindow* wnd);
public:
    Ball(const Vector2d& StartPos, const Vector2d& StartSpeed, float Rad, float density, const sf::Color& clr);
    ~Ball() = default;

    // 1 - if selected by user, else - 0(selected from start)
    bool selected;

    float getRadius(){return Radius;}
    Vector2d getSpeed()const {return Speed;}
    Vector2d getPos() const {return Pos;}
    Vector2d getForce() const {return Force;}
    float getMass() const {return Mass;}

    void setSpeed(const Vector2d& newSpeed) {Speed = newSpeed;}
    void setPos(const Vector2d& newPos) {Pos = newPos;}
    void setForce(const Vector2d& newForce) {Force = newForce;}

    void Draw(sf::RenderWindow* wnd);

    void EnableSelectedEfect(int thickness);
    void DisableSelectedEfect();

};

