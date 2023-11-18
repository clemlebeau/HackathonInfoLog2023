/// @file Timer.hpp
/// @brief Contient la classe Timer
/// @author Clément Lebeau (clementlebeau13@gmail.com)

#pragma once

#include <ctime>
#include <chrono>

/// @class Timer
/// @brief Chronomètre qui peut mesurer une intervalle de temps
class Timer
{
private:
    std::chrono::steady_clock::time_point startTime; /// Moment quand le chronomètre à été reset pour la dernière fois

public:
    Timer()
    {
        startTime = std::chrono::steady_clock::now();
    }

    /// @brief Retourne le temps écoulé depuis le dernier reset
    /// @return Temps écoulé en secondes (avec une précision aux nanosecondes)
    double getElapsed()
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - startTime).count() / 1000000000.0;
    }

    /// @brief Reset le chronomètre
    void reset()
    {
        startTime = std::chrono::steady_clock::now();
    }
};