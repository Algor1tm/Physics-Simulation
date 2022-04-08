#pragma once

#include <SFML/Graphics.hpp>

#include "RigidBody.hpp"
#include "../core/Vector2d.hpp"
#include "../core/Settings.hpp"


class Ball: public RigidBody{
private:
    float Density;
    float Radius;

    sf::CircleShape DrawShape;

    void DrawSpeed(sf::RenderWindow* wnd);
public:
    Ball(const Vector2d& StartPos, const Vector2d& StartSpeed, float Rad, float density, const sf::Color& clr);
    ~Ball() = default;

    // 1 - if selected by user, else - 0
    // (selected from start)
    bool selected;

    float getRadius() { return Radius; }
    void Draw(sf::RenderWindow* wnd);

    void EnableSelectedEfect(int thickness);
    void DisableSelectedEfect();

};

