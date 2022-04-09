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
public:
    Engine(const std::string& title, const sf::Color& color);
    ~Engine();

    void AddObject(Ball* object) { balls_.push_back(object), selector_.AddObject(object); }
    void AddObject(SoftBody* object) { softBodies_.push_back(object), selector_.AddObject(object);}
    void AddObject(Line* object){lines_.push_back(object);}
    void AddObject(Polygon* object){polygons_.push_back(object);}

    void Update(double dt);
    void Render();

    void HandleEvents();
    bool isRunning() { return running_; }

private:
    sf::RenderWindow* window_;
    bool running_;
    sf::Color backgroundColor_;

    SelectManager selector_;

    // acceleration of gravity
    Vector2d g;

    std::vector<Ball*> balls_;
    std::vector<SoftBody*> softBodies_;
    std::vector<Line*> lines_;
    std::vector<Polygon*> polygons_;

    void applyGravity(RigidBody* object);

    void applyCollisions(Ball* ball);
    void applyCollisions(SoftBody* soft);

    void updateBall(Ball* ball, double elapsedTime);
    void updateSoftBody(SoftBody* soft, double elapsedTime);

    bool pause_;
    void onKeyPressed(const sf::Keyboard::Key& mousePos);
};
