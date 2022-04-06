#include <iostream>
#include "include/core/MainApp.hpp"


int main()
{
    MainApp* App = new MainApp();

    App->InitObjects();
    App->Start();

   delete App;

    return 0;
}
