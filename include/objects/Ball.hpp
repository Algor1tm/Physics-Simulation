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

    void drawSpeed(sf::RenderWindow* window);
public:
    Ball(const Vector2d& StartPos, const Vector2d& StartSpeed, float Rad, float density, const sf::Color& clr);
    ~Ball() = default;

    bool DrawSpeed;

    bool isInside(const Vector2d& mousePos) override;

    void OnLeftMouseMove(const Vector2d& mousePos) override;
    void OnRightMouseMove(const Vector2d& mousePos) override;

    void OnSelect(int thickness) override;
    void OnDeselect(int thickness) override;

    void Draw(sf::RenderWindow* window) override;

    float getRadius() { return Radius; }
};

