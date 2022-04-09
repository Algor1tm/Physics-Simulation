#pragma once

#include <SFML/Graphics.hpp>

#include "../core/Vector2d.hpp"
#include "Objects.hpp"
#include "Ball.hpp"


class SoftBody: public MovAble, public Selectable
{
public:
    SoftBody();
    virtual ~SoftBody();

    virtual void InnerForces() = 0;

    virtual void Move(float time) override;
    virtual void Move(const Vector2d& distance) override;

    virtual bool isInside(const Vector2d& mousePos) override;
    // user moving object
    void OnLeftMouseMove(const Vector2d& mousePos) override;
    // user change speed
    void OnRightMouseMove(const Vector2d& mousePos) override;
    void OnSelect(int thickness) override;
    void OnDeselect(int thickness) override;

    virtual void Draw(sf::RenderWindow* window);

    virtual bool isNear(Ball* ball);
    virtual Vector2d getCenter() const = 0;
    virtual Vector2d getMaxPoint() = 0;
    virtual Vector2d getMinPoint() = 0;

    Ball* getBall(int i) const { return Balls[i]; }
    size_t getNumOfBalls() const { return numOfBalls_; }

private:
    const int selectThickness_ = 1;
    void drawSpeed(sf::RenderWindow* window);

protected:
    class Spring;

    std::vector<Spring*> Springs;
    std::vector<Ball*> Balls;
    size_t numOfBalls_;

    class Spring
    {
    private:
        static const int Ks = 20000;
        static const int Kd = 3000;

        Ball* ball1_;
        Ball* ball2_;

        Vector2d defaultVector_;
        float defaultLength_;
        // radius1 + radius2
        float cache_;
    public:
        Spring(Ball* ball1, Ball* ball2);
        virtual ~Spring() = default;

        void ApplyHookesForce();
        void ApplyDampingFactor();
        void ApplySelfCollision();

        void Draw(sf::RenderWindow* window);
    };
};

