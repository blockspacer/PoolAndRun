#include "ComponentManagerSingleton.h"

ComponentManagerSingleton::ComponentManagerSingleton()
{}

ComponentManagerSingleton::~ComponentManagerSingleton()
{
    delete instance;
}

ComponentManagerSingleton* ComponentManagerSingleton::getInstance()
{
    if(instance == 0)
    {
        instance = new ComponentManagerSingleton();
    }

    return instance;
}

template <typename T>
void ComponentManagerSingleton::addComponent(ComponentID component)
{
    maps.push_back(EntityComponentMap<T>());
    T test = maps[maps.size()-1];
    componentIndexes.insert(std::pair<ComponentID, int>(component, maps.size()-1));
}

void ComponentManagerSingleton::addComponentToEntity(Component& component, Entity entity)
{
    //r�cup�re l'index de la map de liaison dans le tableau grace � la map d'index
    int index = componentIndexes.at(component.getTypeId());
    //r�cup�re la map dans le tableau grace � l'index
    EntityComponentMap<Component&>& linkMap = *maps[index];

    //ajoute le lien entity-component dans la map si il n'y est pas deja
    if(linkMap.find(entity) != linkMap.end())
    {
        linkMap.insert(std::pair<Entity, Component&>(entity, component));
    }
}

void ComponentManagerSingleton::removeComponentFromEntity(ComponentID component, Entity entity)
{
    //r�cup�re l'index de la map de liaison dans le tableau grace � la map d'index
    int index = componentIndexes.at(component);
    //r�cup�re la map dans le tableau grace � l'index
    EntityComponentMap<Component&>& linkMap = *maps[index];

    //essaye de supprimer le lien entity-component de la map
    linkMap.erase(entity);
}

void ComponentManagerSingleton::removeAllFromEntity(Entity entity)
{
    for(EntityComponentMap<Component&>* linkMap : maps)
    {
        linkMap->erase(entity);
    }
}

EntityComponentMap<Component>* ComponentManagerSingleton::getEntityComponentMap(ComponentID component)
{
    //r�cup�re l'index de la map de liaison dans le tableau grace � la map d'index
    int index = componentIndexes.at(component);
    //r�cup�re la map dans le tableau grace � l'index
    return maps[index];

}
