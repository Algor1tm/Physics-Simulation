#include <iostream>

#include <SFML/Graphics.hpp>

#include "../../include/core/MainApp.hpp"
#include "../../include/objects/SoftRectangle.hpp"
#include "../../include/objects/SoftBall.hpp"
#include "../../include/core/Settings.hpp"
#include "../../include/core/Vector2d.hpp"


MainApp::MainApp()
    : physicEngine_(nullptr)
{

}


void MainApp::Start()
{
    chooseGame();

    std::cout << "\nPress SPACE to Pause/Unpause Simulation\n";
    std::cout << "While Pause, you can move objects with Left Mouse Button and change speed of BALLS with Right Mouse Button\n";

    gameLoop();
}


void MainApp::chooseGame()
{
    int game = 0;
    while (game != Games::OnlyBalls && game != Games::OnlySoftBodies && game != Games::Mix)
    {
        std::cout << "1 - Only Balls\n2 - Only Soft Bodies\n3 - Mix\n";
        std::cout << "Please Choose Game: ";
        std::cin >> game;
    }

    physicEngine_ = new Engine("Physic Simulation", sf::Color(25, 0, 150));

    if (game == Games::OnlyBalls)
        initGameOnlyBalls();
    else if (game == Games::OnlySoftBodies)
        initGameOnlySoftBodies();
    else if (game == Games::Mix)
        initGameMix();
}


void MainApp::gameLoop()
{
    sf::Clock clock;
    float FrameTime = 0;

    while (physicEngine_->isRunning())
    {
        clock.restart();

        physicEngine_->Update(FrameTime);
        physicEngine_->Render();
        physicEngine_->HandleEvents();

        FrameTime = clock.getElapsedTime().asSeconds();
    }
}


void MainApp::initGameMix()
{
    initBox();
    initWalls();

    physicEngine_->AddObject(new SoftRectangle({ 200, 100 }, { 0, 0 }, 8, 5, { 250, 0, 0 }));
    physicEngine_->AddObject(new SoftBall({ 50, 430 }, { 4, 0 }, 30, 12, { 250, 0, 0 }));

    physicEngine_->AddObject(new Ball({ WIDTH - 150, HEIGHT - 150 }, { -10, -10 }, 40, 0.1f, sf::Color(250, 200, 0)));
    physicEngine_->AddObject(new Ball({ WIDTH - 60, 50 }, { -5, 0 }, 30, 0.1f, sf::Color(250, 120, 0)));
    physicEngine_->AddObject(new Ball({ 60, 50 }, { 0, 0 }, 20, 0.1f, sf::Color(250, 50, 0)));
}


void MainApp::initGameOnlySoftBodies()
{
    initBox();
    initWalls();

    physicEngine_->AddObject(new SoftRectangle({ 200, 100 }, { 0, 0 }, 7, 5, { 250, 0, 0 }));
    physicEngine_->AddObject(new SoftRectangle({ WIDTH - 250, 100 }, { 0, 0 }, 7, 5, { 250, 0, 0 }));
    physicEngine_->AddObject(new SoftBall({ WIDTH / 2, 100 }, { 0, 0 }, 30, 12, { 250, 0, 0 }));
}


void MainApp::initGameOnlyBalls()
{
    initBox();

    Vector2d pos, speed;
    float radius;
    for (int i = 0; i < 13; i++)
    {
        pos = Vector2d::Random({ 0, WIDTH }, {0, HEIGHT});
        speed = Vector2d::Random({ -15, 15 }, {-15, 15});
        radius = (float)(std::rand() % 25) + 20;
        physicEngine_->AddObject(new Ball(pos, speed, radius, 0.1f, sf::Color(250, 175, 0)));
    }
}


void MainApp::initBox()
{
    physicEngine_->AddObject(new Line({ 0, 0 }, { WIDTH, 0 }, 1.f));
    physicEngine_->AddObject(new Line({ WIDTH, 0 }, { WIDTH, HEIGHT }, 1.f));
    physicEngine_->AddObject(new Line({ WIDTH, HEIGHT }, { 0, HEIGHT }, 1.f));
    physicEngine_->AddObject(new Line({ 0, HEIGHT }, { 0, 0 }, 1.f));
}


void MainApp::initWalls()
{
    physicEngine_->AddObject(new Polygon({ { 10, HEIGHT - 50 }, {WIDTH - 10, HEIGHT - 50},
                                            {WIDTH - 10, HEIGHT - 10}, {10, HEIGHT - 10} }, 2.f));
    physicEngine_->AddObject(new Polygon({ {100, 180}, { 120, 150 }, { 370, 300 }, { 350, 330 } }, 2.f));

    physicEngine_->AddObject(new Polygon({ {WIDTH - 400, 260 + 120}, {WIDTH - 150, 110 + 120},
                                           {WIDTH - 130, 140 + 120}, {WIDTH - 380, 290 + 120} }, 2.f));
    physicEngine_->AddObject(new Polygon({ {250, 400}, {390, HEIGHT - 50}, {160, HEIGHT - 50} }, 2.f));
}


MainApp::~MainApp()
{
    delete physicEngine_;
}
