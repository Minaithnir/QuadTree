#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "QuadTree.hpp"
#include <iostream>
#include <time.h>
#include <sstream>

#define WIDTH 1900
#define HEIGHT 1000

#define MAX_SPEED 500

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

    sf::Clock frameClock;
    sf::Clock framerateClock;
    long framerate=0;
    long lastFramerate=0;

    std::vector<Entity> entities;

    sf::Font font;
    font.loadFromFile("times.ttf");
    sf::Text entityCounter;
    entityCounter.setFont(font);
    entityCounter.setCharacterSize(24);
    entityCounter.setPosition(10,10);
    entityCounter.setColor(sf::Color::Red);

    QuadTree qTree(sf::FloatRect(0,0, WIDTH, HEIGHT));

    std::ostringstream convert;

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
                    break;
                default :
                    break;
                }
                break;
            case sf::Event::KeyPressed :
                switch(event.key.code)
                {
                case sf::Keyboard::Space :
                    for(unsigned int i=0; i<1; i++)
                        entities.push_back(Entity(sf::Mouse::getPosition(window).x,
                                              sf::Mouse::getPosition(window).y,
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
        qTree.clear();
        for(std::vector<Entity>::iterator it=entities.begin(); it != entities.end(); it++)
        {
            it->update(elapsedTime);
            qTree.insert(&(*it));
        }

        window.clear(sf::Color::White);

        qTree.display(window);
        for(std::vector<Entity>::iterator it=entities.begin(); it != entities.end(); it++)
        {
            it->display(window);
        }

        framerate++;
        if(framerateClock.getElapsedTime().asSeconds()>=1)
        {
            framerateClock.restart();
            lastFramerate = framerate;
            framerate = 0;
        }

        convert.str("");
        convert << "Entities : " << entities.size() << " FPS : " << lastFramerate;

        entityCounter.setString(convert.str());
        window.draw(entityCounter);
        window.display();
    }

    return 0;
}
