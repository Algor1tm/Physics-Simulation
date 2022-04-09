#include "../../include/objects/SoftBall.hpp"



SoftBall::SoftBall(const Vector2d& StartPos, const Vector2d& StartSpeed, float BodyRad, int BallCount, const sf::Color& color)
    : SoftBody(), radius_(BodyRad)
{
    float tempx, tempy;

    for(float angle = 0; angle < 360; angle += 360 / BallCount)
    {
        tempx = radius_ * cosf(angle * (float)M_PI / 180);
        tempy = radius_ * sinf(angle * (float)M_PI / 180);

        Balls.push_back(new Ball(StartPos + Vector2d(tempx, tempy), StartSpeed, ballRad, ballDensity, color));
    }

    for(unsigned i =0; i < Balls.size(); i++)
    {
        if(i == Balls.size() - 1)
            Springs.push_back(new Spring(Balls[i], Balls[0]));
        else
            Springs.push_back(new Spring(Balls[i], Balls[i + 1]));
    }

    numOfBalls_ = Balls.size();
}


void SoftBall::applyEqautionOfIdealGas()
{
    size_t temp = numOfBalls_ / 2;
    Vector2d center;
    for(size_t i = 0; i < temp; i++)
        center += 0.5 * (Balls[i]->getPos() + Balls[i + temp]->getPos());
    center = Vector2d(center.x / temp, center.y / temp);

    Vector2d normal, F, pos;
    float area = computeArea() / areaScale;

    for(size_t i = 0; i < numOfBalls_; i++)
    {
        pos = Balls[i]->getPos();
        normal = (pos - center).normalize();
        F = nRT / area * normal;
        Balls[i]->AddForce(F);
    }
}


void SoftBall::InnerForces()
{
    applyEqautionOfIdealGas();

    for(auto& spring: Springs)
    {
        spring->ApplyHookesForce();
        spring->ApplyDampingFactor();
        spring->ApplySelfCollision();
    }
}


float SoftBall::computeArea() const
{
    float sum = 0;
    Vector2d pos1;
    Vector2d pos2;

    int j = Balls.size() - 1;
    for(unsigned i = 0; i < Balls.size(); i++){
        pos1 = Balls[j]->getPos();
        pos2 = Balls[i]->getPos();

        sum += (pos1.x + pos2.x) * (pos1.y - pos2.y);
        j = i;
    }
    return 0.5f * fabs(sum);
}


Vector2d SoftBall::getMaxPoint()
{
    Vector2d maxPoint;
    maxPoint = Balls[0]->getPos();
    for(unsigned i = 1; i < Balls.size(); i++){
        if(maxPoint.x < Balls[i]->getPos().x)
            maxPoint.x = Balls[i]->getPos().x;
        if(maxPoint.y < Balls[i]->getPos().y)
            maxPoint.y = Balls[i]->getPos().y;
    }
    return maxPoint;
}


Vector2d SoftBall::getMinPoint()
{
    Vector2d minPoint;
    minPoint = Balls[0]->getPos();
    for(unsigned i = 1; i < Balls.size(); i++){
        if(minPoint.x > Balls[i]->getPos().x)
            minPoint.x = Balls[i]->getPos().x;
        if(minPoint.y > Balls[i]->getPos().y)
            minPoint.y = Balls[i]->getPos().y;
    }
    return minPoint;
}
