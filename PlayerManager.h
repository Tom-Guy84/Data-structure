//
// Created by proje on 20/11/2021.
//
#ifndef DAST_PLAYERMANAGER_H
#define DAST_PLAYERMANAGER_H

#include <iostream>
#include "Group.h"
#include "AVLTree.h"
#include <stdbool.h>
namespace wet1_dast
{

    class PlayerManager
    {
        class Node
        {
            friend class PlayerManager;
            Node *next;
            Node *prev;
            Node *next_non_empty;
            Node *prev_non_empty;
            Group* group;
            Node() = default;
        public:
            explicit Node(Group* group): group(group), next(nullptr), prev(nullptr), next_non_empty(nullptr),
                                                                                     prev_non_empty(nullptr){}
            ~Node() = default;
            bool operator==(const Node& other)
            {
                return *group == *(other.group);
            }
            bool operator<=(const Node& other)
            {
                return *group<=*(other.group);
            }
            bool operator>=(const Node& other)
            {
                return *group>=*(other.group);
            }
        };
        PlayerManager()
        {
            non_empty_groups->next = tail;
            non_empty_groups->prev = nullptr;
            non_empty_groups->next_non_empty = tail;
            non_empty_groups->prev_non_empty = nullptr;
            tail->next = nullptr;
            tail->prev = non_empty_groups;
            tail->next_non_empty = nullptr;
            tail->prev_non_empty = non_empty_groups;
        };
        Node *non_empty_groups;
        Node* tail;
        AVLTree<Node> Groups;
        Group PlayersManager;

        void insertInLocation(Node* first, Node* second);
    public:
        typedef enum
        {
            ALLOCATION_ERROR, INVALID_INPUT, FAILURE, SUCCESS
        } StatusType;

        PlayerManager* init();

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