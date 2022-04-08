#pragma once

#include "SFML/Graphics.hpp"

#include "../core/Vector2d.hpp"


// ax + by + c = 0;
struct Line{
    float a;
    float b;
    float c;

    Vector2d Normal;
    float NormalModule;
    float Length;

    Vector2d Point1;
    Vector2d Point2;

    sf::Vertex vertices[4];
    sf::Color clr;
    int Thickness;


    Line(const Vector2d& p1, const Vector2d& p2, int LineThickness, const sf::Color& color = sf::Color::White);
    virtual ~Line() = default;

    float Distance(const Vector2d& point);
    void Draw(sf::RenderWindow* wnd);
};

