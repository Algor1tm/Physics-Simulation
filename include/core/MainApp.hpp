#ifndef MAINAPP_HPP_INCLUDED
#define MAINAPP_HPP_INCLUDED

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



#endif // MAINAPP_HPP_INCLUDED
