#ifndef QUADTREE_H
#define QUADTREE_H

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include <list>

#define NODE_CAPACITY 2
#define MIN_NODE_SIZE 10

class QuadTree
{
    public:
        QuadTree(sf::FloatRect boundaries);
        virtual ~QuadTree();

        bool insert(Entity* entity);
        bool remove(Entity* entity);
        bool merge();
        void split();

        std::list<Entity*> getEntities();
        std::list<Entity*> range(float x, float y, float range);
        void clear();

        void display(sf::RenderTarget& screen);

        long getCount();

    protected:
        std::list<Entity*> m_entities;

        sf::FloatRect m_boundaries;

        sf::VertexArray m_lines;

        QuadTree* m_nw;
        QuadTree* m_ne;
        QuadTree* m_sw;
        QuadTree* m_se;
};

#endif // QUADTREE_H
