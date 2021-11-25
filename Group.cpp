
#include "Group.h"
#include "Player.h"
#include "AVLTree.h"
namespace wet1_dast {

    Player *Group::Get_Highest_Player() {
        {
            return this->Highest_Player;
        }
    }

    bool Group::operator==(const Group &group) const {
        return (this->Group_Id == group.Group_Id);
    }

    void Group::CombineGroups( Group &g) {
        if (g.Highest_Player != nullptr && Highest_Player != nullptr) {
           combineTrees(this->players_by_level,g.players_by_level);
           combineTrees(this->players_by_id,g.players_by_id);
        } else {
            if (g.Highest_Player != nullptr)//Highest_player==nullptr
            {

            }
        }

    }

    int Group::GetSize() const {
        return players_by_level.getSize(); // should be return Players(the tree)->size;
    }

    //with add or Remove,essentially it goes like that
    //in add,WE ASSUME the player doesn't exist in the game!! (we'll have to check it later ofc in playermanager.)
    //in remove we assume the player IS IN this game.
    void Group::AddPlayer(int id, int level) {
        //remember it should throw here in case of not good parameters, we want to catch it in PlayerManager.
        Player p_id(id, level, this, true);
        players_by_id.insert(p_id);
        Player p_level(id, level, this, false);
        players_by_level.insert(p_level);
        //deduct about Highest_Player.
        if (Highest_Player == nullptr) //if Highest_player doesn't exist.{
        {
            Highest_Player = &p_level;
        }
        else {
            Highest_Player=(*Highest_Player<=p_level)? &p_level : Highest_Player;
        }
    }

    void Group::RemovePlayer(int id) {
        //try to remove player.
        Player p_id(id, 0, this, true);
        players_by_id.remove(p_id); //Remove player from players_by_id.
        Player p_level(id, 0, this, false);
        if (*(Highest_Player) == p_level) {
            Highest_Player = players_by_level.findClosest(p_level);
        }
        players_by_level.remove(p_level);
    }

    Group::Group(int Group_id) : Group_Id(Group_id), players_by_id(),
                                 players_by_level(), size(0), Highest_Player(nullptr) {
        if (Group_id <= 0) {
            throw;
        }
    }

    Group::Group() {
        Group_Id = 0;
        size = 0;
        Highest_Player = nullptr;

    }

    bool Group::operator<=(const Group &other) const {
        return Group_Id < other.Group_Id;
    }

    Player *Group::findPlayer(int PlayerId) {
        Player p(PlayerId, 0, nullptr, true);
        return players_by_id.find(p);
    }

    void Group::removePlayer(Player *player) {
        Player player_by_level(player->getId(), player->getLevel(), this, false);
        players_by_id.remove(*player);
        players_by_level.remove(player_by_level);
    }
}

