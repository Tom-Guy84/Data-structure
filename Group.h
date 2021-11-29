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
        Group* next; // will contain the next group with players
        Group* prev; // will contain the previous group with players
        void correctAfterInsert(); //for the list of non-empty groups
        //for the list of non-empty groups
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
         Player* removePlayer(Player* player);
         Group* getNextGroup();
         Group* getPreviousGroup();
         void setNext(Group* next_group);
         void setPrev(Group* prev_group);
         void increaseLevelToPlayer(Player& player, int levelIncrease); //increase level only in the playerByLevel tree
         Player ** getPlayersByLevel();

        void correctAfterRemove();
    };


//
}
#endif //DAST_GROUP_H
