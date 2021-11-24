//
// Created by proje on 20/11/2021.
//

#ifndef DAST_GROUP_H
#define DAST_GROUP_H


#include "AVLTree.h"

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
         friend bool compareGroups(const Group& g1,const Group& g2);
         void CombineGroups(const Group &g);//maybe not const but & for sure todo
         void AddPlayer(int id, int Level);//may be subjected to changes todo
         void RemovePlayer(int id);
    };

//
}
#endif //DAST_GROUP_H
