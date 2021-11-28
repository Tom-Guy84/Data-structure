// im not extremist, just ambitious.

#include "PlayerManager.h"
#include "library1.h"

namespace  wet1_dast {

    void *Init() {
        PlayerManager* DS= new PlayerManager();
        if(!DS)
        {
            return NULL;
        }
        return (void*)DS;
    }
    StatusType AddGroup
}

StatusType AddGroup(void *DS, int GroupID) {
    if(!DS)
    {
        return ALLOCATION_ERROR;
    }
    return ((PlayerManager*)DS)->AddGroup(GroupID);
}

StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int Level) {
    if(!DS)
    {
        return ALLOCATION_ERROR;
    }
    return ((PlayerManager*)DS)->AddPlayer(PlayerID,GroupID,Level);
}

StatusType RemovePlayer(void *DS, int PlayerID) {
    if(!DS)
    {
        return ALLOCATION_ERROR;
    }
    return ((PlayerManager*)DS)->RemovePlayer(PlayerID);
}
StatusType ReplaceGroup(void *DS, int GroupID, int ReplacementID) {
    if(!DS)
    {
        return ALLOCATION_ERROR;
    }
    return ((PlayerManager*)DS)->ReplaceGroup(GroupID,ReplacementID);
}

StatusType IncreaseLevel(void *DS, int PlayerID, int LevelIncrease) {
    if(!DS)
    {
        return ALLOCATION_ERROR;
    }
    return ((PlayerManager*)DS)->(PlayerID,LevelIncrease);
}

StatusType GetHighestLevel(void *DS, int GroupID, int *PlayerID) {
    if(!DS)
    {
        return ALLOCATION_ERROR;
    }
    return ((PlayerManager*)DS)->GetHighestLevel(GroupID,PlayerID);
}

StatusType GetAllPlayersByLevel(void *DS, int GroupID, int **Players, int *numOfPlayers) {
    if(!DS)
    {
        return ALLOCATION_ERROR;
    }
    return ((PlayerManager*)DS)->GetAllPlayersByLevel(GroupID,Players,numOfPlayers);
}

StatusType GetGroupsHighestLevel(void *DS, int numOfGroups, int **Players) {
    if(!DS)
    {
        return ALLOCATION_ERROR;
    }
    return ((PlayerManager*)DS)->GetGroupsHIghestLevel(numOfGroups,Players);
}

void Quit(void **DS) {
    if(!DS)
    {
        return ;
    }
    ((PlayerManager*)DS)->Quit(DS);
}
