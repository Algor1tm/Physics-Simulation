#pragma once

#include "Engine.hpp"


class MainApp{
private:
    bool Running;
    bool Init;

    Engine* PhysicEngine;

public:
    MainApp();
    ~MainApp();

    void InitObjects();

    void Start();
};

