//
// Created by OMEN on 22-05-2024.
//

#ifndef LUDO_GAME_BOARD_H
#define LUDO_GAME_BOARD_H

#include <map>
#include <tuple>

class Board {
public:
    Board();
    int getQuadrant(int player_row, int player_col);
private:
    const int board_size = 15;
    int board[15][15];
    std::map<int, std::tuple<int, int, int, int>> quadrant_ranges;
};

#endif //LUDO_GAME_BOARD_H
