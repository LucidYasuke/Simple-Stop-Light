#include "Engine.h"

void Engine::initWindow()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8.0;

    this->window = new sf::RenderWindow(sf::VideoMode(320, 640), "Simple-Stop-Light", sf::Style::Titlebar | sf::Style::Close, settings);
    this->window->setFramerateLimit(120);
    this->window->setVerticalSyncEnabled(false);
}

Engine::Engine()
{
    this->initWindow();
    this->light = new Light(this->window);
}

Engine::~Engine()
{
    delete this->window;
}

void Engine::updateDeltaTime()
{
    this->dt = this->dtClock.restart().asSeconds();
}

void Engine::updateTimers()
{

}

void Engine::updateEvents()
{
    while (window->pollEvent(this->event))
    {
       if (event.type == sf::Event::Closed)
       {
           window->close();
       }
    } 
}

void Engine::updateLight()
{   
    light->update(dt);
}

void Engine::update()
{
    this->updateTimers();
    this->updateEvents();
    this->updateLight();
}

void Engine::render()
{
    this->window->clear();

    this->light->render(this->window);

    this->window->display();
}

void Engine::core()
{
    while (this->window->isOpen())
    {
        this->updateDeltaTime();
        this->update();
        this->render();
    }   
}