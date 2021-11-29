
#include "Group.h"
#include "Player.h"

namespace wet1_dast {

    Player* Group::Get_Highest_Player() {
        {
            return this->Highest_Player;
        }
    }

    bool Group::operator==(const Group &group) const {
        return (this->Group_Id == group.Group_Id);
    }

    void CombineGroups(Group &g1, Group& g2)
    {
        if (g2.size == 0)
            return;
        combineTrees(g1.players_by_level, g2.players_by_level);
        combineTrees(g1.players_by_id, g2.players_by_id);
        if (!g1.Highest_Player)//Highest_player==nullptr
        {
            g1.Highest_Player = g2.Highest_Player;
        } else if (*(g1.Highest_Player) <= (*(g2.Highest_Player)))
            g1.Highest_Player = g2.Highest_Player;
        Player *players_level = g1.players_by_id.inorderOut();
        Player *players_id = g1.players_by_id.inorderOut();
        for(int i=0; i<g1.size; i++)
        {
            players_level[i].setGroup(&g1);
            players_id->setGroup(&g1);
        }
        g1.players_by_id.inorderInsert(players_id);
        g1.players_by_level.inorderInsert(players_level);
        delete players_level;
        delete players_id;
    }


    int Group::GetSize() const {
        return players_by_level.getSize(); // should be return Players(the tree)->size;
    }


    void Group::AddPlayer(Player& player) {
        //remember it should throw here in case of not good parameters, we want to catch it in PlayerManager.
        players_by_id.insert(player);
        Player* p_level = player.createPlayerByLevel();
        players_by_level.insert(*p_level);
        Player* p = players_by_level.find(*p_level); //making sure the variable isn't local.
        if (Highest_Player == nullptr) //if Highest_player doesn't exist,meaning no player exists in Group.{
        {
            Highest_Player = p;
        } else { //highest player!=nullptr. we then compare between the two
            Highest_Player = (*Highest_Player <= *p) ? p : Highest_Player;
        }
        correctAfterInsert(); //if the group is empty or not before.
    }

    Group::Group(int Group_id) : Group_Id(Group_id), players_by_id(),
                                 players_by_level(), size(0), Highest_Player(nullptr) ,next(nullptr), prev(nullptr) {
        if (Group_id <= 0) {
            throw;
        }
    }

    Group::Group() {
        Group_Id = 0;
        size = 0;
        Highest_Player = nullptr;
        next = nullptr;
        prev = nullptr;
    }

    bool Group::operator<=(const Group &other) const {
        return Group_Id < other.Group_Id;
    }

    Player* Group::findPlayer(int PlayerId) {
        Player p(PlayerId, 0, nullptr, true);
        return players_by_id.find(p);
    }

    Player* Group::removePlayer(Player *player) {
        Player player_by_level(player->getId(), player->getLevel(), this, false);
        Player* player_to_return = players_by_id.remove(*player);
        delete players_by_level.remove(player_by_level);
        if (*(Highest_Player) == *player)
        {
            Highest_Player = players_by_level.findClosestFromBelow(player_by_level);
        }
        correctAfterRemove();
        return player_to_return;
    }

    Group *Group::getNextGroup()
    {
        return next;
    }

    Group *Group::getPreviousGroup()
    {
        return prev;
    }

    void Group::correctAfterInsert()
    {
        if(prev)
        {
            if(!(*(prev->next) == *this)) //TODO ,we need to make sure prev->next is this.
                prev->next = this;
        }
        if(next)
        {
            if(!(*(next->prev) == *this))
                next->prev = this;
        }
    }


    void Group::correctAfterRemove()
    {
        if(!size) // if the group is now empty so need to make adjustment in the list of non-empty groups
        {
            if(prev)
            {
                prev->next = next;
            }
            if(next)
            {
                next->prev = prev;
            }
        }
    }

    void Group::setPrev(Group *prev_group)
    {
        prev = prev_group;
    }

    void Group::setNext(Group *next_group)
    {
        next = next_group;
    }

    void Group::increaseLevelToPlayer(Player &player, int levelIncrease)
    {
        Player* player_up = players_by_level.find(player);
        player_up->setLevel(levelIncrease);
        if(*Highest_Player <= *player_up)
            Highest_Player = player_up;
    }

    Player *Group::getPlayersByLevel()
    {
        return players_by_level.inorderOut();
    }

    Group::~Group()
    {
//        delete &players_by_level;
     //   delete &players_by_id;


    }

}

