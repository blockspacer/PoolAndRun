#include "ComponentManagerSingleton.h"
#include <iostream>

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

//template<typename T>
void ComponentManagerSingleton::addComponentToEntity(Component& component, ComponentID componentId, Entity entity) //ajoute un composant donn� � l'entit�
{
    switch (componentId)
    {
        case PositionComponent::ID :{
                PositionComponent& casted = dynamic_cast<PositionComponent&>(component);
                entityPositions.insert(std::pair<Entity, std::unique_ptr<PositionComponent>>(entity, std::unique_ptr<PositionComponent>(&casted)));
                break;
        }

        case VelocityComponent::ID :{
                VelocityComponent& casted = dynamic_cast<VelocityComponent&>(component);
                entityVelocities.insert(std::pair<Entity, std::unique_ptr<VelocityComponent>>(entity, std::unique_ptr<VelocityComponent>(&casted)));
                break;
        }

        case GravityComponent::ID :{
                GravityComponent& casted = dynamic_cast<GravityComponent&>(component);
                entityGravities.insert(std::pair<Entity, std::unique_ptr<GravityComponent>>(entity, std::unique_ptr<GravityComponent>(&casted)));
                break;
        }

        case RendererComponent::ID :{
                RendererComponent& casted = dynamic_cast<RendererComponent&>(component);
                entityRenderers.insert(std::pair<Entity, std::unique_ptr<RendererComponent>>(entity, std::unique_ptr<RendererComponent>(&casted)));
                break;
        }

        case ColliderComponent::ID :{
                ColliderComponent& casted = dynamic_cast<ColliderComponent&>(component);
                entityColliders.insert(std::pair<Entity, std::unique_ptr<ColliderComponent>>(entity, std::unique_ptr<ColliderComponent>(&casted)));
                break;
        }

        case TriggerComponent::ID :{
                TriggerComponent& casted = dynamic_cast<TriggerComponent&>(component);
                entityTriggers.insert(std::pair<Entity, std::unique_ptr<TriggerComponent>>(entity, std::unique_ptr<TriggerComponent>(&casted)));
                break;
        }

        case CharacterComponent::ID :{
                CharacterComponent& casted = dynamic_cast<CharacterComponent&>(component);
                entityCharacters.insert(std::pair<Entity, std::unique_ptr<CharacterComponent>>(entity, std::unique_ptr<CharacterComponent>(&casted)));
                break;
        }

        case ConstraintComponent::ID :{
                ConstraintComponent& casted = dynamic_cast<ConstraintComponent&>(component);
                entityConstraints.insert(std::pair<Entity, std::unique_ptr<ConstraintComponent>>(entity, std::unique_ptr<ConstraintComponent>(&casted)));
                break;
        }

        case RespawnComponent::ID:{
                RespawnComponent& casted = dynamic_cast<RespawnComponent&>(component);
                entityRespawn.insert(std::pair<Entity, std::unique_ptr<RespawnComponent>>(entity, std::unique_ptr<RespawnComponent>(&casted)));
                break;
        }
        case ControllerComponent::ID:{
                ControllerComponent& casted = dynamic_cast<ControllerComponent&>(component);
                entityController.insert(std::pair<Entity, std::unique_ptr<ControllerComponent>>(entity, std::unique_ptr<ControllerComponent>(&casted)));
                break;
        }
    }
}

void ComponentManagerSingleton::removeComponentFromEntity(ComponentID component, Entity entity)
{
    switch(component)
    {
        case PositionComponent::ID : {entityPositions.erase(entity);}break;
        case VelocityComponent::ID : {entityVelocities.erase(entity);}break;
        case GravityComponent::ID : {entityGravities.erase(entity);}break;
        case RendererComponent::ID : {entityRenderers.erase(entity);}break;
        case ColliderComponent::ID : {entityColliders.erase(entity);}break;
        case TriggerComponent::ID : {entityTriggers.erase(entity);}break;
        case CharacterComponent::ID : {entityCharacters.erase(entity);}break;
        case ConstraintComponent::ID : {entityConstraints.erase(entity);}break;
        case RespawnComponent::ID : {entityRespawn.erase(entity);}break;
        case ControllerComponent::ID : {entityController.erase(entity);}break;
    }
}

void ComponentManagerSingleton::removeAllFromEntity(Entity entity)
{
    removeComponentFromEntity(PositionComponent::ID, entity);
    removeComponentFromEntity(VelocityComponent::ID, entity);
    removeComponentFromEntity(GravityComponent::ID, entity);
    removeComponentFromEntity(RendererComponent::ID, entity);
    removeComponentFromEntity(ColliderComponent::ID, entity);
    removeComponentFromEntity(TriggerComponent::ID, entity);
    removeComponentFromEntity(CharacterComponent::ID, entity);
    removeComponentFromEntity(ConstraintComponent::ID, entity);
    removeComponentFromEntity(RespawnComponent::ID, entity);
    removeComponentFromEntity(ControllerComponent::ID, entity);
}

EntityComponentMap<PositionComponent>& ComponentManagerSingleton::getEntityPositionMap()
{
    return entityPositions;
}

EntityComponentMap<VelocityComponent>& ComponentManagerSingleton::getEntityVelocityMap()
{
    return entityVelocities;
}

EntityComponentMap<GravityComponent>& ComponentManagerSingleton::getEntityGravityMap()
{
    return entityGravities;
}

EntityComponentMap<RendererComponent>& ComponentManagerSingleton::getEntityRendererMap()
{
    return entityRenderers;
}

EntityComponentMap<ColliderComponent>& ComponentManagerSingleton::getEntityColliderMap()
{
    return entityColliders;
}

EntityComponentMap<TriggerComponent>& ComponentManagerSingleton::getEntityTriggerMap()
{
    return entityTriggers;
}

EntityComponentMap<CharacterComponent>& ComponentManagerSingleton::getEntityCharacterMap()
{
    return entityCharacters;
}

EntityComponentMap<ConstraintComponent>& ComponentManagerSingleton::getEntityConstraintMap()
{
    return entityConstraints;
}

EntityComponentMap<RespawnComponent>& ComponentManagerSingleton::getEntityRespawnMap()
{
    return entityRespawn;
}

EntityComponentMap<ControllerComponent>& ComponentManagerSingleton::getEntityControllerMap()
{
    return entityController;
}
