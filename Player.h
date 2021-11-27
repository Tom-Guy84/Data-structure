//
//
//
#include <ostream>
#include "Group.h"

#ifndef DAST_PLAYER_H
#define DAST_PLAYER_H

namespace wet1_dast {

    class Group;
    class Player {
    private:
        int player_id;
        int level;
        Group* group;
        bool sort_by_id;
    public:
        Player(int player_id, int level, Group *group, bool sort_by_id);//
        ~Player();
        Player()=default;
        Player(const Player &p) = default;
        Player& operator=(const Player& p);
        Group* getGroup();
        void setLevel(int level_to_set);// p->level_to_set=level_to_set.
        int getLevel() const;
        int getId() const;
        void setGroup(Group* group);
        bool operator==(const Player &p1) const;
        bool operator<=(const Player& other) const;
        friend std::ostream &operator<<(std::ostream &os, const Player &p);
        Player* createPlayerByLevel() const;
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
