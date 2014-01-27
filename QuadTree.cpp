#include "QuadTree.hpp"

QuadTree::QuadTree(sf::FloatRect boundaries) : m_boundaries(boundaries)
{}

QuadTree::~QuadTree()
{}

bool QuadTree::insert(Entity* entity)
{
    if(!m_boundaries.contains(entity->getPosition()))
        return false;

    if(m_entities.size() < NODE_CAPACITY)
    {
        m_entities.push_back(entity);
        return true;
    }
    else
    {
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
    }

    return false;
}

void QuadTree::subdivide()
{

}

