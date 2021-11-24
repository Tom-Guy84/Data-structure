//
//
//


#ifndef DAST_PLAYER_H
#define DAST_PLAYER_H
#include <ostream>
#include "Group.h"
namespace wet1_dast {
    class Player {
    private:
        int player_id;
        int level;
        Group* group;
    public:
        Player(int player_id, int level);//
        ~Player() = default;
        Player(const Player &p) = delete;
        void setLevel(int level_to_set);// p->level_to_set=level_to_set.
        int getLevel() const;
        int getId() const;
        bool operator==(const Player &p1) const;
        bool operator==(int PlayerId);
        bool operator<=(const Player &p1) const;
        bool operator>=(const Player &p1) const;
        bool operator<=(int PlayerID) const;
        bool operator>=(int PlayerID) const;
        friend std::ostream &operator<<(std::ostream &os, const Player &p);
    class InvalidIdentifiers: public std::exception
    {
    public:
        const char* what() const noexcept override
        {
            return "Invalid input as level or id";
        }
    };
    };


}


#endif //DAST_PLAYER_H
