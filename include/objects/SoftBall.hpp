#pragma once

#include "SoftBody.hpp"
#include "../core/Vector2d.hpp"


class SoftBall: public SoftBody{
public:
    SoftBall(const Vector2d& StartPos, const Vector2d& StartSpeed, float BodyRad, int BallCount, const sf::Color& color);
    virtual ~SoftBall(){}

    void InnerForces() override;

    Vector2d getCenter() const override {return 0.5 * (Balls[0]->getPos() + Balls[Balls.size()/ 2]->getPos());}
    Vector2d getMaxPoint() override;
    Vector2d getMinPoint() override;

private:
    float radius_;

    static const int ballRad = 5;
    static const int ballDensity = 1;
    static const int nRT = 10000;
    static const int areaScale = 20000;

    // Pressure * Volume = nRT
    void applyEqautionOfIdealGas();
    float computeArea() const;
};

