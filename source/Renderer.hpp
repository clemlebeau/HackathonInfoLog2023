/// @file Renderer.hpp
/// @brief Contient la classe Renderer
/// @author Clément Lebeau (clementlebeau13@gmail.com)
/// @author Mikaël Bureau (mikael.bureau00@gmail.com)

#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Window.hpp"

/// @class Renderer
/// @brief Implémentation orientée objet de SDL_Renderer
class Renderer : public Window
{
private:
    SDL_Renderer *renderer; /// Pointeur vers le moteur de rendu SDL

public:
    Renderer(const char *title = "", int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int width = 640, int height = 480, unsigned int windowFlags = 0, int index = -1, unsigned int rendererFlags = SDL_RENDERER_PRESENTVSYNC) : Window(title, x, y, width, height, windowFlags)
    {
        renderer = SDL_CreateRenderer(Window::window, index, rendererFlags);
    }

    virtual ~Renderer()
    {
        SDL_DestroyRenderer(renderer);
    }

    /// @brief Retourne un SDL_Texture* contenant une image en format .png
    /// @param fileName Emplacement du fichier où trouver l'image
    /// @return Une texture contenant l'image désirée
    SDL_Texture *loadTextureFromImage(std::string fileName)
    {
        return IMG_LoadTexture(renderer, fileName.c_str());
    }

    /// @brief Retourne un SDL_Texture* depuis un SDL_Surface*
    /// @param surface SDL_Surface* qu'on désire avoir en tant que SDL_Texture*
    /// @return SDL_Texture* surface transformée en texture
    SDL_Texture *createTextureFromSurface(SDL_Surface *surface)
    {
        return SDL_CreateTextureFromSurface(renderer, surface);
    }

    /// @brief Vide le moteur de rendu selon la couleur actuelle
    void clear()
    {
        SDL_RenderClear(renderer);
    }

    /// @brief Dessine un point à l'écran selon la couleur actuelle
    /// @param point SDL_Point& qu'on souhaite afficher
    void drawPoint(const SDL_Point &point)
    {
        SDL_RenderDrawPoint(renderer, point.x, point.y);
    }

    /// @brief Change la couleur d'affichage du moteur de rendu
    /// @param color Couleur qu'on veut utiliser
    void setDrawColor(const SDL_Color &color)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    }

    /// @brief Retourne la couleur de dessin actuelle
    /// @return Couleur actuelle
    SDL_Color getDrawColor()
    {
        SDL_Color color;
        SDL_GetRenderDrawColor(renderer, &color.r, &color.g, &color.b, &color.a);
        return color;
    }

    /// @brief Remplit le rectangle passé en paramètre d'une couleur
    /// @param dstRect Rectangle qui va être rempli d'une couleur
    /// @param color Couleur qu'on veut donner au rectangle
    void fillRectangle(const SDL_Rect &dstRect, const SDL_Color &color)
    {
        SDL_Color actualColor = getDrawColor();
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &dstRect);
        SDL_SetRenderDrawColor(renderer, actualColor.r, actualColor.g, actualColor.b, actualColor.a);
    }

    /// @brief Dessine une ligne de la couleur désirée
    /// @param color Couleur de laquelle dessiner la ligne
    /// @param x1 Abscisse du premier point
    /// @param y1 Ordonnée du premier point
    /// @param x2 Abscisse du deuxième point
    /// @param y2 Ordonnée du deuxième point
    void drawLine(const SDL_Color &color, int x1, int y1, int x2, int y2)
    {
        SDL_Color actualColor = getDrawColor();
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        SDL_SetRenderDrawColor(renderer, actualColor.r, actualColor.g, actualColor.b, actualColor.a);
    }

    /// @brief Affiche les modifications appliquées au moteur de rendu
    void refresh()
    {
        SDL_RenderPresent(renderer);
    }

    /// @brief Récuperer de l'information sur le moteur de rendu
    /// @param rendererInfo SDL_RendererInfo* qui sera rempli avec l'information du moteur de rendu actuel
    /// @return Code d'erreur (0 en temps normal)
    int getRendererInfo(SDL_RendererInfo *rendererInfo)
    {
        return SDL_GetRendererInfo(renderer, rendererInfo);
    }

    /// @brief Afficher une texture au moteur de rendu
    /// @param texture SDL_Texture* à afficher
    /// @param srcRect SDL_Rect* qui spécifie quelle partie de la texture on souhaite afficher (nullptr pour afficher la texture entière)
    /// @param dstRect SDL_Rect* qui spécifie sur quelle partie du moteur de rendu on souhaite afficher (nullptr pour afficher la texture sur le moteur de rendu au complet)
    void copy(SDL_Texture *texture, const SDL_Rect *srcRect, const SDL_Rect *dstRect)
    {
        SDL_RenderCopy(renderer, texture, srcRect, dstRect);
    }

    /// @brief Affiche une texture sur le moteur de rendu avec plus d'options
    /// @param texture Texture à afficher
    /// @param srcRect Partie de la texture à afficher (nullptr pour afficher la texture entière)
    /// @param dstRect Partie du moteur de rendu sur laquelle afficher la texture (nullptr pour le moteur de rendu entier)
    /// @param flip Détermine quelle action de SDL_RendererFlip devra être appliquée sur la texture
    /// @param angle Angle de rotation de la texture
    /// @param center Centre de rotation de la texture (centre de la texture si nullptr)
    void copyExtra(SDL_Texture *texture, const SDL_Rect *srcRect, const SDL_Rect *dstRect, const SDL_RendererFlip &flip, double angle = 0, const SDL_Point *center = nullptr)
    {
        SDL_RenderCopyEx(renderer, texture, srcRect, dstRect, angle, center, flip);
    }

    /// @brief Gestion des évènements
    virtual void handleEvent() = 0;
    /// @brief Gestion des mises à jour
    /// @param deltaTime Intervalle de temps depuis la dernière frame (en secondes)
    virtual void handleUpdate(double deltaTime) = 0;
    /// @brief Gestion de l'affichage
    virtual void handleDraw() = 0;
};