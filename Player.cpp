#include <iostream>
#include "Player.h"
#include <ostream>


namespace wet1_dast {

    Player::Player(int player_id, int level, Group *group=nullptr) : group(group) {  //tested
        if (player_id > 0 && level >= 0) {
            this->player_id = player_id;
            this->level = level;
        } else {
            throw InvalidIdentifiers();
        }
    }
    void Player::setLevel(int level_to_set) {
        level = level_to_set; //tested
    }
    int Player::getLevel() const{
        return level; //tested
    }
    bool Player::operator==(const Player &p1) const{ //tested
        return (player_id == p1.player_id);
    }
    int Player::getId() const {
        return player_id;
    }
    std::ostream &operator<<(std::ostream &os, const Player &p) {
        os << "Player id: " << p.player_id<<std::endl;
        os << "Player level:" << p.level<<std::endl;
        return os;
    }
    bool comparePlayersByLevel_aux(const Player &p1, const Player &p2) {
        return (p1.level <= p2.level) || (p1.level == p2.level && p1.player_id > p2.player_id);
    }

    bool comparePlayersById_aux(const Player& p1,const Player& p2) {
         return p1.player_id<p2.player_id;
    }

    bool Player::comparePlayersByLevel::operator()(const Player &p1, const Player &p2) {
        return comparePlayersByLevel_aux(p1,p2);
    }
    void Player::setGroup(Group* group_to_set) {
     group=group_to_set;
    }


    bool Player::comparePlayersById::operator()(const Player &p1, const Player &p2) {
        return comparePlayersById_aux(p1,p2);
    }
}
