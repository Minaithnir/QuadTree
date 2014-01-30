#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "QuadTree.hpp"
#include <iostream>
#include <time.h>
#include <sstream>

#define WIDTH 1900
#define HEIGHT 1000

#define MAX_SPEED 500
#define BATCH_SIZE 100

#define RANGE 5

void Collisions(std::vector<Entity>& entities, QuadTree& qTree, bool& useQTree);

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

    sf::Clock frameClock;
    sf::Clock framerateClock;
    long framerate=0;
    double elapsedTime;
    bool toggleDisplay = true;
    bool toggleQTree = true;

    std::vector<Entity> entities;
    std::list<Entity*> inRange;

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
                case sf::Keyboard::A :
                    // batch insertion
                    for(unsigned int i=0; i<BATCH_SIZE; i++)
                    {
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
                    // batch delete
                    if(entities.size()>0)
                        for(unsigned int i=0; i<BATCH_SIZE; i++)
                        {
                            //qTree.remove(&(entities.back()));
                            entities.pop_back();
                        }
                    convert.str("");
                    convert << "Entities : " << entities.size();
                    entityCounter.setString(convert.str());
                    break;
                case sf::Keyboard::G :
                    toggleDisplay = toggleDisplay? false : true;
                    break;
                case sf::Keyboard::T :
                    toggleQTree = toggleQTree? false : true;
                    if(!toggleQTree)
                        qTree.clear();
                    break;
                default :
                    break;
                }
                break;
            default :
                break;
            }
        }

        /// updates
        elapsedTime = frameClock.getElapsedTime().asSeconds();
        frameClock.restart();
        if(toggleQTree)
            qTree.clear();
        // entity update and qtree insertion
        for(std::vector<Entity>::iterator it=entities.begin(); it != entities.end(); it++)
        {
            it->update(elapsedTime);
            if(toggleQTree)
                qTree.insert(&(*it));
        }

        // framerate update
        framerate++;
        if(framerateClock.getElapsedTime().asSeconds()>=1)
        {
            framerateClock.restart();
            convert.str("");
            convert << "FPS : " << framerate;
            fps.setString(convert.str());
            framerate = 0;
        }

        // inrange update
        for(std::vector<Entity>::iterator it=entities.begin(); it!=entities.end(); it++)
        {
            it->setColor(sf::Color::Black);
        }

        Collisions(entities, qTree, toggleQTree);
/*
        float mouseX = sf::Mouse::getPosition(window).x;
        float mouseY = sf::Mouse::getPosition(window).y;

        if(toggleQTree)
        {
            inRange = qTree.range(mouseX, mouseY, RANGE);
            for(std::list<Entity*>::iterator it=inRange.begin(); it!=inRange.end(); it++)
            {
                if((*it)->distance(mouseX, mouseY) < RANGE)
                {
                    (*it)->setColor(sf::Color::Red);
                }
                else
                    (*it)->setColor(sf::Color::Blue);
            }
        }
*/

        /// display
        window.clear(sf::Color::White);

        if(toggleDisplay)
            qTree.display(window);
        for(std::vector<Entity>::iterator it=entities.begin(); it != entities.end(); it++)
        {
            it->display(window);
        }

        window.draw(entityCounter);
        window.draw(fps);
        window.display();
    }

    return 0;
}

void Collisions(std::vector<Entity>& entities, QuadTree& qTree, bool& useQTree)
{
    std::list<Entity*> inRange;

    for(std::vector<Entity>::iterator eIt=entities.begin(); eIt!=entities.end(); eIt++)
    {
        float eX = eIt->getPosition().x;
        float eY = eIt->getPosition().y;

        if(useQTree)
        {
            inRange = qTree.range(eX, eY, RANGE);
            for(std::list<Entity*>::iterator it=inRange.begin(); it!=inRange.end(); it++)
            {
                if((*it)->distance(eX, eY) < RANGE && (*it) != (&(*eIt)))
                    (*it)->setColor(sf::Color::Red);
            }
        }
        else
        {
            for(std::vector<Entity>::iterator it=entities.begin(); it!=entities.end(); it++)
            {
                if(it->distance(eX, eY) < RANGE && (&(*it)) != (&(*eIt)))
                    it->setColor(sf::Color::Red);
            }
        }
    }
}
