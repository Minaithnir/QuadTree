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


    m_f.loadFromFile("times.ttf");
    m_t.setFont(m_f);
    m_t.setCharacterSize(24);
    m_t.setPosition(m_boundaries.left+5,m_boundaries.top+5);
    m_t.setColor(sf::Color::Red);
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
    {
        return false;
    }
    else if(m_entities.size() < NODE_CAPACITY && m_nw == NULL)
    {
        m_entities.push_back(entity);
        return true;
    }
    else
    {
        if(m_nw == NULL)
        {
            split();
        }

        if(m_nw->insert(entity))
        {
            std::cout << "inserted nw" << std::endl;
            return true;
        }
        if(m_ne->insert(entity))
        {
            std::cout << "inserted ne" << std::endl;
            return true;
        }
        if(m_sw->insert(entity))
        {
            std::cout << "inserted sw" << std::endl;
            return true;
        }
        if(m_se->insert(entity))
        {
            std::cout << "inserted se" << std::endl;
            return true;
        }
    }



    return false;
}

bool QuadTree::remove(Entity* entity)
{
    bool removed = false;

    if(m_nw == NULL)
    {
        for(std::vector<Entity*>::iterator it=m_entities.begin(); it!=m_entities.end(); it++)
        {
            if((*it) == entity)
            {
                m_entities.erase(it);
                removed = true;
                break;
            }
        }
    }
    else
    {
        removed = m_nw->remove(entity);
        if(!removed)
            removed = m_ne->remove(entity);
        if(!removed)
            removed = m_sw->remove(entity);
        if(!removed)
            removed = m_se->remove(entity);
    }

    if(removed)
        merge();

    return removed;
}

bool QuadTree::merge()
{
    std::cout << getCount() << std::endl;

    if(getCount()<=NODE_CAPACITY && m_nw != NULL)
    {
        m_entities == getEntities();
        delete m_nw;
        m_nw = NULL;
        delete m_ne;
        delete m_sw;
        delete m_se;

        return true;
    }

    std::cout << getCount() << std::endl;

    return false;
}

void QuadTree::split()
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
        insert(entity);
        m_entities.pop_back();
    }
}

std::vector<Entity*> QuadTree::getEntities()
{
    std::vector<Entity*> entities;
    std::vector<Entity*> childEntities;

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

    std::ostringstream convert;
    convert.str("");
    convert << m_entities.size() << " " << getCount();
    m_t.setString(convert.str());

    if(m_nw == NULL)
        m_t.setPosition(m_boundaries.left+5, m_boundaries.top+30);
    else
        m_t.setPosition(m_boundaries.left+5, m_boundaries.top+5);

    screen.draw(m_t);
}

long QuadTree::getCount()
{
    if(m_nw != NULL)
        return m_nw->getCount() + m_ne->getCount() + m_sw->getCount() + m_se->getCount();
    else
        return m_entities.size();
}
