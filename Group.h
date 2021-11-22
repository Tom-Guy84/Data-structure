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
        Player *Highest_Player = nullptr;
        int Group_Id;
        AVLTree<Player *> players;
        int size = 0;


    public:
        explicit Group(int Group_id)=default;

        Player* Get_Highest_Player();

        ~Group() = default;

        Group(const Group &group) = delete;//todo
        void operator=(const Group &other) = delete;//todo
        bool operator==(const Group &group);

        bool operator==(int Other_Group_id);

        bool operator<=(const Group &group);//todo
        //group1<= group2 <=> GroupId1<=groupid2;

        bool operator<=(int Other_Group_id);//todo

        int GetSize();//todo

        void CombineGroups(const Group &g);//maybe not const but & for sure todo
        void AddPlayer(int id, int Level);//may be subjected to changes todo
        void RemovePlayer(int id);
    }


}
#endif //DAST_GROUP_H
