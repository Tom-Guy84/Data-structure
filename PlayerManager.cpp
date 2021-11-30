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
            Group g(GroupId);
            if(All_Groups.find(g))
                return FAILURE;
            Group* new_group = new Group(GroupId);
            All_Groups.insert(*new_group); //insert the group
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
        try {
            Group g(GroupId);
            Group *playersGroup = All_Groups.find(g);
            Player *player_exist = players.findPlayer(PlayerId);
            if (!playersGroup || player_exist) {
                return FAILURE;
            }
            if(playersGroup->GetSize() == 0)
            {
                Group* copy_of_group = new Group(GroupId);
                copy_of_group->setCopy(playersGroup);
                playersGroup->setCopy(copy_of_group);
                Non_Empty_Groups.insert(*copy_of_group);
            }
            Player *player_in_players = new Player(PlayerId, level, playersGroup, true, nullptr);
            Player *player_in_group = new Player(PlayerId, level, playersGroup, true, player_in_players);
            player_in_players->SetPlayerPointer(player_in_group);
            players.AddPlayer(*player_in_players);
            playersGroup->AddPlayer(*player_in_group);
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
        Group* players_group = player->getGroup();
        players.removePlayer(player);
        Player *player_in_group = players_group->findPlayer(PlayerId);
        players_group->removePlayer(player_in_group);
        if(players_group->GetSize() == 0)
        {
            Non_Empty_Groups.remove(*(players_group));
        }
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
            Group* g_to_delete = All_Groups.find(group_delete);
            Group group_replace(ReplacementId);
            Group* g_to_replace = All_Groups.find(group_replace);
            if(!g_to_delete ||!g_to_replace)
                return FAILURE;
            CombineGroups(g_to_delete, g_to_replace);
            if(group_delete.GetSize() > 0)
            {
                Non_Empty_Groups.remove(group_delete);
            }
            All_Groups.remove(group_delete);
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
            Group* group = All_Groups.find(g);
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
                if (players.GetSize() == 0)
                {
                    *numOfPlayers = 0;
                    *Players = NULL;
                    return SUCCESS;
                }
                return GetPlayersByLevel(&players, Players, numOfPlayers);
            }
            Group g(GroupId);
            Group* group = All_Groups.find(g);
            if(!group)
                return FAILURE;
            if(group->GetSize() == 0)
            {
                *numOfPlayers = 0;
                Players = NULL;
                return SUCCESS;
            }
            return GetPlayersByLevel(group, Players, numOfPlayers);
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

        }

        catch (std::exception&e)
        {
        }
        return ALLOCATION_ERROR;
    }

    void Quit(PlayerManager *DS) {
        delete DS;
    }

    StatusType PlayerManager::GetPlayersByLevel(Group *group, int **Players, int *numOfPlayers)
    {
        Player** players_of_the_group = group->getPlayersByLevel();
        int *group_players = (int*)malloc(sizeof(int)*group->GetSize());
        if(!group_players)
        {
            delete players_of_the_group;
            return FAILURE;
        }
        for(int i = 0; i < group->GetSize(); i++)
        {
            group_players[i] = players_of_the_group[group->GetSize() -i -1]->getId();
        }
        *Players = group_players;
        delete players_of_the_group;
        *numOfPlayers = group->GetSize();
        return SUCCESS;
    }


}