#include "CollisionSystem.h"

CollisionSystem::CollisionSystem(Characters& cha,
                        Renderers& r,
                        Positions& p,
                        Velocities& ve,
                        Colliders& col,
                        Triggers& t,
                        Constraints& con,
                        sf::View v
                        )
{
    characters = &cha;
    renderers = &r;
    positions = &p;
    velocities = &ve;
    colliders = &col;
    triggers = &t;
    constraints = &con;
    view = v;

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
///on va ensuite verifier si il y a collision sur base du type de collider, si l'autre entit� est un personnage on va transf�rer une proportion de la v�locit�
///si oui on va bloquer le d�placement du personnage dans la direction qui a provoqu� la collision
///si l'entit� a un trigger, on ne bloque pas le d�placement mais on d�clenche la fonction "onTrigger()" du composant
///si le personnage est le joueur et tombe hors de la cam�ra, on le tue
void CollisionSystem::update(float dt)
{
    for(Characters::iterator it1 = characters->begin(); it1 != characters->cend(); it1++)
    {

        Entity e1 = it1->first;
        CharacterComponent& ch1 = *(it1->second);
        PositionComponent& p1 = *(positions->at(e1));
        VelocityComponent v1 = *(velocities->at(e1));
        RendererComponent& r1 = *(renderers->at(e1));
        ColliderComponent& co1 = *(colliders->at(e1));

        //on bouge le sprite pour la dur�e du test de collision
        r1.getSpriteRef().move(v1.getVelocity() * dt);

        //y a-t-il eu une collision?
        bool colliding = false;

        //test de collision avec les bords de la vue (pour le joueur uniquement)
        if(ch1.getTag() == "Joueur")
        {
            colliding = addViewBorderConstraints(r1.getSpriteRef(), e1);
        }

        //test de collision avec d'autres entit�
        for(Colliders::iterator it2 = colliders->begin(); it2 != colliders->cend(); it2++)
        {
            Entity e2 = it2->first;
            ColliderComponent& c2 = *(it2->second);
            PositionComponent& p2 = *(positions->at(e2));
            RendererComponent& r2 = *(renderers->at(e2));


            if(e1 == e2)
            {
                continue;
            }

            bool collideWith = false;

            //verifie si il y a une collision selon 3 test possibles
            if(Vector2fMath::distanceBetween(p1.getPosition(), p2.getPosition()) <= maxCollidingDistance)
            {
                switch (co1.getColliderType())
                {
                    case ColliderTypeEnum::Circle:{
                        collideWith = Collision::CircleTest(r1.getSpriteRef(), r2.getSpriteRef());
                        break;
                    }
                    case ColliderTypeEnum::PixelPerfect:{
                        collideWith = Collision::PixelPerfectTest(r1.getSpriteRef(), r2.getSpriteRef());
                        break;
                    }
                    default:{//box par defaut
                        collideWith = Collision::BoundingBoxTest(r1.getSpriteRef(), r2.getSpriteRef());
                        break;
                    }
                }

            }

            // en cas de collision...
            if(collideWith)
            {

                //declenche le trigger de la deuxieme entit� si il existe
                if(triggers->find(e2) != triggers->cend())
                {
                    triggers->at(e2)->onTrigger(e1, ch1.getTag());
                }
                //si on ne passe pas au travers de l'autre objet
                else if(!co1.isCrossable())
                {
                    //transfert de vitesse si l'autre entit� c'est un personnage
                    if(characters->find(e2) != characters->cend() && velocities->find(e2) != velocities->cend())
                    {
                        transfertVelocity(e1, e2, c2.getImpactAbsorption());
                    }
                    //sinon evalue la vitesse pour soit rebondir, soit appliquer des contraintes
                    else
                    {
                        if(Vector2fMath::magnitude(v1.getVelocity()) < 5)
                        {
                            addCollisionConstraints(r1.getSpriteRef(), r2.getSpriteRef(), e1);
                        }else
                        {
                            floorBouncing(e1, e2, 0.4);
                        }
                    }
                }

                colliding = true;
            }
        }

        if(!colliding && constraints->find(e1) != constraints->cend()) //si il n'y a pas eu de collision, on retire les contraintes
        {
                removeCollisionConstraints(e1);
        }

        //on remet le sprite a sa position d'origine
        r1.getSpriteRef().move(-v1.getVelocity() * dt);


    }
}

bool CollisionSystem::addViewBorderConstraints(sf::Sprite s, Entity entity)
{
    ConstraintComponent& c = *(constraints->at(entity));
    sf::FloatRect gb = s.getGlobalBounds();
    sf::Vector2 p = s.getPosition();

    sf::Vector2 viewSize = view.getSize();
    sf::Vector2 viewCenter = view.getCenter();

    bool colliding = false;

    if(p.x + gb.width > viewCenter.x + (viewSize.x / 2)) //collision � droite
    {
        c.addConstraint(ConstraintEnum::Right);
        colliding = true;
    }
    if(p.y > viewCenter.y + (viewSize.y / 2)) //collision en bas
    {
        ComponentManagerSingleton::getInstance()->addComponentToEntity(*(new RespawnComponent()), RespawnComponent::ID, entity);
        colliding = true;
    }
    if(viewCenter.x - (viewSize.x / 2) > p.x) //collision � gauche
    {
        c.addConstraint(ConstraintEnum::Left);
        colliding = true;
    }
    if(viewCenter.y - (viewSize.y / 2) > p.y) //collision en haut
    {
        c.addConstraint(ConstraintEnum::Up);
        colliding = true;
    }

    return colliding;
}

//ajoute les contraintes ad�quates en fonction de la direction de la collision
void CollisionSystem::addCollisionConstraints(sf::Sprite s1, sf::Sprite s2, Entity entity)
{
    ConstraintComponent& c = *(constraints->at(entity));
    sf::FloatRect gb1 = s1.getGlobalBounds();
    sf::FloatRect gb2 = s2.getGlobalBounds();
    sf::Vector2 p1 = s1.getPosition();
    sf::Vector2 p2 = s2.getPosition();

    if(p1.x + gb1.width > p2.x && p1.x < p2.x) //collision � droite
    {
        c.addConstraint(ConstraintEnum::Right);
    }
    if(p1.y + gb1.height > p2.y && p1.y < p2.y) //collision en bas
    {
        c.addConstraint(ConstraintEnum::Down);
    }
    if(p2.x + gb2.width > p1.x && p2.x < p1.x) //collision � gauche
    {
        c.addConstraint(ConstraintEnum::Left);
    }
    if(p2.y + gb2.height > p1.y && p2.y < p1.y) //collision en haut
    {
        c.addConstraint(ConstraintEnum::Up);
    }
}

void CollisionSystem::removeCollisionConstraints(Entity entity)
{

    ConstraintComponent& c = *(constraints->at(entity));
    c.removeConstraint(ConstraintEnum::Right);
    c.removeConstraint(ConstraintEnum::Down);
    c.removeConstraint(ConstraintEnum::Up);
    c.removeConstraint(ConstraintEnum::Left);
}

void CollisionSystem::transfertVelocity(Entity e1, Entity e2, float absorption)
{
    sf::Sprite& s1 = renderers->at(e1)->getSpriteRef();
    sf::Sprite& s2 = renderers->at(e2)->getSpriteRef();

    VelocityComponent& v1 = *(velocities->at(e1));
    VelocityComponent& v2 = *(velocities->at(e2));

    float angle12 = Vector2fMath::angleBetween(s1.getPosition(), s2.getPosition());
    float angle21 = Vector2fMath::angleBetween(s2.getPosition(), s1.getPosition());
    float speed = Vector2fMath::magnitude(v1.getVelocity());

    sf::Vector2f dv2 = sf::Vector2f(speed * std::sin(angle12) * absorption, speed * std::cos(angle12) * absorption);
    sf::Vector2f dv1 = sf::Vector2f(speed * std::sin(angle21) * (1-absorption), speed * std::cos(angle21) * (1-absorption));
    v2.addVelocity(dv2);
    v1.addVelocity(dv1);
}

void CollisionSystem::floorBouncing(Entity character, Entity platform, float absorption)
{
    sf::Sprite& s1 = renderers->at(character)->getSpriteRef();
    sf::Sprite& s2 = renderers->at(platform)->getSpriteRef();

    VelocityComponent& v = *(velocities->at(character));

    float angle = Vector2fMath::angleBetween(s2.getPosition(), s1.getPosition()) * 180 / M_PI;
    float speed = Vector2fMath::magnitude(v.getVelocity());

    //arrondi l'angle � un des points cardinaux
    if(angle <= 315 && angle > 225) // viens de la gauche
    {
        angle = 3 * M_PI / 2;
    }else if(angle > 135) //viens d'en haut
    {
        angle = 0;
    }else if(angle > 45) //viens de la droite
    {
        angle = M_PI / 2;
    }else{ //vien d'en bas
        angle = M_PI;
    }

    sf::Vector2f dv = sf::Vector2f(speed * std::sin(angle) * (1+1-absorption), -speed * std::cos(angle) * (1+1-absorption));
    v.addVelocity(dv);
}













