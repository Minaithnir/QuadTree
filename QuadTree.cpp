#include "QuadTree.hpp"
#include <iostream>
#include <sstream>

QuadTree::QuadTree(sf::FloatRect boundaries) : m_boundaries(boundaries), m_nw(NULL), m_ne(NULL), m_sw(NULL), m_se(NULL)
{
    m_shape = sf::RectangleShape(sf::Vector2f(m_boundaries.width, m_boundaries.height));
    m_shape.setOutlineColor(sf::Color::Black);
    m_shape.setOutlineThickness(1);
    m_shape.setPosition(m_boundaries.left, m_boundaries.top);
    m_shape.setFillColor(sf::Color::White);
}

QuadTree::~QuadTree()
{
}

bool QuadTree::insert(Entity* entity)
{
    if(!m_boundaries.contains(entity->getPosition()))
        return false;

    if(m_entities.size() < NODE_CAPACITY && m_nw == NULL)
    {
        m_entities.push_back(entity);
        return true;
    }

    if(m_nw == NULL)
    {
        subdivide();
    }

    if(m_nw->insert(entity))
        return true;
    if(m_ne->insert(entity))
        return true;
    if(m_sw->insert(entity))
        return true;
    if(m_se->insert(entity))
        return true;

    return false;
}

void QuadTree::subdivide()
{
    m_nw = new QuadTree(sf::FloatRect(m_boundaries.left, m_boundaries.top,
                                      m_boundaries.width/2, m_boundaries.height/2));
    m_ne = new QuadTree(sf::FloatRect(m_boundaries.left+m_boundaries.width/2, m_boundaries.top,
                                      m_boundaries.width/2, m_boundaries.height/2));
    m_sw = new QuadTree(sf::FloatRect(m_boundaries.left, m_boundaries.top+m_boundaries.height/2,
                                      m_boundaries.width/2, m_boundaries.height/2));
    m_se = new QuadTree(sf::FloatRect(m_boundaries.left+m_boundaries.width/2, m_boundaries.top+m_boundaries.height/2,
                                      m_boundaries.width/2, m_boundaries.height/2));

    Entity* entity;
    while(!m_entities.empty())
    {
        entity = m_entities.back();
        if(!m_nw->insert(entity))
            if(!m_ne->insert(entity))
                if(!m_sw->insert(entity))
                    m_se->insert(entity);
        m_entities.pop_back();
    }
}

void QuadTree::clear()
{
    if(m_nw != NULL)
    {
        m_nw->clear();
        delete m_nw;
        m_nw = NULL;

        m_ne->clear();
        delete m_ne;

        m_sw->clear();
        delete m_sw;

        m_se->clear();
        delete m_se;
    }

    while(!m_entities.empty())
    {
        m_entities.pop_back();
    }
}

void QuadTree::display(sf::RenderTarget& screen)
{
    m_shape = sf::RectangleShape(sf::Vector2f(m_boundaries.width, m_boundaries.height));
    m_shape.setOutlineColor(sf::Color::Black);
    m_shape.setOutlineThickness(1);
    m_shape.setPosition(m_boundaries.left, m_boundaries.top);
    m_shape.setFillColor(sf::Color::White);
    screen.draw(m_shape);

    if(m_nw != NULL)
    {
        m_nw->display(screen);
        m_ne->display(screen);
        m_sw->display(screen);
        m_se->display(screen);
    }
}

long QuadTree::getCount()
{
    if(m_nw != NULL)
        return m_nw->getCount() + m_ne->getCount() + m_sw->getCount() + m_se->getCount();
    else
        return m_entities.size();
}
