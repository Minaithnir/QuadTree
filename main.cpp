#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include <iostream>
#include <time.h>

#define WIDTH 800
#define HEIGHT 600

#define MAX_SPEED 500

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

    sf::Clock frameClock;

    std::vector<Entity> entities;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
            case sf::Event::Closed :
                window.close();
                break;
            case sf::Event::MouseButtonPressed :
                switch(event.mouseButton.button)
                {
                case sf::Mouse::Left :
                    entities.push_back(Entity(event.mouseButton.x,
                                              event.mouseButton.y,
                                              rand()%MAX_SPEED - MAX_SPEED/2,
                                              rand()%MAX_SPEED - MAX_SPEED/2,
                                              sf::FloatRect(0, 0, WIDTH, HEIGHT)));
                    break;
                default :
                    break;
                }
                break;
            default :
                break;
            }
        }

        // Entities update
        double elapsedTime = frameClock.getElapsedTime().asSeconds();
        frameClock.restart();
        for(std::vector<Entity>::iterator it=entities.begin(); it != entities.end(); it++)
        {
            it->update(elapsedTime);
        }

        window.clear(sf::Color::White);
        for(std::vector<Entity>::iterator it=entities.begin(); it != entities.end(); it++)
        {
            it->display(window);
        }

        window.display();
    }

    return 0;
}
