///@file Observable.hpp
///@brief Gère les observateurs et les notifies
///@author Louis-Philippe Dalmont (lpdalmont@hotmail.com)

#pragma once

#include "Observer.hpp"
#include <list>

///@class Observable 
///@brief Gère les observateurs et les notifies

class Observable{

	private:
		std::list <Observer*> observers; ///< Liste d'observateurs

	public:
        /// @brief Ajoute un observateur à la liste observers
        /// @param observer Prend en paramètre un observateur de type Observer pointeur
        void subscribe(Observer* observer){
			observers.push_back(observer);
		
        }
		///@brief Enlève un observateur à la liste observers
		///@param observer Prend en paramètre un observateur de type Observer pointeur
		void unsubscribe(Observer* observer){
			observers.remove(observer);
		}
		/// @brief Notifie chaque observateur inscrit à la liste
		void notify(){
			for (auto it : observers){
				it->notification();
			}

		}
		
};