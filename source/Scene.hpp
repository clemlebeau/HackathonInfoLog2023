/// @file Scene.hpp
/// @brief Contient la classe Scene
/// @author Clément Lebeau (clementlebeau13@gmail.com)
/// @author Louis-philippe Dalmont (lpdalmont@hotmail.com)

#pragma once

#include <map>
#include <string>

#include "Component.hpp"
#include "Renderer.hpp"
#include "Observable.hpp"
#include "Observer.hpp"
#include "Cursor.hpp"

using namespace std;
/// @class Scene
/// @brief Représentation d'une scène

class Scene : public Observer
{

private:
    map<unsigned int, Observable*> eventTypes; ///< Contient tous les observables selon leur type d'événement
protected:
    map<std::string, Component *> components; /// Contient tous les components selon leur nom

public:
    Scene()
    {
        subscribeComponent(SDL_USEREVENT, this);
        subscribeComponent(SDL_MOUSEMOTION, Cursor::getInstance());
    }

    virtual ~Scene()
    {
        for (auto it : components)
            delete it.second;
        components.clear();

        for (auto it : eventTypes)
            delete it.second;
        eventTypes.clear();
    }

    virtual void setParams(int argc, ...) = 0;

    /// @brief Ajoute un nouveau type d'événement pouvant être observé
    /// @param eventType Prend en paramètre un type d'événement
    void addEventType(unsigned int eventType)
    {
        if (eventTypes.find(eventType) == eventTypes.end())
        {
            eventTypes[eventType] = new Observable();
        }
    }
    /// @brief Enlève un type d'événement pouvant être observé
    /// @param eventType Prend en paramètre un type d'événement
    void removeEventType(unsigned int eventType)
    {
        if (eventTypes.find(eventType) != eventTypes.end())
        {
            delete eventTypes[eventType];
            eventTypes.erase(eventType);
        }
    }
    /// @brief Lie un Observer* à un type d'événement
    /// @param eventType Le type d'événement à être observer par l'Observer*
    /// @param component L'Observer* qui observera le type d'événement
    void subscribeComponent(unsigned int eventType, Observer *component)
    {
        if (eventTypes.find(eventType) == eventTypes.end())
        {
            eventTypes[eventType] = new Observable();
            eventTypes[eventType]->subscribe(component);
        }
        else
        {
            eventTypes[eventType]->subscribe(component);
        }
    }
    /// @brief Enlève le type d'événement lié à l'Observer*
    /// @param eventType Le type d'événement qui ne sera pu observer par l'Observer*
    /// @param component L'Observer* qui n'observera plus le type d'événement
    void unsubscribeComponent(unsigned int eventType, Observer *component)
    {
        if (eventTypes.find(eventType) != eventTypes.end())
        {
            eventTypes[eventType]->unsubscribe(component);
        }
    }
    /// @brief Notifie les observateurs qui sont abonnés au type d'événement
    /// @param eventType Type d'événement à appeler
    void call(unsigned int eventType)
    {
        eventTypes[eventType]->notify();
    }

    /// @brief Ajoute un Component* à la scène
    /// @param component Component* à ajouter à la scène
    /// @param componentName Nom du Component* à ajouter
    /// @param overwrite Si ce paramètre est true et qu'il existe déjà un Component* du même nom, ce component sera écrasé
    /// @return Code d'erreur (0 si le Component* est ajouté, 1 s'il y a écrasement et -1 si l'ajout n'a pas pu être fait)
    char addComponent(Component *component, std::string componentName, bool overwrite = false)
    {
        if (components.find(componentName) == components.end())
        {
            components[componentName] = component;
            return 0;
        }
        else if (overwrite)
        {
            delete components[componentName];
            components[componentName] = component;
            return 1;
        }
        return -1;
    }

    /// @brief Retire un Component* à la scène
    /// @param componentName Nom du Component* à retirer
    void removeComponent(std::string componentName) {
        components.erase(componentName);
    }

    /// @brief Gère les évènements de la scène
    void handleEvent()
    {
        if (eventTypes.find(Event::getType()) != eventTypes.end())
        {
            eventTypes[Event::getType()]->notify();
        }
    }

    /// @brief Gère les évènements personnalisés de la scène
    virtual void notification() = 0;

    /// @brief Gère l'affichage sur le moteur de rendu
    /// @param renderer Moteur de rendu sur lequel afficher la scène
    virtual void handleDraw(Renderer *renderer) = 0;
    
    /// @brief Gère les mises à jour de la scène
    /// @param deltaTime Intervalle de temps depuis la dernière frame (en secondes)
    virtual void handleUpdate(double deltaTime) = 0;
};