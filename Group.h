//
// Created by proje on 20/11/2021.
//

#include "AVLTree.h"

#ifndef DAST_GROUP_H
#define DAST_GROUP_H

namespace wet1_dast {
    class Player;
    class Group {
    private:
        Player* Highest_Player ;
        int Group_Id;
        AVLTree<Player> players_by_id;
        AVLTree<Player> players_by_level;
        int size ;
        Group* copy_non_empty;
    public:
         explicit Group(int Group_id);
         Group();
        Player* Get_Highest_Player();
        ~Group();
         Group(const Group &group) =delete;//todo
         Group& operator=(const Group &other)=delete ;//todo
         bool operator==(const Group &group) const;
         int GetSize() const;//todo
         bool operator<=(const Group& other) const;
         friend void CombineGroups(Group* to_delete,Group *to_insert);
         void AddPlayer(Player& player);
         Player* findPlayer(int PlayerId);
         void removePlayer(Player* player);
         void increaseLevelToPlayer(Player& player, int levelIncrease);
         Player ** getPlayersByLevel();
         void setCopy(Group* copy);
         Group* GetCopy();
    };


//
}
#endif //DAST_GROUP_H
