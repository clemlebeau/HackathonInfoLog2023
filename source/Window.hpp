/// @file Window.hpp
/// @brief Contient la classe Window
/// @author Clément Lebeau (clementlebeau13@gmail.com)
/// @author Mikaël Bureau (mikael.bureau00@gmail.com)

#pragma once

#include <SDL2/SDL.h>

/// @class Window
/// @brief Implémentation d'une SDL_Window en orienté objet
class Window
{
protected:
    SDL_Window *window; ///< Pointeur vers la fenêtre SDL

public:
    Window(const char *title, int x, int y, int width, int height, unsigned int flags)
    {
        window = SDL_CreateWindow(title, x, y, width, height, flags);
    }

    virtual ~Window()
    {
        SDL_DestroyWindow(window);
    }

    /// @brief Retourne l'identifiant de la fenêtre
    /// @return Identifiant de la fenêtre
    unsigned int getID()
    {
        return SDL_GetWindowID(window);
    }

    /// @brief Affiche les modification apportées au moteur de rendu
    virtual void refresh() = 0;

    /// @brief Gère les évènements de la fenêtre
    virtual void handleEvent() = 0;
    /// @brief Gère les mises à jour de la fenêtre
    /// @param deltaTime Intervalle de temps depuis la dernière frame (en secondes)
    virtual void handleUpdate(double deltaTime) = 0;
    /// @brief Gère l'affichage de la fenêtre
    virtual void handleDraw() = 0;
};