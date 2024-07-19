//
// Created by OMEN on 21-05-2024.
//

#ifndef LUDO_GAME_GAME_H
#define LUDO_GAME_GAME_H
#include "Player.h"
#include <vector>

class Game {
private:
    std::vector<Player> players;
public:
    bool addPlayer(const Player &player){
        if(players.size() >= 4){
            return false; // Cannot add more than 4 players
        }
        players.push_back(player);
        return true;
    }
    bool isPlayable() const{
        return players.size()>=2;
    }

};


#endif //LUDO_GAME_GAME_H
