#pragma once

#include <SFML/Graphics.hpp>

#include "../core/Vector2d.hpp"
#include "Objects.hpp"
#include "Ball.hpp"


class SoftBody: public MovAble, public Selectable
{
private:
    const int selectThickness_ = 1;

protected:
    struct Spring
    {
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

public:
    SoftBody() = default;
    virtual ~SoftBody();

    virtual void InnerForces() = 0;

    virtual void Move(double time) override;
    virtual void Move(const Vector2d& distance) override;

    virtual bool isInside(const Vector2d& mousePos) override;
    void OnLeftMouseMove(const Vector2d& mousePos) override;
    void OnRightMouseMove(const Vector2d& mousePos) override {};
    void OnSelect(int thickness) override;
    void OnDeselect(int thickness) override;

    virtual void Draw(sf::RenderWindow* window);

    virtual Vector2d getCenter() const = 0;
    virtual Vector2d getMaxPoint() = 0;
    virtual Vector2d getMinPoint() = 0;

    Ball* getBall(int i) const { return Balls[i]; }
    unsigned getNumOfBalls() const { return NumOfBalls; }
};

