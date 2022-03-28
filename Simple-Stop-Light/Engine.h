#ifndef ENGINE_H
#define ENGINE_H

#include "Light.h"

class Engine
{
private:
    float dt;
    sf::Clock dtClock;

    sf::Event event;
    sf::RenderWindow* window;

    Light* light;

    void initWindow();
public:
    Engine();
    virtual ~Engine();

    void updateDeltaTime();
    void updateTimers();
    void updateEvents();
    void updateLight();
    void update();

    void render();

    void core();
};

#endif