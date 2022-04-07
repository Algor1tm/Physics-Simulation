#pragma once

#include "SoftBody.hpp"
#include "../core/Vector2d.hpp"


class SoftRectangle: public SoftBody{
private:
    int width;
    int height;

public:
    SoftRectangle(const Vector2d& StartPos, const Vector2d& StartSpeed, int w, int h, int interval, int rad, float ballDensity,const sf::Color& clr);
    virtual ~SoftRectangle(){}

    void InnerForces() override;

    Vector2d getCenter() const override {return 0.5 * (Balls[0]->getPos() + Balls[Balls.size() - 1]->getPos());}
    Vector2d getMaxPoint() override;
    Vector2d getMinPoint() override;
};

