#pragma once

#include "SoftBody.hpp"
#include "../core/Vector2d.hpp"


class SoftRectangle: public SoftBody
{
public:
    SoftRectangle(const Vector2d& StartPos, const Vector2d& StartSpeed, int width, int height, const sf::Color& color);
    virtual ~SoftRectangle() = default;

    void InnerForces() override;
    
    Vector2d getCenter() const override;
    Vector2d getMaxPoint() override;
    Vector2d getMinPoint() override;

private:
    int width_;
    int height_;

    static const int interval = 17;
    static const int ballRad = 6;
    static const int ballDensity = 1;
};

