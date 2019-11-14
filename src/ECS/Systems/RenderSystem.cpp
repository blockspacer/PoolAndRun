#include "RenderSystem.h"

RenderSystem::RenderSystem(Positions& p, Renderers& r, sf::RenderWindow& v, pr::AssetManager& am)
{
    positions = &p;
    renderers = &r;
    view = &v;
    asset = &am;
}

RenderSystem::~RenderSystem()
{
    delete positions;
    delete renderers;
    delete view;
    delete asset;
}


///Le renderSystem va permettre l'affichage des sprites des diff�rentes entit�s sur la vue
///Il va commencer chaque update en nettoyant la vue
///la boucle se fait par couche
///-1 : les tiles, non affich�e mais n�c�ssaires aux calculs de collision
///0 : le background
///1 : le niveau complet
///2 : les triggers
///3 : les ennemis
///4 : le joueur
///5 : le GUI
///ensuite charger la texture sur le sprite si celui ci ne la poss�de pas d�j�
///puis il va ajuster l'echelle du sprite
///avant de finalement le dessiner sur la vue
///(par soucis d'optimisation, le draw des tiles individuelles est remplacer par le draw du niveau mais leur existence reste n�c�ssaire pour les collision)
///et pour finir il va afficher la vue dans la fen�tre
void RenderSystem::update(float dt)
{

    view->clear();

    for(int layer = -1; layer < 6; layer++)
    {
        for(Renderers::iterator it = renderers->begin(); it != renderers->cend(); it++)
        {

            Entity entity = it->first;
            RendererComponent& render = *(it->second);
            sf::Sprite& sprite = render.getSpriteRef();

            //saute l'entit� pour cette boucle
            if (render.getLayer() != layer)
            {
                continue;
            }

            //si le sprite n'a pas encore de texture, lui en assigne une
            if(!render.hasSpriteTextured()){
                asset->setSpriteTexture(sprite, render.getTextureName());
                sprite.setScale(render.getScale());
            }

            //si l'entit� a une position, applique cette position au sprite, sinon lui assigne la position (0, 0);
            if(positions->find(entity) != positions->cend())
            {
                sprite.setPosition(positions->at(entity)->getPosition());
            }else
            {
                sprite.setPosition(0.0, 0.0);
            }

            //dessinne le sprite
            if(layer >= 0){view->draw(sprite);}

        }
    }
    view->display();
}
