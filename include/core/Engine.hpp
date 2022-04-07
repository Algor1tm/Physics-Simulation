#pragma once

#include <SFML/Graphics.hpp>

#include "../objects/Ball.hpp"
#include "../objects/Line.hpp"
#include "../objects/Polygon.hpp"
#include "../objects/SoftBody.hpp"
#include "Settings.hpp"
#include "Vector2d.hpp"


class Engine{
private:
    sf::RenderWindow* Window;
    sf::Color bgColor;

    float Speedfactor;
    float Accelfactor;
    // acceleration of gravity
    Vector2d g;
    float EnergyRemainAfterCollision;


    bool Pause;
    Ball* SelectedBall;
    SoftBody* SelectedSoftBody;
    // 1 - user pressing right mouse button and selecting object, else - 0
    bool RightMouseButton;
    // 1 - if user pressing left mouse button and selecting object, else - 0
    bool LeftMouseButton;


    std::vector<Ball*> Balls;
    std::vector<SoftBody*> SoftBodies;
    std::vector<Line*> Lines;
    std::vector<Polygon*> Polygons;
    // 0 --> p, q and r are collinear
    // 1 --> Clockwise
    // 2 --> Counterclockwise
    int orientation(const Vector2d& p, const Vector2d& q, const Vector2d& r);

    void ForceObject(Ball* object);
    void MoveObject(Ball* object, double dt);

    void MoveObject(Ball* ball, Vector2d dx);

    void ApplyCollisions(Ball* ball, bool softBody);

    // 1 - if collides, 0 - else
    bool CheckCollision(Ball* ball, Line* line);
    // softBody = 1 if ball belongs to softBody, else - 0
    void Collide(Ball* ball, Line* line, bool softBody);

    // return: -1 if not collides or
    //         Line* with which collides
    Line* CheckCollision(Ball* ball, Polygon* pol);

    bool CheckCollision(Ball* ball1, Ball* ball2);
    void Collide(Ball* ball1, Ball* ball2);

    Ball* CheckCollision(Ball* ball, SoftBody* body);

    void UpdateSoftBody(SoftBody* sb, double dt);
    void UpdateBall(Ball* sb, double dt);


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
