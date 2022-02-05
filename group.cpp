
#include "group.h"
#include "player.h"

namespace wet2_dast {

    bool Group::operator==(const Group &group) const {
        return (this->Group_Id == group.Group_Id);
    }

    void merge(Group* to_delete,Group *to_insert) //to_delete is deleted
    {
        if (to_delete->size == 0)
            return;
        for(int i = 0; i < 201; i++)
        {
            to_insert->scores[i] += to_delete->scores[i];
        }
        combineTrees(to_delete->players_by_level, to_insert->players_by_level);//combine two trees
        combineTrees(to_delete->players_by_score, to_insert->players_by_score);//combine two tress
        to_insert->size += to_delete->size;
        Player **players_level = to_insert->players_by_level.inorderOut(to_insert->players_by_level.getSize());
        Player **players_id = to_insert->players_by_score.inorderOut(to_insert->players_by_score.getSize());
        for(int i=0; i < to_insert->players_by_score.getSize(); i++)
        {
            players_id[i]->setGroup(to_insert->Group_Id);
        }
        to_insert->players_by_score.inorderInsert(players_id);
        to_insert->players_by_level.inorderInsert(players_level);
        delete[] players_level;
        delete[] players_id;
        to_delete->size = 0;
        Union(to_insert->players, to_delete->players);
    }


    int Group::GetSize() const {
        return size; // should be return Players(the tree)->size;
    }


    void Group::AddPlayer(Player& player) {
        players.insert_object(&player, player.getId());
        scores[player.getScore()]++;
        size++;
    }

    Group::Group(int Group_id) : Group_Id(Group_id), players_by_score(),
                                 players_by_level(), size(0), players()  {
        if (Group_id < 0) {
            throw;
        }
        scores = new int[201];
        for(int i=0; i< 201; i++)
            scores[i] = 0;
    }

    Group::Group() {
        Group_Id = 0;
        size = 0;
        scores = new int[201];
        for(int i=0; i< 201; i++)
            scores[i] = 0;
    }

    bool Group::operator<=(const Group &other) const {
        return Group_Id < other.Group_Id;
    }

    Player* Group::findPlayer(int PlayerId){
        return players.find_object(PlayerId);
    }

    void Group::removePlayer(int player_id) {
        Player* player = players.find_object(player_id);
        if(!player)
            throw std::exception();
        size--;

        if(player->getLevel() == 0)
        {
            scores[player->getScore()]--;
            players.delete_object(player_id);

            return;
        }
        Player* player_by_level = player->createPlayerByLevel();
        players_by_level.remove(*player_by_level);
        players_by_score.remove(*player);
        players.delete_object(player_id);
        delete player_by_level;
    }

    void Group::increaseLevelToPlayer(int player_id, int levelIncrease)
    {
        Player* player = players.find_object(player_id);
        if(player->getLevel() == 0)
        {
            player->setLevel(levelIncrease);
            auto* player_by_score = new Player(*player);
            players_by_score.insert(*player_by_score);
            Player* player_by_level = player->createPlayerByLevel();
            players_by_level.insert(*player_by_level);
            scores[player->getScore()]--;
            return;
        }
        Player* player_by_level = player->createPlayerByLevel();//to find the player.
        players_by_level.remove(*player_by_level);
        player_by_level->setLevel(levelIncrease);
        players_by_level.insert(*player_by_level);
        players_by_score.remove(*player);
        player->setLevel(levelIncrease);
        auto* player_by_score = new Player(*player);
        players_by_score.insert(*player_by_score);
    }
//
//    Player** Group::getPlayersByLevel()
//    {
//        return players_by_level.inorderOut(players_by_level.getSize());
//    }

    void Group::increaseScoreToPlayer(int player_id, int scoreIncrease)
    {
        Player* player = players.find_object(player_id);
        if(!player)
            throw std::exception();
        int old_score = player->getScore();
        player->setScore(scoreIncrease);
        if(player->getLevel() == 0)
        {
            scores[player->getScore()]++;
            scores[old_score]--;
            return;
        }
        Player player_old(player_id, player->getLevel(), player->getGroup(), true, old_score);
        players_by_score.remove(player_old);
        auto* player_by_score = new Player(*player);
        players_by_score.insert(*player_by_score);
    }

    double Group::getPercentOfPlayersWithScoreInBounds(int score, int lowerLevel, int higherLevel) const
    {
        if(score <= 0 || score > 200)
            score = 1;
        if(lowerLevel <= 0)
        {
            lowerLevel = 0;
            int amount_level_zero = size - players_by_level.getSize();
            if(higherLevel == 0)
            {
                if(amount_level_zero == 0)
                    throw exceptions();
                return (100*(scores[score]/(double)amount_level_zero));
            }
            Player lower_player_score(0 ,1, Group_Id, true, score);
            Player higher_player_score(0, higherLevel + 1, Group_Id, true, score);
            Player lower_player_level(0, 1, Group_Id, false, score);
            Player higher_player_level(0, higherLevel +1, Group_Id, false, score);
            double total_players_in_bounds = players_by_level.between_to_places(lower_player_level, higher_player_level)
                    + amount_level_zero;
            if(total_players_in_bounds == 0)
                throw exceptions();
            double amount_wanted = players_by_score.between_to_places(lower_player_score, higher_player_score);
            amount_wanted += scores[score];
            return (100*amount_wanted/total_players_in_bounds);
        }
        Player lower_player_score(0 ,lowerLevel, Group_Id, true, score);
        Player higher_player_score(0, higherLevel + 1, Group_Id, true, score);
        Player lower_player_level(0, lowerLevel, Group_Id, false, score);
        Player higher_player_level(0, higherLevel +1, Group_Id, false, score);
        double total_players_in_bounds = players_by_level.between_to_places(lower_player_level, higher_player_level);
        if(total_players_in_bounds == 0)
            throw exceptions();
        return (100*((double)(players_by_score.between_to_places(lower_player_score, higher_player_score)))
                                                            /total_players_in_bounds);
    }

    double Group::averageHighestPlayerLevel(int wanted_number_of_players) const
    {
        if(wanted_number_of_players > players_by_level.getSize())
        {
            return ((players_by_level.getSize()*players_by_level.getAverage(players_by_level.getSize()))
                                                                     /(double)wanted_number_of_players);
        }
        return players_by_level.getAverage(wanted_number_of_players);
    }

    Group::~Group()
    {
        delete[] scores;
    }

} //namespace wet2_dast

