#include "../../include/objects/SoftRectangle.hpp"


SoftRectangle::SoftRectangle(const Vector2d& StartPos, const Vector2d& StartSpeed, int w, int h, int interval, \
                             int Rad, float ballDensity, const sf::Color& clr)
{
    width = w;
    height = h;
    Vector2d pos = StartPos;

    float startx = StartPos.x;
    for (int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            Balls.push_back(new Ball(pos, StartSpeed, Rad, ballDensity, clr));
            pos.x += interval;
        }
        pos.y += interval;
        pos.x = startx;
    }

    for (int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            if(j < w - 1)
                Springs.push_back(new Spring(Balls[j + i * w], Balls[j + 1 + i * w]));
            if(i < h - 1)
                Springs.push_back(new Spring(Balls[j + i * w], Balls[j + (i + 1)* w]));
            if((j < w - 1) && (i < h - 1))
                Springs.push_back(new Spring(Balls[j + i * w], Balls[j + 1 + (i + 1)* w]));
            if((j > 0) && (i < h - 1))
                Springs.push_back(new Spring(Balls[j + i * w], Balls[j - 1 + (i + 1)* w]));

        }
    }

    NumOfBalls = Balls.size();

}

Vector2d SoftRectangle::getMaxPoint(){
    //candidates:
    Vector2d c1 = Balls[0]->getPos();
    Vector2d c2 = Balls[width - 1]->getPos();
    Vector2d c3 = Balls[width * (height - 1)]->getPos();
    Vector2d c4 = Balls[Balls.size() - 1]->getPos();

    MaxPoint.x = std::max(std::max(std::max(c1.x, c2.x), c3.x), c4.x);
    MaxPoint.y = std::max(std::max(std::max(c1.y, c2.y), c3.y), c4.y);

    return MaxPoint;
}

Vector2d SoftRectangle::getMinPoint(){
    Vector2d c1 = Balls[0]->getPos();
    Vector2d c2 = Balls[width - 1]->getPos();
    Vector2d c3 = Balls[width * (height - 1)]->getPos();
    Vector2d c4 = Balls[Balls.size() - 1]->getPos();

    MinPoint.x = std::min(std::min(std::min(c1.x, c2.x), c3.x), c4.x);
    MinPoint.y = std::min(std::min(std::min(c1.y, c2.y), c3.y), c4.y);
    return MinPoint;
}

void SoftRectangle::InnerForces(){
    for(auto& spring: Springs){
        spring->ApplyHookesForce();
        spring->ApplyDampingFactor();
        spring->ApplySelfCollision();
    }
}
