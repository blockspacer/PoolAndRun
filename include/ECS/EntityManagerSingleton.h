#ifndef ENTITYMANAGERSINGLETON_H
#define ENTITYMANAGERSINGLETON_H

#include <cstdint> //pour les uint
#include <vector>

using Entity = uint32_t; //une entit� n'�tant repr�sent�e que par un ID, on cr�e un alias d'un entier non sign� de 32 bits

class EntityManagerSingleton
{
    public:
        static const Entity MAX_ENTITY = 10000; //nombre maximum d'entit�s qui pourront �tre cr��es

        static EntityManagerSingleton* getInstance(); //renvois l'instance du singleton
        virtual ~EntityManagerSingleton(); //destructeur

        Entity createNewEntity(); //ajoute une nouvelle entit�s � la liste des entit� existantes et renvoie cette entit�
        int indexOf(Entity entity) const; //donne la position de l'entit� pass�e en argument si elle existe, -1 dans le cas contraire
        void deleteEntity(Entity entity); //retire l'entit� de la liste des entit� existante
    protected:

    private:
        EntityManagerSingleton(); //cr�e l'instance du singleton si besoin
        static inline EntityManagerSingleton* instance = 0; //instance du singleton

        static inline Entity nextEntity = 0; //identifiant de la prochaine entit� qui sera cr��e.
        std::vector<Entity> entities; //liste des entit�s existantes
};

#endif // ENTITYMANAGERSINGLETON_H
