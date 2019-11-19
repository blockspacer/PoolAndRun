#ifndef PHYSICSYSTEM_H
#define PHYSICSYSTEM_H

#include <System.h>
#include <iostream>

class PhysicSystem : public System
{
    public:
        PhysicSystem(Positions& p, Velocities& v, Gravities& g, Constraints& c);
        virtual ~PhysicSystem();

        virtual void update(float dt);

        void addGravityToVelocity(Entity entity, float dt); //ajoute la force de gravit� sur la v�locit� des entit�s poss�dant les deux composant
        void addVelocityToPosition(Entity entity, float dt); //ajoute la v�locit� � la position des entit�s poss�dants les deux composant
        void applyFriction(Entity entity, float dt); //applique une force de friction sur base de la velocit�
        void applyConstraints(Entity entity); //applique les contraintes en annulant la velocit� si besoin


    protected:

    private:
        Positions* positions;
        Velocities* velocities;
        Gravities* gravities;
        Constraints* constraints;
        static inline const float frictionCoefficient = 0.3;
};

#endif // PHYSICSYSTEM_H
