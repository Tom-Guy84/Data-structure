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
        Player *Highest_Player ;
        int Group_Id;
        AVLTree<Player> players_by_id;
        AVLTree<Player> players_by_level;
        int size ;
    public:
         explicit Group(int Group_id);
         Group();
        Player* Get_Highest_Player();
        ~Group() = default;
         Group(const Group &group) =delete;//todo
      //  Group& operator=(const Group &other) ;//todo
         bool operator==(const Group &group) const;
         int GetSize() const;//todo
         bool operator<=(const Group& other) const;
         void CombineGroups(const Group &g);//maybe not const but & for sure todo
         void AddPlayer(int id, int Level);//may be subjected to chanegs todo
         void RemovePlayer(int id);
         Player* findPlayer(int PlayerId);
         void removePlayer(Player* player);
    };

//
}
#endif //DAST_GROUP_H
