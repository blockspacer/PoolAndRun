#include "EntityCreator.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "ECSCoordinatorSingleton.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "ComponentManagerSingleton.h"

#include <iostream>


EntityCreator::EntityCreator()
{
    //ctor
}

EntityCreator::~EntityCreator()
{
    //dtor
}

//methode pour la creation d'un joueur
Entity EntityCreator::createPlayer(float x, float y, std::string textureName, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs){

    Entity player = ecs.createNewEntity();

    compManager.addComponentToEntity(*(new CharacterComponent("H�ro", TAG_PLAYER, 7)), CharacterComponent::ID, player);
    compManager.addComponentToEntity(*(new RendererComponent(textureName, sf::Vector2f(0.075, 0.075), 4)), RendererComponent::ID, player);
    compManager.addComponentToEntity(*(new PositionComponent(coordinateConverter(sf::Vector2f(x, y)))), PositionComponent::ID, player);
    compManager.addComponentToEntity(*(new VelocityComponent()), VelocityComponent::ID, player);
    compManager.addComponentToEntity(*(new GravityComponent()), GravityComponent::ID, player);
    compManager.addComponentToEntity(*(new ConstraintComponent()), ConstraintComponent::ID, player);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::PixelPerfect, false, 0.8)), ColliderComponent::ID, player);
    compManager.addComponentToEntity(*(new ControllerComponent(100, 320, 200, 2.5)), ControllerComponent::ID, player);
    return player;
}

Entity EntityCreator::createTile(float x, float y, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs){
    Entity platform = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new RendererComponent("tile", sf::Vector2f(1, 1), -1)), RendererComponent::ID, platform);
    compManager.addComponentToEntity(*(new PositionComponent(coordinateConverter(sf::Vector2f(x, y)))), PositionComponent::ID, platform);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::Box, false, 0.6)), ColliderComponent::ID, platform);

    return platform;
}
//cr�ation d'un ennemi boule
Entity EntityCreator::createEnnemyBall(float x, float y, std::string textureName, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs){

    Entity ball = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new CharacterComponent(textureName, TAG_ENEMY_BALL, 0)), CharacterComponent::ID, ball);
    compManager.addComponentToEntity(*(new RendererComponent(textureName, sf::Vector2f(0.07, 0.07), 3)), RendererComponent::ID, ball);
    compManager.addComponentToEntity(*(new PositionComponent(coordinateConverter(sf::Vector2f(x, y)))), PositionComponent::ID, ball);
    compManager.addComponentToEntity(*(new VelocityComponent()), VelocityComponent::ID, ball);
    compManager.addComponentToEntity(*(new GravityComponent()), GravityComponent::ID, ball);
    compManager.addComponentToEntity(*(new ConstraintComponent()), ConstraintComponent::ID, ball);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::PixelPerfect, false, 0.8)), ColliderComponent::ID, ball);

    return ball;
}

//cr�ation d'un ennemi queue
Entity EntityCreator::createEnnemyCue(float x, float y, std::string textureName, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs) {
    Entity cue = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new CharacterComponent("Queue", TAG_ENEMY_CUE, 0)), CharacterComponent::ID, cue);
    compManager.addComponentToEntity(*(new RendererComponent(textureName, sf::Vector2f(1.5, 1.1), 3)), RendererComponent::ID, cue);
    compManager.addComponentToEntity(*(new PositionComponent(coordinateConverter(sf::Vector2f(x, y)))), PositionComponent::ID, cue);
    compManager.addComponentToEntity(*(new VelocityComponent()), VelocityComponent::ID, cue);
    compManager.addComponentToEntity(*(new GravityComponent()), GravityComponent::ID, cue);
    compManager.addComponentToEntity(*(new ConstraintComponent()), ConstraintComponent::ID, cue);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::PixelPerfect, false, 0)), ColliderComponent::ID, cue);
    compManager.addComponentToEntity(*(new CueAttackTriggerComponent()), TriggerComponent::ID, cue);

    return cue;
}

//cr�ation du point de point de controle
Entity EntityCreator::createCheckPoint(float x, float y, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs){

    Entity checkPoint = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new RendererComponent("checkPoint", sf::Vector2f(1, 1), 2)), RendererComponent::ID, checkPoint);
    compManager.addComponentToEntity(*(new PositionComponent(coordinateConverter(sf::Vector2f(x, y)))), PositionComponent::ID, checkPoint);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::Box, true, 0)), ColliderComponent::ID, checkPoint);
    compManager.addComponentToEntity(*(new CheckPointTriggerComponent()), TriggerComponent::ID, checkPoint);

    return checkPoint;
}


//creation de la zone de t�l�portation
void EntityCreator::createWarp(float x1, float y1,float x2, float y2,  ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs){

    Entity warp1 = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new RendererComponent("warpIn", sf::Vector2f(1, 1),2)), RendererComponent::ID, warp1);
    compManager.addComponentToEntity(*(new PositionComponent(coordinateConverter(sf::Vector2f(x1, y1)))), PositionComponent::ID, warp1);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::Box, true, 0)), ColliderComponent::ID, warp1);
    compManager.addComponentToEntity(*(new WarpTriggerComponent(coordinateConverter(sf::Vector2f(x2, y2)), true)), TriggerComponent::ID, warp1);

    Entity warp2 = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new RendererComponent("warpOut", sf::Vector2f(1, 1), 2)), RendererComponent::ID, warp2);
    compManager.addComponentToEntity(*(new PositionComponent(coordinateConverter(sf::Vector2f(x2, y2)))), PositionComponent::ID, warp2);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::Box, true, 0)), ColliderComponent::ID, warp2);
    compManager.addComponentToEntity(*(new WarpTriggerComponent(coordinateConverter(sf::Vector2f(x1, y1)), false)), TriggerComponent::ID, warp2);

}
//creation des trous
Entity EntityCreator::createHole(float x, float y, std::string targetTag, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs){

    Entity hole = ecs.createNewEntity();
    if(targetTag == TAG_ENEMY_BALL)
    {
        compManager.addComponentToEntity(*(new RendererComponent("holeEnemy", sf::Vector2f(1, 1), 2)), RendererComponent::ID, hole);
    }else
    {
        compManager.addComponentToEntity(*(new RendererComponent("holePlayer", sf::Vector2f(1, 1), 2)), RendererComponent::ID, hole);
    }
    compManager.addComponentToEntity(*(new PositionComponent(coordinateConverter(sf::Vector2f(x, y)))), PositionComponent::ID, hole);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::Box, true, 0)), ColliderComponent::ID, hole);
    compManager.addComponentToEntity(*(new HoleTriggerComponent(targetTag)), TriggerComponent::ID, hole);
    return hole;
}

//creation de la fin du niveau
Entity EntityCreator::createEndLevel(float x, float y, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs){

    Entity endLevel = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new RendererComponent("endLevel", sf::Vector2f(1, 1), 2)), RendererComponent::ID, endLevel);
    compManager.addComponentToEntity(*(new PositionComponent(coordinateConverter(sf::Vector2f(x, y)))), PositionComponent::ID, endLevel);
    compManager.addComponentToEntity(*(new ColliderComponent(ColliderTypeEnum::Box, true, 0)), ColliderComponent::ID, endLevel);
    compManager.addComponentToEntity(*(new EndLevelTriggerComponent()), TriggerComponent::ID, endLevel);
    return endLevel;

}

//creation d'un �l�ment d'interface
Entity EntityCreator::createUIElement(float x, float y, float sx, float sy, UITypeEnum uiType, int data, std::string textureName, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs)
{
    Entity ui = ecs.createNewEntity();
    compManager.addComponentToEntity(*(new RendererComponent(textureName, sf::Vector2f(sx, sy), 5)), RendererComponent::ID, ui);
    compManager.addComponentToEntity(*(new PositionComponent(x, y)), PositionComponent::ID, ui);
    compManager.addComponentToEntity(*(new UIComponent(uiType, data)), UIComponent::ID, ui);
    return ui;
}

//creation des �l�ments de la barre de vie
void EntityCreator::createHealthBar(float x, float y, ComponentManagerSingleton& compManager, ECSCoordinatorSingleton& ecs)
{
    createUIElement(x, y, 0.05, 0.05, UITypeEnum::HealthBar, 0, "ball8", compManager, ecs);
    createUIElement(x, y, 0.05, 0.05, UITypeEnum::HealthBar, 1, "ball1", compManager, ecs);
    createUIElement(x+15, y, 0.05, 0.05, UITypeEnum::HealthBar, 2, "ball2", compManager, ecs);
    createUIElement(x+30, y, 0.05, 0.05, UITypeEnum::HealthBar, 3, "ball3", compManager, ecs);
    createUIElement(x+45, y, 0.05, 0.05, UITypeEnum::HealthBar, 4, "ball4", compManager, ecs);
    createUIElement(x+60, y, 0.05, 0.05, UITypeEnum::HealthBar, 5, "ball5", compManager, ecs);
    createUIElement(x+75, y, 0.05, 0.05, UITypeEnum::HealthBar, 6, "ball6", compManager, ecs);
    createUIElement(x+90, y, 0.05, 0.05, UITypeEnum::HealthBar, 7, "ball7", compManager, ecs);
}

//convertit les coordonn�e de cr�ation en position
sf::Vector2f EntityCreator::coordinateConverter(sf::Vector2f position)
{
    sf::Vector2f result = sf::Vector2(position.x * TILE_WIDTH, position.y * TILE_HEIGHT);
    return result;
}
