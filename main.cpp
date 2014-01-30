#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "QuadTree.hpp"
#include <iostream>
#include <time.h>
#include <sstream>

#define WIDTH 1900
#define HEIGHT 1000

#define MAX_SPEED 500
#define INIT 100

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

    sf::Clock frameClock;
    sf::Clock framerateClock;
    long framerate=0;
    double elapsedTime;
    bool toggleDisplay = true;

    std::vector<Entity> entities;

    sf::Font font;
    font.loadFromFile("times.ttf");
    sf::Text entityCounter;
    entityCounter.setFont(font);
    entityCounter.setCharacterSize(24);
    entityCounter.setPosition(10,10);
    entityCounter.setColor(sf::Color::Red);

    sf::Text fps;
    fps.setFont(font);
    fps.setCharacterSize(24);
    fps.setPosition(10,30);
    fps.setColor(sf::Color::Red);

    QuadTree qTree(sf::FloatRect(-1,-1, WIDTH+2, HEIGHT+2));

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
                    for(unsigned int i=0; i<INIT; i++)
                    {
                        /*
                        entities.push_back(Entity(sf::Mouse::getPosition(window).x,
                                              sf::Mouse::getPosition(window).y,
                                              0,
                                              0,
                                              sf::FloatRect(0, 0, WIDTH, HEIGHT)));
                                              */
                        entities.push_back(Entity(sf::Mouse::getPosition(window).x,
                                              sf::Mouse::getPosition(window).y,
                                              rand()%MAX_SPEED - MAX_SPEED/2,
                                              rand()%MAX_SPEED - MAX_SPEED/2,
                                              sf::FloatRect(0, 0, WIDTH, HEIGHT)));
                    }
                    convert.str("");
                    convert << "Entities : " << entities.size();
                    entityCounter.setString(convert.str());
                    break;
                case sf::Keyboard::D :
                    if(entities.size()>0)
                        for(unsigned int i=0; i<INIT; i++)
                        {
                            //qTree.remove(&(entities.back()));
                            entities.pop_back();
                        }
                    convert.str("");
                    convert << "Entities : " << entities.size();
                    entityCounter.setString(convert.str());
                    break;
                case sf::Keyboard::A :
                    toggleDisplay = toggleDisplay? false : true;
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
        elapsedTime = frameClock.getElapsedTime().asSeconds();
        frameClock.restart();
        qTree.clear();
        for(std::vector<Entity>::iterator it=entities.begin(); it != entities.end(); it++)
        {
            it->update(elapsedTime);
            qTree.insert(&(*it));
        }

        window.clear(sf::Color::White);

        if(toggleDisplay)
            qTree.display(window);
        for(std::vector<Entity>::iterator it=entities.begin(); it != entities.end(); it++)
        {
            it->display(window);
        }

        framerate++;
        if(framerateClock.getElapsedTime().asSeconds()>=1)
        {
            framerateClock.restart();
            convert.str("");
            convert << "FPS : " << framerate;
            fps.setString(convert.str());
            framerate = 0;
        }

        window.draw(entityCounter);
        window.draw(fps);
        window.display();
    }

    return 0;
}
