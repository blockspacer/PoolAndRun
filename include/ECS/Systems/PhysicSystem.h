#ifndef PHYSICSYSTEM_H
#define PHYSICSYSTEM_H

#include <System.h>

class PhysicSystem : public System
{
    public:
        PhysicSystem(Positions& p, Velocities& v, Gravities& g);
        virtual ~PhysicSystem();

        virtual void update(float dt);

        void addGravityToVelocity(Entity entity, float dt); //ajoute la force de gravit� sur la v�locit� des entit�s poss�dant les deux composant
        void addVelocityToPosition(Entity entity, float dt); //ajoute la v�locit� � la position des entit�s poss�dants les deux composant

    protected:

    private:
        Positions* positions;
        Velocities* velocities;
        Gravities* gravities;
};

#endif // PHYSICSYSTEM_H
