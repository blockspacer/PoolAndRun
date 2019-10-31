#ifndef COMPONENTMANAGERSINGLETON_H
#define COMPONENTMANAGERSINGLETON_H

#include <unordered_map>
#include <cstdint>
#include <vector>

#include <EntityManagerSingleton.h>
#include <Component.h>
#include <PositionComponent.h>

//template pour les association Entit�<->Component
template <typename T>
using EntityComponentMap = std::unordered_map<Entity, T&>;

class ComponentManagerSingleton
{
    public:
        static ComponentManagerSingleton* getInstance(); //r�cup�re l'instance du singleton
        virtual ~ComponentManagerSingleton(); //destructeur du singleton

        template <typename T>
        void addComponent(ComponentID component);
        void addComponentToEntity(Component& component, Entity entity); //ajoute un composant donn� � l'entit�
        void removeComponentFromEntity(ComponentID component, Entity entity); //retire le composant donn� de l'entit�
        void removeAllFromEntity(Entity entity); //retire tous les composant de l'entit� (avant suppresion de l'entit� par exemple)

        EntityComponentMap<Component>* getEntityComponentMap(ComponentID component);

    protected:

    private:
        ComponentManagerSingleton();//cr�e l'instance du singleton si besoin
        static inline ComponentManagerSingleton* instance = 0; //instance du singleton

        std::vector<EntityComponentMap<Component>*> maps; //vector contenant toutes les association
        std::unordered_map<ComponentID, int> componentIndexes; // map contenant l'index de chaque map d'association en fonction de l'index de chaque type de component
};

#endif // COMPONENTMANAGERSINGLETON_H
