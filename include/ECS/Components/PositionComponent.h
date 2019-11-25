

#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include <Component.h>


class PositionComponent : public Component
{
    public:
        PositionComponent(float x = 0, float y = 0); //cr�e une position sur base de 2 r�els
        PositionComponent(sf::Vector2f position); // cr�e une position sur base d'un vecteur2 de r�els
        virtual ~PositionComponent();

        static inline const ComponentID ID = 0; //l'ID du composant

        sf::Vector2f getPosition() const;
        virtual ComponentID getTypeId() const;

        void translate(float dx, float dy); //d�place la position selon 2 r�els
        void translate(sf::Vector2f dp); //d�place la position selon un vecteur2 de r�els
        void setPosition(float x, float y); //change la position selon 2 r�els
        void setPosition(sf::Vector2f position); //change la position selon un vecteur2 de r�els;

        virtual std::string str() const;

    protected:

    private:
        sf::Vector2f position;
};

#endif // POSITONCOMPONENT_H
