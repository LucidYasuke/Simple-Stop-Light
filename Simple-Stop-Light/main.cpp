#include "Engine.h"

int main()
{
    //Init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    //Init Game Engine
    Engine engine;

    engine.core();

    return 0;
}