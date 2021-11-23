//
// Created by  on 21/11/2021.
//
#include "Group.h"
#include "Player.h"



namespace wet1_dast {

    Player *Group::Get_Highest_Player() {
        {
            return this->Highest_Player;
        }
    }

    bool Group::operator==(const Group &group) const {
        return (this->Group_Id == group.Group_Id);
    }

    bool Group::operator==(int Other_Group_id)  const {
        return (this->Group_Id == Other_Group_id);
    }

    bool Group::operator<=(const Group &group) const  {
        return (this->Group_Id <= group.Group_Id);
    }

    void Group::CombineGroups(const Group &g) {

    }

    int Group::GetSize() const{
        return size; // should be return Players(the tree)->size;
    }

    bool Group::operator<=(int Other_Group_id) const {
        return (this->Group_Id <= Other_Group_id);
    }

    //with add or Remove,essentially it goes like that
    //in add,WE ASSUME the player doesn't exist in the game!! (we'll have to check it later ofc in playermanager.)
    //in remove we assume the player IS IN this game.
    void Group::AddPlayer(int id, int level) {
        //remember it should throw here in case of not good parameters, we want to catch it in PlayerManager.
        Player p(id, level);
        players.insert(p);
    }
    void Group::RemovePlayer(int id) {

    }

     Group::Group(int Group_id):players(){
       if(Group_id<=0)
       {
         throw;
       }
       this->Group_Id=Group_id;
       size=0;
       this->Highest_Player=nullptr;
    }

    Group::Group()
    {
        Group_Id = 0;
        size = 0;
        Highest_Player = nullptr;
    }
}

