//
// Created by proje on 20/11/2021.
//

#ifndef DAST_GROUP_H
#define DAST_GROUP_H

#include "Player.h"
#include "AVLTree.h"


namespace wet1_dast {
    class Group {
    private:
        Player *Highest_Player ;
        int Group_Id;
        AVLTree<Player> players;
        int size ;


    public:
         explicit Group(int Group_id);
         Group();

        Player* Get_Highest_Player();

        ~Group() = default;

        Group(const Group &group) =delete;//todo
        Group& operator=(const Group &other) ;//todo
        bool operator==(const Group &group) const;

        bool operator==(int Other_Group_id) const;

        bool operator<=(const Group &group) const;
        bool operator>=(const Group &group) const;

        //group1<= group2 <=> GroupId1<=groupid2;

        bool operator<=(int Other_Group_id) const;
        bool operator>=(int Other_Group_id) const;

        int GetSize() const;//todo

        void CombineGroups(const Group &g);//maybe not const but & for sure todo
        void AddPlayer(int id, int Level);//may be subjected to changes todo
        void RemovePlayer(int id);
    };


}
#endif //DAST_GROUP_H
