#include "Entity.hpp"
#include <iostream>

Entity::Entity()
{
    m_shape = sf::CircleShape(10,3);
    m_shape.setOrigin(5,5);
    m_shape.setFillColor(sf::Color::Black);
}

Entity::Entity(double posX, double posY, double speedX, double speedY, sf::FloatRect rect)
{
    m_shape = sf::CircleShape(4,3);
    m_shape.setOrigin(2,2);
    m_shape.setFillColor(sf::Color::Black);

    setPosition(posX, posY);
    setSpeed(speedX, speedY);
    setBoundary(rect);
}

Entity::~Entity()
{
    //dtor
}

sf::Drawable& Entity::getSprite()
{
    return m_shape;
}

void Entity::setPosition(int x, int y)
{
    m_shape.setPosition(x, y);
}

sf::Vector2f Entity::getPosition()
{
    return m_shape.getPosition();
}

void Entity::setSpeed(double x, double y)
{
    m_speed.x = x;
    m_speed.y = y;
}

void Entity::setBoundary(sf::FloatRect rect)
{
    m_boundaries = rect;
}

void Entity::update(double frametime)
{
    double moveX = m_speed.x * frametime;
    double moveY = m_speed.y * frametime;
    m_shape.move(moveX, moveY);

    if(m_shape.getPosition().x < m_boundaries.left
       || m_shape.getPosition().x > m_boundaries.left+m_boundaries.width)
    {
        m_speed.x = -m_speed.x;
        m_shape.setPosition(m_speed.x < 0 ? m_boundaries.left+m_boundaries.width : m_boundaries.left,
                            m_shape.getPosition().y);
    }

    if(m_shape.getPosition().y < m_boundaries.top
       || m_shape.getPosition().y > m_boundaries.top+m_boundaries.height)
    {
        m_speed.y = -m_speed.y;
        m_shape.setPosition(m_shape.getPosition().x,
                            m_speed.y < 0 ? m_boundaries.top+m_boundaries.height : m_boundaries.top);
    }
}

void Entity::display(sf::RenderTarget& screen)
{
    std::cout << m_shape.getFillColor().r << std::endl;
    screen.draw(m_shape);
}