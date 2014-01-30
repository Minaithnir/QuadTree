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
        bool remove(Entity* entity);
        bool merge();
        void split();

        std::vector<Entity*> getEntities();
        void clear();

        void display(sf::RenderTarget& screen);

        long getCount();

    protected:
        std::vector<Entity*> m_entities;

        sf::FloatRect m_boundaries;

        QuadTree* m_nw;
        QuadTree* m_ne;
        QuadTree* m_sw;
        QuadTree* m_se;

        sf::Font m_f;
        sf::Text m_t;

        sf::RectangleShape m_shape;
};

#endif // QUADTREE_H
