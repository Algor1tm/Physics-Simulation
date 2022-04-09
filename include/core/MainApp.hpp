#pragma once

#include "Engine.hpp"


class MainApp{
public:
    MainApp();
    ~MainApp();

    void Start();

private:
    void gameLoop();
    void chooseGame();

    void initGameOnlyBalls();
    void initGameOnlySoftBodies();
    void initGameMix();

    void initBox();
    void initWalls();

    enum Games { OnlyBalls = 1, OnlySoftBodies = 2, Mix = 3 };
    Engine* physicEngine_;
};

