#pragma once

#include <SFML/Graphics.hpp>

#include "PhysicalObjects.hpp"
#include "../core/Vector2d.hpp"
#include "Line.hpp"
#include "Ball.hpp"


class Polygon: public Static, public DrawAble{
private:
    std::vector<Line*> lines;

    Vector2d MaxPoint;
    Vector2d MinPoint;

    int OutLineThickness;

public:
    // declare points only in CLOCKWISE order
    Polygon(std::vector<Vector2d> points, int Thickness);
    virtual ~Polygon();

    void Draw(sf::RenderWindow* wnd) override;

    bool isNear(Ball* ball);

    Line* getLine(int i){return lines[i];}
    unsigned getSizeofLines() {return lines.size();}
};

