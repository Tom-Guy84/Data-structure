#include <iostream>
#include "Player.h"



namespace wet1_dast
{

    Player::Player(int player_id, int level, Group *group = nullptr, bool sort_by_id = true, Player* copy = nullptr) :
            group(group), sort_by_id(sort_by_id), copy_in_other_group(copy)
    {
        if (player_id > 0 && level >= 0)
        {
            this->player_id = player_id;
            this->level = level;
        } else
        {
            throw InvalidIdentifiers();
        }
    }

    void Player::setLevel(int level_to_set)
    {
        level += level_to_set; //tested
    }

    int Player::getLevel() const
    {
        return level; //tested
    }

    bool Player::operator==(const Player &p1) const
    { //tested

        return (player_id == p1.player_id);
    }

    int Player::getId() const
    {
        return player_id;
    }



    void Player::setGroup(Group *group_to_set)
    {
        group = group_to_set;
    }

    Player::~Player()
    {

        group = nullptr;
        copy_in_other_group = nullptr;
    }

    bool Player::operator<=(const Player &other) const
    {
        if (sort_by_id)
        {
            return player_id < other.player_id;
        }
        return (level < other.level || (level == other.level && player_id > other.player_id));
    }

    Group *Player::getGroup() {
        return this->group;
    }

    Player *Player::createPlayerByLevel() const
    {
        auto* playerByLevel  = new Player(player_id, level, group, false, nullptr);
        return playerByLevel;
    }

    Player &Player::operator=(const Player &p)
    {
        player_id = p.player_id;
        level = p.level;
        group = p.group;
        sort_by_id = p.sort_by_id;
        copy_in_other_group = p.copy_in_other_group;
        return *this;
    }

    void Player::SetPlayerPointer(Player *copy)
    {
        copy_in_other_group = copy;
    }

    Player *Player::getCopy()
    {
        return copy_in_other_group;
    }


}
