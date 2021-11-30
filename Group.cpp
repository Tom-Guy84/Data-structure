
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

    void CombineGroups( Group* to_delete,Group *to_insert) //to_delete is deleted
    {
        if (to_delete->size == 0)
            return;
        combineTrees(to_delete->players_by_level, to_insert->players_by_level);//combine two trees
        combineTrees(to_delete->players_by_id, to_insert->players_by_id);//combine two tress
        to_insert->size+=to_delete->size;
        if (!to_insert->Highest_Player)//Highest_player==nullptr
        {
            to_insert->Highest_Player = to_delete->Highest_Player;
        } else
        {
            Player* highest_insert = to_insert->Highest_Player->createPlayerByLevel();
            Player* highest_delete = to_delete->Highest_Player->createPlayerByLevel();
            if (*highest_insert <= *highest_delete)
            {
                to_insert->Highest_Player = to_delete->Highest_Player;
            }
            delete highest_insert;
            delete highest_delete;
        }
        to_insert->Highest_Player->setGroup(to_insert);
        Player **players_level = to_insert->players_by_level.inorderOut();
        Player **players_id = to_insert->players_by_id.inorderOut();
        for(int i=0; i < to_insert->size; i++)
        {
            players_id[i]->setGroup(to_insert);
            players_id[i]->getCopy()->setGroup(to_insert);
        }
        to_insert->players_by_id.inorderInsert(players_id ,to_insert->size+to_delete->size);
        to_insert->players_by_level.inorderInsert(players_level,to_insert->size+to_delete->size);
        delete[] players_level;
        delete[] players_id;
        to_delete->size = 0;
    }


    int Group::GetSize() const {
        return players_by_level.getSize(); // should be return Players(the tree)->size;
    }


    bool Group::AddPlayer(Player& player) {
        //remember it should throw here in case of not good parameters, we want to catch it in PlayerManager.
        players_by_id.insert(player);
        Player* p_level = player.createPlayerByLevel();
        players_by_level.insert(*p_level);
        if (Highest_Player == nullptr) //if Highest_player doesn't exist,meaning no player exists in Group.{
        {
            Highest_Player = &player;
        } else
        { //highest player!=nullptr. we then compare between the two
            Player* highest = Highest_Player->createPlayerByLevel();
            (*highest <= *p_level) ?Highest_Player = &player :Highest_Player = Highest_Player;
            delete highest;
        }
        size++;
        return correctAfterInsert(); //if the group is empty or not before.
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
        Player p(PlayerId, 0, nullptr, true, nullptr);
        return players_by_id.find(p);
    }

    void Group::removePlayer(Player *player) {
        Player* player_by_level = player->createPlayerByLevel();
        Player* highest = Highest_Player->createPlayerByLevel();
        players_by_level.remove(*player_by_level);
        players_by_id.remove(*player);
        if (*highest == *player_by_level)
        {
            Player* new_highest = players_by_level.findClosestFromBelow(*player_by_level);
            if(!new_highest)
            {
                Highest_Player = nullptr;
            }
            else
            {
                Highest_Player = players_by_id.find(*new_highest);
            }
        }

        size--;
        correctAfterRemove();
        delete player_by_level;
        delete highest;
    }

    Group *Group::getNextGroup()
    {
        return next;
    }

    Group *Group::getPreviousGroup()
    {
        return prev;
    }

    bool Group::correctAfterInsert()
    {
        if(next)
        {

            next->prev = this;
        }
        if(prev)
        {
           
                prev->next = this;
            return false;
        }
        return true;

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
        prev = nullptr;
        next = nullptr;
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
        Player* new_copy_of_player = new Player(player_up->getId(), player_up->getLevel()
                                                , player_up->getGroup(), false,  player_up->getCopy());
        Player* highest = Highest_Player->createPlayerByLevel();
        players_by_level.remove(player);
        players_by_level.insert(*new_copy_of_player);
        players_by_id.find(player)->setLevel(levelIncrease);
        if(*highest <= *new_copy_of_player)
            Highest_Player = players_by_id.find(player);
        delete highest;
    }

    Player** Group::getPlayersByLevel()
    {
        return players_by_level.inorderOut();
    }

    Group::~Group()
    {
        Highest_Player = nullptr;
        prev = nullptr;
        next = nullptr;
    }

    void Group::makeEmpty()
    {
        auto** empty_values = new Player*[size];
        for(int i=0; i<size ; i++)
            empty_values[i] = nullptr;
        players_by_id.inorderInsert(empty_values, size);
        delete[] empty_values;
    }

}

