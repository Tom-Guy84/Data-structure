//
// Created by proje on 20/11/2021.
//
#include <iostream>
#include "Group.h"
#ifndef DAST_PLAYERMANAGER_H
#define DAST_PLAYERMANAGER_H
class PlayerManager
{
    AVLTree<Group*> EmptyGroups;
    AVLTree<Group*> NonEmptyGroups;
    Group PlayersManager;

};
#endif //DAST_PLAYERMANAGER_H