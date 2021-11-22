//
//
//
#include <ostream>

using std::ostream;
#ifndef DAST_PLAYER_H
#define DAST_PLAYER_H
namespace wet1_dast {
    class Player {
    private:
        int player_id;
        int level;
    public:
        Player(int player_id, int level);//

        ~Player() = default;

        Player(const Player &p) = delete;

        void setLevel(int level_to_set);// p->level_to_set=level_to_set.
        int getLevel() const;

        int getId() const;

        bool operator==(const Player &p1) const;

        friend bool operator==(const Player &p, int p_id);

        bool operator<=(const Player &p1) const;

        friend ostream &operator<<(ostream &os, const Player &p);

    };


}


#endif //DAST_PLAYER_H
