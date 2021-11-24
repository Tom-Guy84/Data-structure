#include <iostream>
#include "Player.h"
#include <ostream>

namespace wet1_dast {
    Player::Player(int player_id, int level) {  //tested
        if (player_id > 0 && level >= 0) {
            this->player_id = player_id;
            this->level = level;
        } else {
            throw InvalidIdentifiers();
        }
    }

    void Player::setLevel(int level_to_set) {
        this->level = level_to_set; //tested
    }

    int Player::getLevel() const{
        return this->level; //tested
    }

    bool Player::operator==(const Player &p1) const{ //tested
        return (player_id == p1.player_id);
    }



    bool Player::operator<=(const Player &p1) const { //this->level<p1.level ||//comparebylevel
        return (this->level <= p1.getLevel()) || (this->level == p1.getLevel() && this->getId() >= p1.getId());
    }
//    bool Player::operator<=(const Player &p1) const { //this->level<p1.level ||//comparebyid
//        return p1.player_id<=p2.player_id;
//    }



    int Player::getId() const {
        return this->player_id;
    }

    std::ostream &operator<<(std::ostream &os, const Player &p) {
        os << "Player id: " << p.player_id<<std::endl;
        os << "Player level:" << p.level<<std::endl;
        return os;
    }
//lo tzarih
//    bool Player::operator<=(int PlayerID) const
//    {
//        return player_id <= PlayerID;
//    }
//
//    bool Player::operator==(int PlayerId)
//    {
//        return player_id == PlayerId;
//    }
//
//    bool Player::operator>=(int PlayerID) const //bool function
//    {
//        return player_id >= PlayerID;
//    }

}
