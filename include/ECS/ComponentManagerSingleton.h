#ifndef COMPONENTMANAGERSINGLETON_H
#define COMPONENTMANAGERSINGLETON_H

#include <unordered_map>
#include <cstdint>
#include <vector>

#include <EntityManagerSingleton.h>

#include <Component.h>
#include <PositionComponent.h>
#include <VelocityComponent.h>
#include <GravityComponent.h>
#include <RendererComponent.h>
#include <ColliderComponent.h>
#include <TriggerComponent.h>
#include <CheckPointTriggerComponent.h>
#include <CharacterComponent.h>
#include <ConstraintComponent.h>
#include <RespawnComponent.h>
#include <ControllerComponent.h>
#include <UIComponent.h>

//template pour les association Entit�<->Component
template <typename T>
using EntityComponentMap = std::unordered_map<Entity, std::unique_ptr<T>>;

class ComponentManagerSingleton
{
    public:
        static ComponentManagerSingleton* getInstance(); //r�cup�re l'instance du singleton
        virtual ~ComponentManagerSingleton(); //destructeur du singleton

//        template<typename T>
        void addComponentToEntity(Component& component, ComponentID componentId, Entity entity); //ajoute un composant donn� � l'entit�
        void removeComponentFromEntity(ComponentID component, Entity entity); //retire le composant donn� de l'entit�
        void removeAllFromEntity(Entity entity); //retire tous les composant de l'entit� (avant suppresion de l'entit� par exemple)

        EntityComponentMap<PositionComponent>& getEntityPositionMap();
        EntityComponentMap<VelocityComponent>& getEntityVelocityMap();
        EntityComponentMap<GravityComponent>& getEntityGravityMap();
        EntityComponentMap<RendererComponent>& getEntityRendererMap();
        EntityComponentMap<ColliderComponent>& getEntityColliderMap();
        EntityComponentMap<TriggerComponent>& getEntityTriggerMap();
        EntityComponentMap<CharacterComponent>& getEntityCharacterMap();
        EntityComponentMap<ConstraintComponent>& getEntityConstraintMap();
        EntityComponentMap<RespawnComponent>& getEntityRespawnMap();
        EntityComponentMap<ControllerComponent>& getEntityControllerMap();
        EntityComponentMap<UIComponent>& getEntityUIMap();

    protected:

    private:
        ComponentManagerSingleton();//cr�e l'instance du singleton si besoin
        static inline ComponentManagerSingleton* instance = 0; //instance du singleton

        //ajouter une map par Component possible
        EntityComponentMap<PositionComponent> entityPositions;
        EntityComponentMap<VelocityComponent> entityVelocities;
        EntityComponentMap<GravityComponent> entityGravities;
        EntityComponentMap<RendererComponent> entityRenderers;
        EntityComponentMap<ColliderComponent> entityColliders;
        EntityComponentMap<TriggerComponent> entityTriggers;
        EntityComponentMap<CharacterComponent> entityCharacters;
        EntityComponentMap<ConstraintComponent> entityConstraints;
        EntityComponentMap<RespawnComponent> entityRespawn;
        EntityComponentMap<ControllerComponent> entityController;
        EntityComponentMap<UIComponent> entityUI;
};

#endif // COMPONENTMANAGERSINGLETON_H
