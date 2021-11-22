//
// Created by proje on 21/11/2021.
//
#include "Group.h"
#include <iostream>
#include "Player.h"
namespace wet1_dast {

    Player* Group::Get_Highest_Player() {
        {
            return this->Highest_Player;
        }
    }

    bool Group::operator==(const Group &group) {
        return (this->Group_Id==group.Group_Id);
    }

    bool Group::operator==(int Other_Group_id) {
        return (this->Group_Id==Other_Group_id);
    }

    bool Group::operator<=(const Group &group) {
        return (this->Group_Id<=group.Group_Id);
    }

    void Group::CombineGroups(const Group &g) {

    }

    int Group::GetSize() {
        return size; // should be return Players(the tree)->size;
    }

    bool Group::operator<=(int Other_Group_id) {
        return (this->Group_Id<=Other_Group_id);
    }
     //with add or Remove,essentialy it goes like that
     //in add,WE ASSUME the player doens't exist in the game!! (we'll have to check it later ofc in playermanager.)
     //in remove we assume the player IS IN this game.
    void Group::AddPlayer(int id, int Level) {

    }

    void Group::RemovePlayer(int id) {

    }


}

