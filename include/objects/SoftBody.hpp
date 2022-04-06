#ifndef SOFTBODY_HPP_INCLUDED
#define SOFTBODY_HPP_INCLUDED

#include "PhysicalObjects.hpp"
#include "../core/Vector2d.hpp"
#include "Ball.hpp"


class SoftBody: public MovAble, public DrawAble{
protected:
    struct Spring: public DrawAble{
        const int Ks = 25000;
        const int Kd = 3000;

        Ball* ball1;
        Ball* ball2;

        Vector2d DefaultVector;
        float DefaultLength;

        Spring(Ball* p1, Ball* p2);
        virtual ~Spring(){}
        void ApplyHookesForce();
        void ApplyDampingFactor();
        void ApplySelfCollision();

        void Draw(sf::RenderWindow* wnd) override;
    };

    std::vector<Spring*> Springs;
    std::vector<Ball*> Balls;

    unsigned NumOfBalls;

    Vector2d MaxPoint;
    Vector2d MinPoint;

public:
    virtual ~SoftBody();

    virtual void Draw(sf::RenderWindow* wnd) override;
    virtual void EnableSelectedEfect(int thickness);
    virtual void DisableSelectedEfect();

    virtual Ball* getBall(unsigned i) {return Balls[i];}
    virtual unsigned getNumOfBalls() const {return NumOfBalls;}

    virtual Vector2d getCenter() const = 0;
    virtual Vector2d getMaxPoint() = 0;
    virtual Vector2d getMinPoint() = 0;

    virtual void InnerForces() = 0;
};


#endif // SOFTBODY_HPP_INCLUDED
