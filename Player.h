//
//
//


#ifndef DAST_PLAYER_H
#define DAST_PLAYER_H
#include <ostream>

#include "Group.h"
namespace wet1_dast {
    //ask noam about cyclic dependence.
    class Group;
    class Player {
    private:
        int player_id;
        int level;
        Group* group;
    public:
        Player(int player_id, int level, Group *group);//
        ~Player() = default;
        Player(const Player &p) = delete;

        void setLevel(int level_to_set);// p->level_to_set=level_to_set.
        int getLevel() const;
        int getId() const;
        void setGroup(Group* group);
        bool operator==(const Player &p1) const;
        friend bool comparePlayersByLevel_aux(const Player& p1,const Player& p2);
        friend bool comparePlayersById_aux(const Player& p1,const Player& p2);
        friend std::ostream &operator<<(std::ostream &os, const Player &p);
        class comparePlayersByLevel{
        public:
            bool operator()(const Player& p1,const Player& p2);
        };
        class comparePlayersById{
        public:
            bool operator()(const Player& p1, const Player& p2);
        };
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
