#ifndef SYSTEMMANAGERSINGLETON_H
#define SYSTEMMANAGERSINGLETON_H

#include <vector>

#include "PhysicSystem.h"
#include "RenderSystem.h"
#include "CollisionSystem.h"
#include "RespawnSystem.h"
#include "TriggerSystem.h"
#include "ControllerSystem.h"

class SystemManagerSingleton
{
    public:
        static SystemManagerSingleton* getInstance();
        virtual ~SystemManagerSingleton();
        static void releaseInstance();

        void addSystem(System* system); //ajoute un systeme � l'ECS
        void addSystem(RenderSystem* system); //ajoute le systeme qui g�re le rendu � l'ECS
        void updateSystems(float dt); //met a jour tous les syst�me dans leur ordre d'ajout
        void updateRender(float dt, sf::RenderWindow& window, sf::View& view); //permet de mettre a jour le rendu s�parement des autres syst�mes

    protected:

    private:
        SystemManagerSingleton();
        static inline SystemManagerSingleton* instance = 0;

        std::vector<System*> systems;
        RenderSystem* render = 0; //le systeme de rendu, sera ignor� dans l'updateSystems

};

#endif // SYSTEMMANAGERSINGLETON_H
