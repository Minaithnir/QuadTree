#ifndef QUADTREE_H
#define QUADTREE_H

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

#define NODE_CAPACITY 2

class QuadTree
{
    public:
        QuadTree(sf::FloatRect boundaries);
        virtual ~QuadTree();

        bool insert(Entity* entity);
        void subdivide();
        void clear();

        void display(sf::RenderTarget& screen);

        long getCount();

    protected:
        std::vector<Entity*> m_entities;

        QuadTree* m_nw;
        QuadTree* m_ne;
        QuadTree* m_sw;
        QuadTree* m_se;

        sf::FloatRect m_boundaries;

        sf::RectangleShape m_shape;
};

#endif // QUADTREE_H
