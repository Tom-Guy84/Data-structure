//
// Created by proje on 20/11/2021.
//
#include <iostream>
#include "Group.h"
#include "AVLTree.h"

#ifndef DAST_PLAYERMANAGER_H
#define DAST_PLAYERMANAGER_H

namespace wet1_dast
{

    class PlayerManager
    {
        PlayerManager() = default;
        AVLTree<Group> allGroups;
        AVLTree<Group> nonEmptyGroups;
        Group players;
    public:
        typedef enum
        {
            ALLOCATION_ERROR, INVALID_INPUT, FAILURE, SUCCESS
        } StatusType;

        PlayerManager* init();

        StatusType AddGroup(int GroupId);

        StatusType AddPlayer(int PlayerId, int GroupId, int level);

        StatusType RemovePlayer(int PlayerId);

        StatusType ReplaceGroup(int GroupId, int ReplacementId);

        StatusType IncreaseLevel(int PlayerId, int LevelIncrease);

        StatusType GetHighestLevel(int GroupId, int *PlayerId);

        StatusType GetAllPlayersByLevel(int GroupId, int **PlayerId, int numOfPlayers);

        StatusType GetGroupsHighestLevel(int numOfGroups, int **Players);

        void Quit();


    };
}
#endif //DAST_PLAYERMANAGER_H