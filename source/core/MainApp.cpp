#include <iostream>

#include <SFML/Graphics.hpp>

#include "../../include/core/MainApp.hpp"
#include "../../include/objects/SoftRectangle.hpp"
#include "../../include/objects/SoftBall.hpp"


MainApp::MainApp(){
    Running = false;
    Init = true;

    PhysicEngine = new Engine("Some Physics", sf::Color(25, 0, 150));

    std::cout << "WARNING: DO NOT WATCH THE CODE!!!\n\n";
    std::cout << "Press SPACE to Pause/Unpause Simulation\n";
}

void MainApp::InitObjects(){
    Line* line = new Line({0, 0}, {WIDTH, 0}, 1);
    PhysicEngine->AddObject(line);
    line = new Line({WIDTH, 0}, {WIDTH, HEIGHT}, 1);
    PhysicEngine->AddObject(line);
    line = new Line({WIDTH, HEIGHT}, {0, HEIGHT}, 1);
    PhysicEngine->AddObject(line);
    line = new Line({0, HEIGHT}, {0, 0}, 1);
    PhysicEngine->AddObject(line);

    std::vector<Vector2d> points;
    points.push_back({10, HEIGHT - 50});
    points.push_back({WIDTH - 10, HEIGHT - 50});
    points.push_back({WIDTH - 10, HEIGHT - 10});
    points.push_back({10, HEIGHT - 10});
    PhysicEngine->AddObject(new Polygon(points, 3));

    points.clear();
    points.push_back({100, 180});
    points.push_back({120, 150});
    points.push_back({370, 300});
    points.push_back({350, 330});
    PhysicEngine->AddObject(new Polygon(points, 3));

    points.clear();
    points.push_back({WIDTH - 400, 260 + 120});
    points.push_back({WIDTH - 150, 110 + 120});
    points.push_back({WIDTH - 130, 140 + 120});
    points.push_back({WIDTH - 380, 290 + 120});
    PhysicEngine->AddObject(new Polygon(points, 3));

    points.clear();
    points.push_back({250, 400});
    points.push_back({390, HEIGHT - 50});
    points.push_back({160, HEIGHT - 50});
    PhysicEngine->AddObject(new Polygon(points, 3));

    SoftRectangle* srect = new SoftRectangle({200, 100}, {0, 0}, 8, 5, 17, 6, 1, {250, 0, 0});
    PhysicEngine->AddObject(srect);

    SoftBall* sball = new SoftBall({50, 430}, {4, 0}, 30, 12, 5, 1, {250, 0, 0});
    PhysicEngine->AddObject(sball);

    Ball* ball = new Ball({WIDTH  - 150, HEIGHT - 150}, {- 10, -10}, 40, 0.1, sf::Color(250, 200, 0));
    PhysicEngine->AddObject(ball);
    ball = new Ball({WIDTH - 60, 50}, {-5, 0}, 30, 0.1, sf::Color(250, 120, 0));
    PhysicEngine->AddObject(ball);
    ball = new Ball({60, 50}, {0, 0}, 20, 0.1,sf::Color(250, 50, 0));
    PhysicEngine->AddObject(ball);

}

void MainApp::Start(){
    Running = true;

    int result;
    sf::Clock clock;
    double FrameTime = 0;

    if(Init){
        while(Running){
            clock.restart();

            PhysicEngine->Update(FrameTime);

            PhysicEngine->Render();

            result = PhysicEngine->HandleEvents();

            if(result == 1)
                Running = false;

            FrameTime = clock.getElapsedTime().asSeconds();
        }
    }
}

MainApp::~MainApp(){
    delete PhysicEngine;
}
