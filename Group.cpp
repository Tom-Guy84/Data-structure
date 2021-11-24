
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
    void Group::CombineGroups(const Group &g) {

    }
    int Group::GetSize() const{
        return size; // should be return Players(the tree)->size;
    }

    //with add or Remove,essentially it goes like that
    //in add,WE ASSUME the player doesn't exist in the game!! (we'll have to check it later ofc in playermanager.)
    //in remove we assume the player IS IN this game.
    void Group::AddPlayer(int id, int level) {
        //remember it should throw here in case of not good parameters, we want to catch it in PlayerManager.
        Player p(id, level, nullptr);
        players_by_id.insert(p);
        players_by_level.insert(p);
        if(comparePlayersByLevel_aux(*Highest_Player,p))//highestplayer<-
        {
            Highest_Player=&p;
        }
    }
    void Group::RemovePlayer(int id) {
        Player p(id,0,this);
        players_by_id.remove(p);
        players_by_level.remove(p);
        if(*(Highest_Player)==p)
        {
            Highest_Player=players_by_level.findClosest(p);
        }
    }

     Group::Group(int Group_id): Group_Id(Group_id),  players_by_id(Player::comparePlayersById),
                players_by_level(Player::comparePlayersByLevel), size(0), Highest_Player(nullptr){
       if(Group_id<=0)
       {
         throw;
       }
    }
    Group::Group():
    {
        Group_Id = 0;
        size = 0;
        players_by_level;
        players_by_id;
        Highest_Player = nullptr;

    }
    bool compareGroups(const Group &g1, const Group &g2) {
        return g1.Group_Id<g2.Group_Id;
    }
}

