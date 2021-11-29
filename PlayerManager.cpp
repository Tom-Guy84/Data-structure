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

    StatusType PlayerManager::AddGroup(int GroupId)
    {
        if(GroupId <= 0)
        {
            return INVALID_INPUT;
        }
        try
        {
            Group* new_group = new Group(GroupId); //
            Groups.insert(*new_group); //insert the group
            Group* closest = Groups.findClosestFromBelow(*new_group);//find the closest
            if(!closest) //add- he needs to have players. if he exists and he doesnt havae players ,his previous is my previous
                //if
            {
                new_group->setPrev(nullptr);
                Group* closest_from_above = Groups.findClosestFromAbove(*new_group); //if he has players he's the next , if not,he's next is the next.
                if(closest_from_above) {
                    if(closest_from_above->GetSize()==0) {
                        new_group->setNext(closest_from_above->getNextGroup());
                    }
                    else
                    {
                        new_group->setNext(closest_from_above);
                    }
                }
                else {
                    new_group->setNext(nullptr);
                }
            }
            else
            {
                (closest->GetSize() == 0) ? new_group->setPrev(closest->getPreviousGroup()) : new_group->setPrev(closest);
                new_group->setNext(closest->getNextGroup());
            }
            return SUCCESS;
        }
        catch (const AVLTree<Group>::ItemExist& exist)
        {
            return FAILURE;
        }
        catch (const std::exception& e)
        {
            return ALLOCATION_ERROR;
        }
    }

    StatusType PlayerManager::AddPlayer(int PlayerId, int GroupId, int level)
    {
        if(PlayerId <= 0 || GroupId <= 0 || level < 0)
        {
            return INVALID_INPUT;
        }
        try
        {
            Group g(GroupId);
            Group* playersGroup = Groups.find(g);
            if(!playersGroup)
            {
                return FAILURE;
            }
            Player* player =new Player(PlayerId, level, playersGroup, true);
            players.AddPlayer(*player);
            playersGroup->AddPlayer(*player);
        }
        catch (const AVLTree<Player>::ItemExist& e)
        {
            return FAILURE;
        }
        catch (const AVLTree<Group>::ItemNotExist& e)
        {
            return FAILURE;
        }
        return SUCCESS;
    }

    StatusType PlayerManager::RemovePlayer(int PlayerId)
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
        (player->getGroup)()->removePlayer(player); // ignore the player that returns from the function because its get
                                               // deleted in the next line
        delete players.removePlayer(player);
        return SUCCESS;
    }

    StatusType PlayerManager::ReplaceGroup(int GroupId, int ReplacementId)
    {
        if(GroupId == ReplacementId || GroupId <= 0 || ReplacementId <= 0)
        {
            return INVALID_INPUT;
        }
        try
        {
            Group group_delete(GroupId);
            Group* g_to_delete = Groups.find(group_delete);
            Group group_replace(ReplacementId);
            Group* g_to_replace = Groups.find(group_replace);
            if(!g_to_delete ||!g_to_replace)
                return FAILURE;
            CombineGroups(*g_to_replace, *g_to_delete);
            group_delete.correctAfterRemove();
            delete Groups.remove(group_delete);
        }
        catch (std::exception& e)
        {
            return ALLOCATION_ERROR;
        }
        return SUCCESS;
    }

    StatusType PlayerManager::IncreaseLevel(int PlayerId, int LevelIncrease)
    {
        if(PlayerId <= 0 || LevelIncrease <= 0)
            return INVALID_INPUT;
        try
        {
            Player* player = players.findPlayer(PlayerId);
            if(!player)
                return FAILURE;
            player->setLevel(LevelIncrease);
            player->getGroup()->increaseLevelToPlayer(*player, LevelIncrease);
            players.increaseLevelToPlayer(*player, LevelIncrease);
            return SUCCESS;
        }
        catch (std::exception& e)
        {
            return ALLOCATION_ERROR;
        }
    }

    StatusType PlayerManager::GetHighestLevel(int GroupId, int *PlayerId)
    {
        if(GroupId == 0 || !PlayerId)
            return INVALID_INPUT;
        try
        {
            if(GroupId < 0)
            {
                (players.Get_Highest_Player() == nullptr)? *PlayerId = -1 :
                        *PlayerId = players.Get_Highest_Player()->getId();
                return SUCCESS;
            }
            Group g(GroupId);
            Group* group = Groups.find(g);
            if(!group)
                return FAILURE;
            (group->Get_Highest_Player() == nullptr)? *PlayerId = -1 :
                    *PlayerId = group->Get_Highest_Player()->getId();
            return SUCCESS;
        }
        catch (std::exception& e)
        {
            return ALLOCATION_ERROR;
        }
    }

    StatusType PlayerManager::GetAllPlayersByLevel(int GroupId, int **Players, int *numOfPlayers)
    {
        if (GroupId == 0 || !Players || !numOfPlayers)
            return INVALID_INPUT;
        try
        {
            if(GroupId < 0)
            {
                if(players.GetSize() == 0)
                {
                    *numOfPlayers = 0;
                    *Players = NULL;
                    return SUCCESS;
                }
                Group g(GroupId);
                Group* group = Groups.find(g);
                if(!group)
                    return FAILURE;
                if(group->GetSize() == 0)
                {
                    *numOfPlayers = 0;
                    Players = NULL;
                    return SUCCESS;
                }
                Player* players_of_the_group = group->getPlayersByLevel();
                int *group_players = (int*)malloc(sizeof(int)*group->GetSize());
                if(!group_players)
                {
                    delete players_of_the_group;
                    return FAILURE;
                }
                for(int i = 0; i < group->GetSize(); i++)
                {
                    group_players[i] = players_of_the_group[group->GetSize() -i -1].getId();
                }
                *Players = group_players;
                delete players_of_the_group;
                return SUCCESS;
            }
        }
        catch (std::exception* e)
        {
        }
        return ALLOCATION_ERROR;
    }

    StatusType PlayerManager::GetGroupsHighestLevel(int numOfGroups, int **Players)
    {
        if(numOfGroups < 1 || !Players)
            return INVALID_INPUT;
        try
        {
            int* highest_players = (int*)malloc(sizeof(int)*numOfGroups);
            if(!highest_players)
                return ALLOCATION_ERROR;
            Group* group = Groups.GetLowesValue();
            int count;
            for(count = 0; count < numOfGroups && group; count++)
            {
                highest_players[count] = group->Get_Highest_Player()->getId();
                group = group->getNextGroup();
            }
            if(!group && count < numOfGroups)
            {
                free(highest_players);
                return FAILURE;
            }
            *Players = highest_players;
            return SUCCESS;
        }

        catch (std::exception&e)
        {
        }
        return ALLOCATION_ERROR;
    }

    void PlayerManager::Quit()
    {
        delete &Groups;
        delete &players;
    }
}