#ifndef QUADTREE_H
#define QUADTREE_H

#include <SFML/System.hpp>
#include "Entity.hpp"

#define NODE_CAPACITY 4

class QuadTree
{
    public:
        QuadTree(sf::FloatRect boundaries);
        virtual ~QuadTree();

        bool insert(Entity* entity);
        void subdivide();


    protected:
        std::vector<Entity*> m_entities;

        QuadTree* m_nw;
        QuadTree* m_ne;
        QuadTree* m_sw;
        QuadTree* m_se;

        sf::FloatRect m_boundaries;
};

#endif // QUADTREE_H
