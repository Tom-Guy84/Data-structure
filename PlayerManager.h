//
// Created by proje on 20/11/2021.
//
#include <iostream>
#include "Group.h"
#include "AVLTree.h"
#include "Player.h"
#include "library1.h"

#ifndef DAST_PLAYERMANAGER_H
#define DAST_PLAYERMANAGER_H

namespace wet1_dast
{

    class PlayerManager
    {
        AVLTree<Group> Groups;
        Group players;
        StatusType GetPlayersByLevel(Group* group, int** Players, int* numOfPlayers);
    public:
        PlayerManager() = default;

        PlayerManager* init();

        StatusType AddGroup(int GroupId);

        StatusType AddPlayer(int PlayerId, int GroupId, int level);

        StatusType RemovePlayer(int PlayerId);

        StatusType ReplaceGroup(int GroupId, int ReplacementId);

        StatusType IncreaseLevel(int PlayerId, int LevelIncrease);

        StatusType GetHighestLevel(int GroupId, int *PlayerId);

        StatusType GetAllPlayersByLevel(int GroupId, int **Players, int* numOfPlayers);

        StatusType GetGroupsHighestLevel(int numOfGroups, int **Players);

       friend void Quit(PlayerManager *DS);


    };
}
#endif //DAST_PLAYERMANAGER_H