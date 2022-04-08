#pragma once

#include "../core/Vector2d.hpp"
#include "Ball.hpp"


class SoftBody{
protected:
    struct Spring{
        const int Ks = 20000;
        const int Kd = 3000;

        Ball* ball1;
        Ball* ball2;

        Vector2d DefaultVector;
        float DefaultLength;

        Spring(Ball* p1, Ball* p2);
        virtual ~Spring() = default;

        void ApplyHookesForce();
        void ApplyDampingFactor();
        void ApplySelfCollision();

        void Draw(sf::RenderWindow* wnd);
    };

    std::vector<Spring*> Springs;
    std::vector<Ball*> Balls;

    unsigned NumOfBalls;

    Vector2d MaxPoint;
    Vector2d MinPoint;

public:
    virtual ~SoftBody();

    virtual void Draw(sf::RenderWindow* wnd);
	virtual void EnableSelectedEfect(int thickness);
	virtual void DisableSelectedEfect();

    virtual Ball* getBall(int i) const {return Balls[i];}
    virtual unsigned getNumOfBalls() const {return NumOfBalls;}

    virtual Vector2d getCenter() const = 0;
    virtual Vector2d getMaxPoint() = 0;
    virtual Vector2d getMinPoint() = 0;

    virtual void InnerForces() = 0;
};

