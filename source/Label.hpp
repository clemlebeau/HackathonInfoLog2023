/// @file Label.hpp
/// @brief Contient la classe Label
/// @author Clément Lebeau (clementlebeau13@gmail.com)

#pragma once

#include "Component.hpp"
#include "Renderer.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/// @brief Un label peut afficher du texte à l'écran avec une certaine couleur
/// @class Label
class Label : public Component
{
private:
    TTF_Font *font;       /// Police de caractère du texte
    SDL_Color color;      /// Couleur du texte
    SDL_Surface *surface; /// Surface qui est modifiée à chaque changement de texte
    SDL_Texture* texture; ///< Pointeur de la texture du label qui peut être affichée

public:
    Label(TTF_Font *font, SDL_Color color, int x, int y, std::string text = "") : Component(x, y)
    {
        this->font = font;
        this->color = color;
        this->surface = TTF_RenderText_Blended(this->font, text.c_str(), color);
        this->texture = nullptr;
        rectangle.w = surface->w;
        rectangle.h = surface->h;
    }

    virtual ~Label()
    {
        if (texture)
            SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
    }

    /// @brief Change le texte du Label
    /// @param text Texte à afficher
    void setText(std::string text)
    {
        SDL_FreeSurface(surface);
        surface = TTF_RenderText_Blended(font, text.c_str(), color);
    }

    /// @brief Affichage du Label
    /// @param renderer Le moteur de rendu sur lequel afficher le Label
    void draw(Renderer *renderer)
    {
        if (texture)
            SDL_DestroyTexture(texture);
        texture = renderer->createTextureFromSurface(surface);
        SDL_QueryTexture(texture, nullptr, nullptr, &rectangle.w, &rectangle.h);
        renderer->copy(texture, nullptr, &rectangle);
    }

    virtual void update(double deltaTime) {}
    void notification() {}
};