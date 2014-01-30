#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

/**
Class describing a basic mobile that move over time
**/
class Entity
{
    public:
        Entity();
        Entity(double posX, double posY, double speedX, double speedY, sf::FloatRect rect);
        virtual ~Entity();

        sf::Drawable& getSprite();
        void setPosition(double x, double y);
        sf::Vector2f getPosition();

        void setSpeed(double x, double y);

        void setBoundary(sf::FloatRect rect);

        void update(double frametime);

        void display(sf::RenderTarget& screen);

        void pos();
    protected:
        sf::CircleShape m_shape;
        sf::Vector2f m_pos;
        sf::Vector2f m_speed;

        sf::FloatRect m_boundaries;
};

#endif // ENTITY_H
