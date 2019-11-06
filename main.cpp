#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "Game.h"

#include "ECSCoordinatorSingleton.h"
#include "AssetManager.h"
#include "InputManager.h"

using std::cout;
using std::endl;


bool test(){
    return true;
}
int main()
{
    pr::AssetManager am;
    am.loadTexture("ball", pr::AssetManager::BALLS_PATH + "ball0.png");

    sf::Sprite ballSprite;
    am.setSpriteTexture(ballSprite, "ball");
    ballSprite.scale(sf::Vector2f(0.1, 0.1));

    pr::InputManager im;

    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
    /*while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    switch(event.mouseButton.button){
                        case sf::Mouse::Left:{
                            if(im.isSpriteClicked(ballSprite, sf::Mouse::Left, window)){
                                cout << "clicked" << endl;
                            }

                            break;
                        }
                    }
            }
        }

        window.clear();
        if(ballSprite.getTexture() != nullptr){
            window.draw(ballSprite);
        }
        window.display();
    }*/





    // Getting instances of ECS Coordinator and ComponenManager singletons
    ECSCoordinatorSingleton& ecs = *(ECSCoordinatorSingleton::getInstance());
    ComponentManagerSingleton& compManager = *(ComponentManagerSingleton::getInstance());

    //ajout des systemes
    PhysicSystem physicSystem = PhysicSystem(
                                        compManager.getEntityPositionMap(),
                                        compManager.getEntityVelocityMap(),
                                        compManager.getEntityGravityMap()
                                       );

    RenderSystem renderSystem = RenderSystem(
                                       compManager.getEntityPositionMap(),
                                       compManager.getEntityRendererMap(),
                                       window,
                                       am
                                       );
    ecs.addSystem(physicSystem);
    ecs.addSystem(renderSystem);


    PositionComponent& position = *(new PositionComponent(0, 0));
    GravityComponent& gravity = *(new GravityComponent());
    VelocityComponent& velocity = *(new VelocityComponent());
    RendererComponent& render = *(new RendererComponent("ball"));

    Entity e1 = ecs.createNewEntity();
    compManager.addComponentToEntity(position, PositionComponent::ID, e1);
    compManager.addComponentToEntity(gravity, GravityComponent::ID, e1);
    compManager.addComponentToEntity(velocity, VelocityComponent::ID, e1);
    compManager.addComponentToEntity(render, RendererComponent::ID, e1);

    float dt = 0.0f;
    float time = 0.0f;

	while (time < 20)
	{
		auto startTime = std::chrono::high_resolution_clock::now();

		ecs.updateSystems(dt);
        sf::sleep(sf::milliseconds(20));

		auto stopTime = std::chrono::high_resolution_clock::now();
		dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
		time+=dt;

		cout << time << endl << endl;
	}

    delete &position, &gravity, &velocity, &render;
    return 0;
}
