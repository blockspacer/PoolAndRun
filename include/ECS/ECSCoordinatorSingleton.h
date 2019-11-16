#ifndef ECSCOORDINATORSINGLETON_H
#define ECSCOORDINATORSINGLETON_H

#include <EntityManagerSingleton.h>
#include <ComponentManagerSingleton.h>
#include <SystemManagerSingleton.h>

class ECSCoordinatorSingleton
{
    public:
        static ECSCoordinatorSingleton* getInstance();
        virtual ~ECSCoordinatorSingleton();

        Entity createNewEntity(); //cr�e une nouvelle entit� et la renvoie pour utilisation
        void removeEntity(Entity entity); //supprime une Entit� du syst�me

        void removeComponentFromEntity(ComponentID component, Entity entity); //retire le component de l'entit�

        void addSystem(System* system); //ajoute un systeme � execut� lors de l'execution /!\ ajouter dans l'ordre d'execution voulu /!\//
        void addSystem(RenderSystem* render);
        void updateSystems(float dt); //met � jour les systeme en leur disant le temps ecouler depuis la derni�re update
        void updateRender(float dt, sf::RenderWindow& view); //permet de mettre a jour le render s�parement des autres syst�mes
    protected:

    private:
        ECSCoordinatorSingleton();

        static inline ECSCoordinatorSingleton* instance = 0;

        EntityManagerSingleton* entityManager = EntityManagerSingleton::getInstance();
        ComponentManagerSingleton* componentManager = ComponentManagerSingleton::getInstance();
        SystemManagerSingleton* systemManager = SystemManagerSingleton::getInstance();
};

#endif // ECSCOORDINATORSINGLETON_H
