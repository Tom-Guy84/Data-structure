#include <iostream>
#include "Player.h"
#include <ostream>

namespace wet1_dast {
    Player::Player(int player_id, int level) {  //tested
        if (player_id > 0 && level >= 0) {
            this->player_id = player_id;
            this->level = level;
        } else {
            throw std::runtime_error("illegal values");
        }
    }

    void Player::setLevel(int level_to_set) {
        this->level = level_to_set; //tested
    }

    int Player::getLevel() const{
        return this->level; //tested
    }

    bool Player::operator==(const Player &p1) const{ //tested
        return (this->getLevel() == p1.getLevel() && this->getId() == p1.getId());
    }


    bool operator==(const Player &p, int p_id) { //tested
        return (p.getId() == p_id);
    }

    bool Player::operator<=(const Player &p1) { //this->level<p1.level ||
        return (this->level <= p1.getLevel()) || (this->level == p1.getLevel() && this->getId() >= p1.getId());
    }


    int Player::getId() const {
        return this->player_id;
    }

    ostream &operator<<(ostream &os, const Player &p) {
        os << "Player id: " << p.player_id<<std::endl;
        os << "Player level:" << p.level<<std::endl;
        return os;
    }

}


