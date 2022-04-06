#ifndef SOFTBALL_HPP_INCLUDED
#define SOFTBALL_HPP_INCLUDED

#include "SoftBody.hpp"
#include "../core/Vector2d.hpp"


class SoftBall: public SoftBody{
private:
    float Rad;
    const int nRT = 10000;
    // PV = nRT
    void ApplyEqautionOfIdealGas();

public:
    SoftBall(Vector2d StartPos, Vector2d StartSpeed, float BodyRad, int BallCount, \
             int BallRad, float ballDensity, const sf::Color& clr);
    virtual ~SoftBall(){}

    void InnerForces() override;

    float CalculateArea() const;

    Vector2d getCenter() const override {return 0.5 * (Balls[0]->getPos() + Balls[Balls.size()/ 2]->getPos());}
    Vector2d getMaxPoint() override;
    Vector2d getMinPoint() override;

};


#endif // SOFTBALL_HPP_INCLUDED
