/// @file Cursor.hpp
/// @brief Contient la classe Cursor
/// @author Clément Lebeau (clementlebeau13@gmail.com)

#pragma once

#include <SDL2/SDL.h>

#include "Renderer.hpp"
#include "Observer.hpp"
#include "Event.hpp"
#include "RessourceManager.hpp"

/// @class Cursor
/// @brief Un curseur doit s'afficher à la position de la souris
class Cursor : public Observer
{
private:
    static Cursor instance;
    SDL_Texture *texture;
    SDL_Rect dstRect;

public:
    Cursor()
    {
        // Ne pas afficher le curseur par défaut
        SDL_ShowCursor(SDL_DISABLE); 
        texture = nullptr;
        dstRect = {0, 0, 0, 0};
    }

    ~Cursor() {}

    static Cursor *getInstance() { return &instance; }

    /// @brief Cette méthode est appellée quand un MouseMotion event est détecté
    void notification()
    {
        setTexture(RessourceManager::get<SDL_Texture*>("cursor"));
        dstRect.x = Event::getMouseMotionX();
        dstRect.y = Event::getMouseMotionY();
    }

    /// @brief Affichage du curseur s'il est dans la fenêtre
    /// @param renderer Moteur de rendu sur lequel afficher le curseur
    void draw(Renderer *renderer)
    {
        SDL_RendererInfo rendererInfo;
        renderer->getRendererInfo(&rendererInfo);

        if (texture && dstRect.x >= 0 && dstRect.x < rendererInfo.max_texture_width - dstRect.w && dstRect.y >= 0 && dstRect.y < rendererInfo.max_texture_height - dstRect.h)
            renderer->copy(texture, nullptr, &dstRect);
    }

    /// @brief Change la texture du curseur
    /// @param texture Texture désirée
    void setTexture(SDL_Texture *texture)
    {
        this->texture = texture;
        SDL_QueryTexture(texture, nullptr, nullptr, &dstRect.w, &dstRect.h);
    }
};
Cursor Cursor::instance;