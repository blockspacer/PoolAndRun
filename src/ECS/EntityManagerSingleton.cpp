

#include "EntityManagerSingleton.h"
#include <iostream>


EntityManagerSingleton::EntityManagerSingleton()
{}

EntityManagerSingleton::~EntityManagerSingleton()
{
    entities.clear();
    nextEntity = 0;
}

void EntityManagerSingleton::releaseInstance()
{
    delete instance;
    nextEntity = 0;
    instance = 0;
}


EntityManagerSingleton* EntityManagerSingleton::getInstance(){
    //cr�e l'instance du singleton si elle n'existe pas encore
    if(instance == 0)
    {   instance = new EntityManagerSingleton(); }

    return instance;
}

Entity EntityManagerSingleton::createNewEntity()
{
    if(nextEntity < MAX_ENTITY) //ajoute l'ID suivant si possible
    {
        entities.push_back(nextEntity++);
        return (nextEntity - 1); //renvoie l'entit� qui viens juste d'�tre cr��e
    }
    //si l'ID suivant est le maximum mais qu'il n'y a pas le maximum d'entit� dans la liste,
    //on parcours cette liste pour trouv� le premier ID libre

    else if(entities.size() < MAX_ENTITY)
    {
        for(uint32_t i = 0; i < entities.size(); i++)
        {
            if(entities[i] != i)
            {
                std::vector<Entity>::iterator it = entities.begin();
                entities.insert(it + i, i);
                return i;  //renvoie l'entit� qui viens juste d'�tre cr��e
            }
        }
    }

    return MAX_ENTITY; //renvoie une valeur fausse pour signifier la non cr�ation de l'entit�
}

int EntityManagerSingleton::indexOf(Entity entity) const
{
    for(int i = 0; i < entities.size(); i++)
    {
        if(entities[i] == entity)
        {
            return i;
        }
    }
    return -1;
}

void EntityManagerSingleton::deleteEntity(Entity entity)
{
    int index = indexOf(entity); //on r�cup�re la position de l'entit� dans le vecteur
    if(index > -1)
    {
        if(index == (entities.size()-1)) //si l'entit� est la derni�re ajout�e, on d�cr�mente nextEntity
        {
            entities.pop_back();
            nextEntity--;
        }else //on laisse un trou qui sera combl� plus tard
        {
            std::vector<Entity>::iterator it = entities.begin();
            entities.erase(it+index);
        }
    }
}

