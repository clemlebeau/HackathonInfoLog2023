///@file Observer.hpp
///@brief Observateur du patron observateur
///@author Louis-Philippe Dalmont (lpdalmont@hotmail.com)

#pragma once

using namespace std;

///@class Observer
///@brief Reçoit une notification de la classe Observable

class Observer {
    public :
        /// @brief Oblige les classes dérivées d'utiliser la méthode notification()
        virtual void notification() = 0; 
};