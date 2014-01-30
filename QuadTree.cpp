#include "QuadTree.hpp"
#include <iostream>
#include <sstream>

QuadTree::QuadTree(sf::FloatRect boundaries) : m_boundaries(boundaries), m_nw(NULL), m_ne(NULL), m_sw(NULL), m_se(NULL)
{
    m_lines = sf::VertexArray(sf::LinesStrip, 3);
    m_lines[0].position = sf::Vector2f(m_boundaries.left+m_boundaries.width, m_boundaries.top);
    m_lines[0].color = sf::Color::Black;
    m_lines[1].position = sf::Vector2f(m_boundaries.left+m_boundaries.width, m_boundaries.top+m_boundaries.height);
    m_lines[1].color = sf::Color::Black;
    m_lines[2].position = sf::Vector2f(m_boundaries.left, m_boundaries.top+m_boundaries.height);
    m_lines[2].color = sf::Color::Black;
}

QuadTree::~QuadTree()
{
    if(m_nw != NULL)
    {
        delete m_nw;
        delete m_ne;
        delete m_sw;
        delete m_se;
    }
}

bool QuadTree::insert(Entity* entity)
{
    if(!m_boundaries.contains(entity->getPosition()))
        return false;

    if((m_entities.size() < NODE_CAPACITY && m_nw == NULL) || (m_boundaries.height/2 < MIN_NODE_SIZE) || (m_boundaries.width/2 < MIN_NODE_SIZE))
    {
        m_entities.push_back(entity);
        return true;
    }

    if(m_nw == NULL)
        split();

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

void QuadTree::split()
{
    float halfWidth = m_boundaries.width/2.0f;
    float halfHeight = m_boundaries.height/2.0f;
    float x = m_boundaries.left;
    float y = m_boundaries.top;
    m_nw = new QuadTree(sf::FloatRect(x, y,
                                      halfWidth, halfHeight));
    m_ne = new QuadTree(sf::FloatRect(x+halfWidth, y,
                                      halfWidth, halfHeight));
    m_sw = new QuadTree(sf::FloatRect(x, y+halfHeight,
                                      halfWidth, halfHeight));
    m_se = new QuadTree(sf::FloatRect(x+halfWidth, y+halfHeight,
                                      halfWidth, halfHeight));

    Entity* entity;
    while(!m_entities.empty())
    {
        entity = m_entities.back();
        insert(entity);
        m_entities.pop_back();
    }
}

std::list<Entity*> QuadTree::getEntities()
{
    std::list<Entity*> entities;
    std::list<Entity*> childEntities;

    if(m_nw != NULL)
    {
        childEntities = m_nw->getEntities();
        entities.insert(entities.begin(), childEntities.begin(), childEntities.end());
        childEntities = m_ne->getEntities();
        entities.insert(entities.begin(), childEntities.begin(), childEntities.end());
        childEntities = m_sw->getEntities();
        entities.insert(entities.begin(), childEntities.begin(), childEntities.end());
        childEntities = m_se->getEntities();
        entities.insert(entities.begin(), childEntities.begin(), childEntities.end());

        return entities;
    }

    return m_entities;
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
    else
    {
        m_entities.clear();
    }
}

void QuadTree::display(sf::RenderTarget& screen)
{
    if(m_nw != NULL)
    {
        m_nw->display(screen);
        m_ne->display(screen);
        m_sw->display(screen);
        m_se->display(screen);
    }
    else
        screen.draw(m_lines);
}

long QuadTree::getCount()
{
    if(m_nw != NULL)
        return m_nw->getCount() + m_ne->getCount() + m_sw->getCount() + m_se->getCount();
    else
        return m_entities.size();
}
