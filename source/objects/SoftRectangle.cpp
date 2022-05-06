#include "../../include/objects/SoftRectangle.hpp"


SoftRectangle::SoftRectangle(const Vector2d& StartPos, const Vector2d& StartSpeed,  \
                             int width, int height, const sf::Color& color)
    : SoftBody(), width_(width), height_(height)
{
    Vector2d pos = StartPos;

    float startx = StartPos.x;
    for (int i = 0; i < height_; i++)
    {
        for(int j = 0; j < width_; j++)
        {
            Balls.push_back(new Ball(pos, StartSpeed, ballRad, ballDensity, color));
            pos.x += interval;
        }
        pos.y += interval;
        pos.x = startx;
    }

    for (int i = 0; i < height_; i++)
    {
        for(int j = 0; j < width_; j++)
        {
            if(j < width_ - 1)
                Springs.push_back(new Spring(Balls[j + i * width_], Balls[j + 1 + i * width_]));
            if(i < height_ - 1)
                Springs.push_back(new Spring(Balls[j + i * width_], Balls[j + (i + 1) * width_]));
            if((j < width_ - 1) && (i < height_ - 1))
                Springs.push_back(new Spring(Balls[j + i * width_], Balls[j + 1 + (i + 1) * width_]));
            if((j > 0) && (i < height_ - 1))
                Springs.push_back(new Spring(Balls[j + i * width_], Balls[j - 1 + (i + 1) * width_]));

        }
    }

    numOfBalls_ = Balls.size();
}


Vector2d SoftRectangle::getCenter() const
{ 
    return 0.5 * (Balls[0]->getPos() + Balls[numOfBalls_ - 1]->getPos());
}

Vector2d SoftRectangle::getMaxPoint()
{
    Vector2d maxPoint;
    //candidates:
    Vector2d c1 = Balls[0]->getPos();
    Vector2d c2 = Balls[width_ - 1]->getPos();
    Vector2d c3 = Balls[width_ * (height_ - 1)]->getPos();
    Vector2d c4 = Balls[Balls.size() - 1]->getPos();

    maxPoint.x = std::max(std::max(std::max(c1.x, c2.x), c3.x), c4.x);
    maxPoint.y = std::max(std::max(std::max(c1.y, c2.y), c3.y), c4.y);

    return maxPoint;
}


Vector2d SoftRectangle::getMinPoint()
{
    Vector2d minPoint;
    //candidates:
    Vector2d c1 = Balls[0]->getPos();
    Vector2d c2 = Balls[width_ - 1]->getPos();
    Vector2d c3 = Balls[width_ * (height_ - 1)]->getPos();
    Vector2d c4 = Balls[Balls.size() - 1]->getPos();

    minPoint.x = std::min(std::min(std::min(c1.x, c2.x), c3.x), c4.x);
    minPoint.y = std::min(std::min(std::min(c1.y, c2.y), c3.y), c4.y);
    return minPoint;
}


void SoftRectangle::InnerForces()
{
    for(auto& spring: Springs)
    {
        spring->ApplyHookesForce();
        spring->ApplyDampingFactor();
        spring->ApplySelfCollision();
    }
}
