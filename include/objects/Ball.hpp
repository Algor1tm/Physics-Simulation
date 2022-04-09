#pragma once

#include <SFML/Graphics.hpp>

#include "RigidBody.hpp"
#include "../core/Vector2d.hpp"
#include "../core/Settings.hpp"


class Ball: public RigidBody
{
public:
    Ball(const Vector2d& StartPos, const Vector2d& StartSpeed, float Rad, float density, const sf::Color& color);
    ~Ball() = default;

    bool isInside(const Vector2d& mousePos) override;
    // user moving object
    void OnLeftMouseMove(const Vector2d& mousePos) override;
    // user change speed
    void OnRightMouseMove(const Vector2d& mousePos) override;

    void OnSelect(int thickness) override;
    void OnDeselect(int thickness) override;

    void Draw(sf::RenderWindow* window) override;

    float getRadius() const { return radius_; }
    // if true - drawing speed(arrow)
    bool DrawSpeed;
private:
    float density_;
    float radius_;

    sf::CircleShape toDraw_;

    void drawSpeed(sf::RenderWindow* window);
};

