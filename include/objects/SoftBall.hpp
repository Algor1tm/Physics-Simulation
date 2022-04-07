#pragma once

#include "SoftBody.hpp"
#include "../core/Vector2d.hpp"


class SoftBall: public SoftBody{
private:
    float Rad;
    const int nRT = 10000;
    // PV = nRT
    void ApplyEqautionOfIdealGas();
    float CalculateArea() const;

public:
    SoftBall(const Vector2d& StartPos, const Vector2d& StartSpeed, float BodyRad, int BallCount, \
             int BallRad, float ballDensity, const sf::Color& clr);
    virtual ~SoftBall(){}

    void InnerForces() override;

    Vector2d getCenter() const override {return 0.5 * (Balls[0]->getPos() + Balls[Balls.size()/ 2]->getPos());}
    Vector2d getMaxPoint() override;
    Vector2d getMinPoint() override;

};


