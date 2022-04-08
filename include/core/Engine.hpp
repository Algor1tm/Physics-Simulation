#pragma once

#include <SFML/Graphics.hpp>

#include "../objects/Ball.hpp"
#include "../objects/Line.hpp"
#include "../objects/Polygon.hpp"
#include "../objects/SoftBody.hpp"
#include "../objects/RigidBody.hpp"
#include "Collision.hpp"
#include "Settings.hpp"
#include "Vector2d.hpp"


class Engine{
private:
    sf::RenderWindow* Window;
    sf::Color bgColor;

    // acceleration of gravity
    Vector2d g;

    std::vector<Ball*> Balls;
    std::vector<SoftBody*> SoftBodies;
    std::vector<Line*> Lines;
    std::vector<Polygon*> Polygons;

    void ApplyGravity(RigidBody* object);

    void ApplyCollisions(Ball* ball);
    void ApplyCollisions(SoftBody* soft);

    void UpdateSoftBody(SoftBody* sb, double dt);
    void UpdateBall(Ball* sb, double dt);


    bool Pause;
    Ball* SelectedBall;
    SoftBody* SelectedSoftBody;
    // 1 - user pressing right mouse button and selecting object, else - 0
    bool RightMouseButton;
    // 1 - if user pressing left mouse button and selecting object, else - 0

    bool LeftMouseButton;
    //return: first value - if 0 - ball selected, if 1 - softbody selected
    //        second value - index of object
    //        returns {-1, -1} if no object were selected
    Vector2d SelectObject(const Vector2d& mpos);
    void OnMousePressed(const sf::Event& event);
    void OnMouseMove(const sf::Event& event);
    void OnKeyPressed(const sf::Event& event);

public:
    Engine(const char* title, const sf::Color& clr);
    ~Engine();

    void AddObject(Ball* object){Balls.push_back(object);}
    void AddObject(Line* object){Lines.push_back(object);}
    void AddObject(Polygon* object){Polygons.push_back(object);}
    void AddObject(SoftBody* object){SoftBodies.push_back(object);}

    void Update(double dt);
    void Render();

    // return 1 if Window were closed, else 0
    int HandleEvents();
};
