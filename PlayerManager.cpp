//
// Created by Tom Guy on 11/23/2021.
//

#include "PlayerManager.h"

namespace wet1_dast
{

    PlayerManager& PlayerManager::init()
    {
        auto* Manager = new PlayerManager();
        return *Manager;
    }
}