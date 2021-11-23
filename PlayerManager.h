//
// Created by proje on 20/11/2021.
//
#ifndef DAST_PLAYERMANAGER_H
#define DAST_PLAYERMANAGER_H

#include <iostream>
#include "Group.h"
#include "AVLTree.h"
namespace wet1_dast
{

    class PlayerManager
    {
        AVLTree<Group> Groups;
        Group PlayersManager;

        class Node
        {
            friend class PlayerManager;
            Node *next;
            Node *prev;
            Node *next_non_empty;
            Node *prev_non_empty;
            Group *group;
        };
        PlayerManager() = default;


        Node *non_empty_groups;

    public:
        typedef enum
        {
            ALLOCATION_ERROR, INVALID_INPUT, FAILURE, SUCCESS
        } StatusType;

        PlayerManager& init();

        StatusType AddGroup(int GroupId);

        StatusType AddPlayer(int PlayerId, int GroupId, int lever);

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