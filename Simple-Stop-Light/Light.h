#ifndef LIGHT_H
#define LIGHT_H

#include "Includes.h"

enum class LightState{RED=0, YELLOW, GREEN};

class Light
{
private:
    LightState state;

    sf::RenderWindow* window;

    sf::RectangleShape frame;
    sf::CircleShape circRed, circYellow, circGreen;
    sf::CircleShape circRedShade, circYellowShade, circGreenShade;
    sf::CircleShape circRedBack, circYellowBack, circGreenBack;

    sf::Time timerRed, timerRedMax;
    sf::Time timerYellow, timerYellowMax;
    sf::Time timerGreen, timerGreenMax;

public:
    Light(sf::RenderWindow* window);
    virtual ~Light();

    void updateTimer(const float& dt);
    void updateState();
    void update(const float& dt);

    void renderLights(sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
};

#endif
