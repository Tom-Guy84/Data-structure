//
// Created by Tom Guy on 11/23/2021.
//

#include "PlayerManager.h"

namespace wet1_dast
{

    PlayerManager* PlayerManager::init()
    {
        try
        {
            auto* Manager = new PlayerManager();
            return Manager;
        }
        catch (const std::exception& e)
        {
            return nullptr;
        }

    }

    PlayerManager::StatusType PlayerManager::AddGroup(int GroupId)
    {
        if(GroupId <= 0)
        {
            return INVALID_INPUT;
        }
        try
        {
            Group new_group(GroupId);
            allGroups.insert(new_group);
            return SUCCESS;
        }
        catch (const AVLTree<Group, compareGroups>::ItemExist& exist)
        {
            return FAILURE;
        }
        catch (const std::exception& e)
        {
            return ALLOCATION_ERROR;
        }
    }

    PlayerManager::StatusType PlayerManager::AddPlayer(int PlayerId, int GroupId, int level)
    {
        if(PlayerId <= 0 || GroupId <= 0 || level < 0)
        {
            return INVALID_INPUT;
        }
        try
        {
            Group g(GroupId);
            Group* playersGroup = allGroups.find(g);
            if(!playersGroup)
            {
                return FAILURE;
            }
            Player new_player(PlayerId, level, playersGroup);
            players.insert(new_player);
        }
        catch (const AVLTree<Player, comparePlayersById>::ItemExist& e)
        {
            return FAILURE;
        }
        catch (const AVLTree<Group, CompareGroupById>::ItemNotExist& e)
        {
            return FAILURE;
        }
        return ALLOCATION_ERROR;
    }
}