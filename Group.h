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
        AVLTree<Player> players_by_id;
        AVLTree<players> players_by_level;
        int size ;


    public:
         explicit Group(int Group_id);
         Group();

        Player* Get_Highest_Player();

        ~Group() = default;

        Group(const Group &group) =delete;//todo
//        Group& operator=(const Group &other) ;//todo
        bool operator==(const Group &group) const;

        bool operator==(const int Other_Group_id) const;

        bool operator<=(const Group &group) const;
        bool operator>=(const Group &group) const;

        //group1<= group2 <=> GroupId1<=groupid2;



        int GetSize() const;//todo
       friend bool CompareGroupById(const Group& g1,const Group& g2);
        void CombineGroups(const Group &g);//maybe not const but & for sure todo
        void AddPlayer(int id, int Level);//may be subjected to changes todo
        void RemovePlayer(int id);
    };
bool CompareGroupById(const Group& g1,const Group& g2){ //g1<=g2
    return g1.Group_Id<g2.Group_Id;
}
//
}
#endif //DAST_GROUP_H
