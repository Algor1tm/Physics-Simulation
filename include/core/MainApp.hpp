#pragma once

#include "Engine.hpp"


class MainApp{
public:
    MainApp();
    ~MainApp();

    void InitObjects();
    void Start();

private:
    void gameLoop();

    Engine* physicEngine_;
};

