#pragma once

#include <SFML/Graphics.hpp>

#include "../objects/Ball.hpp"
#include "../objects/Line.hpp"
#include "../objects/Polygon.hpp"
#include "../objects/SoftBody.hpp"
#include "../objects/RigidBody.hpp"

#include "SelectManager.hpp"
#include "Collision.hpp"
#include "Settings.hpp"
#include "Vector2d.hpp"


class Engine{
private:
    sf::RenderWindow* Window;
    sf::Color backgroundColor;

    SelectManager selector_;

    // acceleration of gravity
    Vector2d g;

    std::vector<Ball*> Balls;
    std::vector<SoftBody*> SoftBodies;
    std::vector<Line*> Lines;
    std::vector<Polygon*> Polygons;

    void ApplyGravity(RigidBody* object);

    void ApplyCollisions(Ball* ball);
    void ApplyCollisions(SoftBody* soft);

    void UpdateBall(Ball* ball, double dt);
    void UpdateSoftBody(SoftBody* soft, double dt);

    bool Pause;
    void OnKeyPressed(const sf::Keyboard::Key& mpos);

public:
    Engine(const char* title, const sf::Color& clr);
    ~Engine();

    void AddObject(Ball* object) { Balls.push_back(object), selector_.AddObject(object); }
    void AddObject(SoftBody* object) { SoftBodies.push_back(object), selector_.AddObject(object);}
    void AddObject(Line* object){Lines.push_back(object);}
    void AddObject(Polygon* object){Polygons.push_back(object);}


    void Update(double dt);
    void Render();

    // return 1 if Window were closed, else 0
    int HandleEvents();
};
