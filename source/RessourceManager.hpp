/// @file RessourceManager.hpp
/// @brief Contient la classe RessourceManager
/// @author Mikaël Bureau (mikael.bureau00@gmail.com)

#pragma once

#include <map>
#include <string>

///\class RessourceManager
///\brief Conteneur des ressources(textures, fonts, etc.) et permet d'y accéder
class RessourceManager {
private:
    static std::map<std::string, void*> ressources; ///< Map de l'entièreté des ressources

public:
    /// @brief Permet d'enlever une ressource à la map de ressources
    /// @param key Clé qui identifie la ressource qu'on veut enlever
    static void remove(std::string key) {
        ressources.erase(key);
    }

    /// @brief Permet d'obtenir une ressource
    /// @tparam T indique le type de la ressource qu'on veut obtenir
    /// @param key Clé qui indique la ressource qu'on veut obtenir
    /// @return Retourne la ressource voulue
    template <typename T>
    static T get(std::string key) {
        return (T)ressources[key];
    }

    /// @brief Permet d'ajouter une ressource à la map de ressources
    /// @param key Clé qui identifie la ressource qu'on veut ajouter
    /// @param ressource Ressource à ajouter
    static void add(std::string key, void* ressource) {
        ressources[key] = ressource;
    }
};
std::map<std::string, void*> RessourceManager::ressources;