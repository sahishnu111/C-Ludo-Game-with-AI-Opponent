//
// Created by OMEN on 22-05-2024.
//

#include "Board.h"

Board::Board() {
    quadrant_ranges = {
            {1, {6, 0, 8, 5}}, // First quadrant range
            {2, {0, 6, 5, 8}}, // Second quadrant range
            {3, {6, 9, 14, 14}}, // Updated third quadrant range
            {4, {9, 5, 14, 8}}, // Updated fourth quadrant range
    };
}

int Board::getQuadrant(int player_row, int player_col) {
    for (const auto& [quadrant, range] : quadrant_ranges) {
        int start_row, start_col, end_row, end_col;
        std::tie(start_row, start_col, end_row, end_col) = range;
        if (player_row >= start_row && player_row <= end_row && player_col >= start_col && player_col <= end_col) {
            return quadrant;
        }
    }
    return -1; // Return -1 if the player's position is not in any quadrant
}