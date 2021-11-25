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
            if(playersGroup->GetSize() == 1)
            {
                nonEmptyGroups.insert(*playersGroup);
            }
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

    PlayerManager::StatusType PlayerManager::RemovePlayer(int PlayerId)
    {
        if(PlayerId <= 0)
        {
            return INVALID_INPUT;
        }
        Player *player = players.findPlayer(PlayerId);
        if(!player)
        {
            return FAILURE;
        }
        player->group->removePlayer(player);
        if(player->group->GetSize() == 0)
        {
            //need to figure out what todo if the group is now empty because remove is not good in complexity
        }
        players.removePlayer(player);
        return SUCCESS;
    }

    PlayerManager::StatusType PlayerManager::ReplaceGroup(int GroupId, int ReplacementId)
    {
        if(GroupId == ReplacementId || GroupId <= 0 || ReplacementId <= 0)
        {
            return INVALID_INPUT;
        }
        try
        {
            Group g_to_delete =
        }

    }
}