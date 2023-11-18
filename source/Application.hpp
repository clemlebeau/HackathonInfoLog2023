/// @file Application.hpp
/// @brief Fichier contenant la classe Application. Contient la boucle d'application (Évènements, Mises à jour, Affichage)
/// @author Clément Lebeau (clementlebeau13@gmail.com)
/// @author Mikaël Bureau (mikael.bureau00@gmail.com)

#pragma once

#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Event.hpp"
#include "Window.hpp"
#include "Timer.hpp"

/// @class Application
/// @brief Impose les trois étapes de la boucle d'application. Initialise SDL
class Application
{
private:
    static Application instance; ///< Seule instance de l'application (patron Singleton)
    std::map<unsigned int, Window *> windows; ///< Toutes les fenêtres présentes dans l'application (identifiées par leur UUID)
    Timer timer; ///< Chronomètre utilisé pour calculer le deltaTime

public:
    Application()
    {
        timer.reset();
        SDL_Init(SDL_INIT_VIDEO);
        IMG_Init(IMG_INIT_PNG);
        TTF_Init();
    }

    ~Application()
    {
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    /// @brief Retourne l'instance de l'application
    /// @return Référence à l'instance de l'application
    static Application &getInstance()
    {
        return instance;
    }

    /// @brief Démarre l'application
    void start()
    {
        // Application loop
        while (windows.size())
        {
            double deltaTime = timer.getElapsed();
            timer.reset();
            // if (deltaTime < 0.001)
            //     deltaTime = 0.001;

            // Handle events
            while (Event::poll())
            {
                switch (Event::getType())
                {
                case SDL_WINDOWEVENT:
                    switch (Event::getWindowEvent())
                    {
                    case SDL_WINDOWEVENT_CLOSE:
                        delete windows[Event::getWindowID()];
                        windows.erase(Event::getWindowID());
                        break;
                    }
                    break;
                
                case SDL_QUIT:
                    delete windows[Event::getWindowID()];
                    windows.erase(Event::getWindowID());
                    break;

                default:
                    if (windows.find(Event::getWindowID()) != windows.end())
                        windows[Event::getWindowID()]->handleEvent();
                    break;
                }
            }

            // Handle updates and graphics
            for (auto it : windows)
            {
                it.second->handleUpdate(deltaTime);
                it.second->handleDraw();
            }
        }
    }

    /// @brief Ajoute une fenêtre à l'application
    /// @param window Pointeur vers la fenêtre à ajouter
    void addWindow(Window *window)
    {
        windows[window->getID()] = window;
    }

    /// @brief Permet d'obtenir une fenêtre de l'application
    /// @param id Identificateur de la fenêtre à obtenir
    /// @return Fenêtre à obtenir
    Window* getWindow(unsigned int id) {
        return windows[id];
    }
};
Application Application::instance;