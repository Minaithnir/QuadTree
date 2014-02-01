QuadTree
========

QuadTree est une simple implementation de l'arbre de partitionnement QuadTree en C++ avec la bibliothèque SFML pour la partie graphique.
Le projet contient à l'heure actuelle une petite démonstration de gestion de collision.

Les entités se déplacent à vitesse fixe et "rebondissent" sur les murs.
Lorsqu'elle entrent en collision avec une autre entitée, elles se colorent en rouge.

#####Système :#####
Ce programme est développé et compilé avec C::B et MinGW sous Windows 7.

#####Contrôles :#####
* A - ajoute un batch d'entités aux coordonnées de la souris avec des vitesses variables
* D - supprime le dernier batch ajouté
* T - active ou desactive l'usage du quadTree pour la gestion des collisions.
* G - active ou desactive l'affichage du quadTree lorsque celui-ci est activé.
