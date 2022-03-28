#include "Light.h"

Light::Light(sf::RenderWindow* window)
{
    this->window = window;
    this->state = LightState::RED;
    
    this->frame.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
    this->frame.setPosition(static_cast<float>(this->window->getSize().x) / 2.f - this->frame.getSize().x / 2.f, static_cast<float>(this->window->getSize().y) / 2.f - this->frame.getSize().y / 2.f);
    this->frame.setFillColor(sf::Color(240, 118, 16));

    //===Init Active Lights===//
    this->circRed.setRadius(this->frame.getGlobalBounds().width / 3.5f);
    this->circRed.setPosition(this->frame.getGlobalBounds().width / 2.f - this->circRed.getRadius() + this->frame.getGlobalBounds().left, this->frame.getGlobalBounds().height * (1.f / 3.f) / 2.f - this->circRed.getRadius() + this->frame.getGlobalBounds().top);
    this->circRed.setFillColor(sf::Color(216, 67, 46));

    this->circYellow.setRadius(this->frame.getGlobalBounds().width / 3.5f);
    this->circYellow.setPosition(this->frame.getGlobalBounds().width / 2.f - this->circYellow.getRadius() + this->frame.getGlobalBounds().left, this->frame.getGlobalBounds().height * (3.f / 3.f) / 2.f - this->circYellow.getRadius() + this->frame.getGlobalBounds().top);
    this->circYellow.setFillColor(sf::Color(255, 179, 0));

    this->circGreen.setRadius(this->frame.getGlobalBounds().width / 3.5f);
    this->circGreen.setPosition(this->frame.getGlobalBounds().width / 2.f - this->circGreen.getRadius() + this->frame.getGlobalBounds().left, this->frame.getGlobalBounds().height * (5.f / 3.f) / 2.f - this->circGreen.getRadius() + this->frame.getGlobalBounds().top);
    this->circGreen.setFillColor(sf::Color(0, 151, 85));
    //---Init Active Lights---//

    //===Init Unactive Lights===//
    this->circRedShade = this->circRed;
    this->circRedShade.setFillColor(sf::Color(216, 67, 46, 90));
    
    this->circYellowShade = this->circYellow;
    this->circYellowShade.setFillColor(sf::Color(255, 179, 0, 90));
    
    this->circGreenShade = this->circGreen;
    this->circGreenShade.setFillColor(sf::Color(0, 151, 85, 90));
    //---Init Unactive Lights---// 

    //===Init Back Lights===//
    this->circRedBack = this->circRed;
    this->circRedBack.setFillColor(sf::Color::Black);

    this->circYellowBack = this->circYellow;
    this->circYellowBack.setFillColor(sf::Color::Black);

    this->circGreenBack = this->circGreen;
    this->circGreenBack.setFillColor(sf::Color::Black);
    //---Init Back Lights---//

    //===Init Timers===//
    this->timerRedMax = sf::seconds(2.5f);
    this->timerYellowMax = sf::seconds(1.2f);
    this->timerGreenMax = sf::seconds(2.0f);
    //---Init Timers---//
}

Light::~Light()
{

}

void Light::updateTimer(const float& dt)
{
    switch (this->state)
    {
    case LightState::RED:
        this->timerRed += sf::seconds(dt);
        break;    
    case LightState::YELLOW:
        this->timerYellow += sf::seconds(dt);
        break;    
    case LightState::GREEN:
        this->timerGreen += sf::seconds(dt);
        break;
    }
}

void Light::updateState()
{
    switch (this->state)
    {
    case LightState::RED:
        if (this->timerRed >= this->timerRedMax)
        {
            this->state = LightState::GREEN;
            this->timerRed = sf::seconds(0.f);
        }
        break;
    case LightState::YELLOW:
        if (this->timerYellow >= this->timerYellowMax)
        {
            this->state = LightState::RED;
            this->timerYellow = sf::seconds(0.f);
        }
        break;
    case LightState::GREEN:
        if (this->timerGreen >= this->timerGreenMax)
        {
            this->state = LightState::YELLOW;
            this->timerGreen = sf::seconds(0.f);
        }
        break;
    default:
        break;
    }
}

void Light::update(const float& dt)
{
    this->updateTimer(dt);
    this->updateState();
}

void Light::renderLights(sf::RenderTarget* target)
{
    target->draw(this->circRedBack);
    target->draw(this->circYellowBack);
    target->draw(this->circGreenBack);
    
    target->draw(this->circRedShade);
    target->draw(this->circYellowShade);
    target->draw(this->circGreenShade);

    switch (this->state)
    {
    case LightState::RED:
        target->draw(this->circRed);
        break;
    case LightState::YELLOW:
        target->draw(this->circYellow);
        break;
    case LightState::GREEN:
        target->draw(this->circGreen);
        break;
    default:
        break;
    }
}

void Light::render(sf::RenderTarget* target)
{
    target->draw(this->frame);
    this->renderLights(target);
}