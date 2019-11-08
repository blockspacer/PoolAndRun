#include "CollisionSystem.h"

CollisionSystem::CollisionSystem(Characters& cha,
                        Renderers& r,
                        Positions& p,
                        Velocities& ve,
                        Colliders& col,
                        Triggers& t,
                        Constraints& con
                        )
{
    characters = &cha;
    renderers = &r;
    positions = &p;
    velocities = &ve;
    colliders = &col;
    triggers = &t;
    constraints = &con;

}

CollisionSystem::~CollisionSystem()
{
    delete characters;
    delete renderers;
    delete positions;
    delete velocities;
    delete colliders;
    delete triggers;
    delete constraints;
}

///le collisionSystem va permettre de d�tecter les collisions entre les personnages et les autres �l�ments du jeu
///il va parcourir la liste via une double boucle, la premi�re sur les entit�s poss�dant un characterComponent, la deuxieme sur les entit�s poss�dant un ColliderComponent
///pour �viter les tests impossibles on va d'abord v�rifier que les deux entit�s sont suffisamment proches l'une de l'autre
///on va ensuite verifier si il y a collision sur base du type de collider
///si oui on va bloquer le d�placement du personnage dans la direction qui a provoqu� la collision
///si l'entit� a un trigger, on ne bloque pas le d�placement mais on d�clenche la fonction "onTrigger()" du composant
void CollisionSystem::update(float dt)
{
    for(Characters::iterator it1 = characters->begin(); it1 != characters->cend(); it1++)
    {
        Entity e1 = it1->first;
        CharacterComponent& ch1 = it1->second;
        PositionComponent& p1 = positions->at(e1);
        VelocityComponent& v1 = velocities->at(e1);
        RendererComponent& r1 = renderers->at(e1);
        ColliderComponent& co1 = colliders->at(e1);

        //on bouge le sprite pour la dur�e du test de collision
        r1.getSpriteRef().move(v1.getVelocity() * dt);

        for(Colliders::iterator it2 = colliders->begin(); it2 != colliders->cend(); it2++)
        {
            Entity e2 = it2->first;
            PositionComponent& p2 = positions->at(e2);
            RendererComponent& r2 = renderers->at(e2);

            bool colliding = false;

            //verifie si il y a une collision selon 3 test possibles
            if(Vector2fMath::distanceBetween(p1.getPosition(), p2.getPosition()) <= maxCollidingDistance)
            {
                switch (co1.getColliderType())
                {
                    case ColliderTypeEnum::Circle:{
                        colliding = Collision::CircleTest(r1.getSpriteRef(), r2.getSpriteRef());
                        break;
                    }
                    case ColliderTypeEnum::PixelPerfect:{
                        colliding = Collision::PixelPerfectTest(r1.getSpriteRef(), r2.getSpriteRef());
                        break;
                    }
                    default:{//box par defaut
                        colliding = Collision::BoundingBoxTest(r1.getSpriteRef(), r2.getSpriteRef());
                        break;
                    }
                }

            }

            // en cas de collision...
            if(colliding)
            {
                //declenche le trigger de la deuxieme entit� si il existe
                if(triggers->find(e2) != triggers->cend())
                {
                    triggers->at(e2).onTrigger(e1);
                }
                //provoque l'ajout de contrainte sur la premi�re entit� pour limit� son d�placement
                else if(!co1.isCrossable())
                {
                    addCollisionConstraints(r1.getSpriteRef(), r2.getSpriteRef(), e1);
                }
            }
        }
        //on remet le sprite a sa position d'origine
        r1.getSpriteRef().move(-v1.getVelocity() * dt);
    }
}


//ajoute les contraintes ad�quates en fonction de la direction de la collision
void CollisionSystem::addCollisionConstraints(sf::Sprite s1, sf::Sprite s2, Entity entity)
{
    ConstraintComponent& c = constraints->at(entity);
    sf::FloatRect gb1 = s1.getGlobalBounds();
    sf::FloatRect gb2 = s2.getGlobalBounds();
    sf::Vector2 p1 = s1.getPosition();
    sf::Vector2 p2 = s2.getPosition();

    if(p1.x + gb1.width > p2.x && p1.x < p2.x) //collision � droite
    {
        c.addConstraint(ConstraintEnum::Right);
    }
    if(p1.y - gb1.height < p2.y && p1.y > p2.y) //collision en bas
    {
        c.addConstraint(ConstraintEnum::Down);
    }
    if(p2.x + gb2.width > p1.x && p2.x < p1.x) //collision � gauche
    {
        c.addConstraint(ConstraintEnum::Left);
    }
    if(p2.y - gb2.height < p1.y && p2.y > p1.y) //collision en haut
    {
        c.addConstraint(ConstraintEnum::Up);
    }
}
