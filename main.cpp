#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <random>
#include "Player.h"
#include "Game.h"
#include "Board.h"
#include "Computer.h"

Game game;
Board board;
int ROll;

std::vector<std::string> colors = {"Red", "Green", "Blue", "Yellow"};
std::vector<Player> players;
std::vector<std::vector<int>> safeSpots= {{6, 1}, {8, 3}, {2, 6}, {1, 8},{6,12},{8,13},{12,8},{13,6}};
std::vector<bool> players_at_home_pushed={false,false,false,false};
std::vector<int> Winner;

void PLAYER1();
void PLAYER2();
void PLAYER3();
void PLAYER4();
void ComputerPLAYER();
int Computer_Move(int PlayerID,int Roll);
int Computer_Attack(const std::vector<int>& Computer_set,const std::vector<int>& Enemy_set,int ROLL);
int ComputerSafeSpots(const std::vector<int>& Computer_set,int ROLL);
int ComputerAlmostHome(const std::vector<int>& Computer_set,int ROLL);
int getRandomIndex(const std::vector<bool>& playerPieces_set);
bool Computer_PLayer_attack(int Moved_piece,int PlayerID);


int generateRandomNumber();
int rollDice();
void updated_position_of_Starting_pieces(int NumberOfPlayers);
void Quadrant_moves(int player_row,int player_col, int ROLL,int PlayerID,int Quadrant,int Wanna_move_piece);
void Quad1(int player_row,int player_col, int ROLL,int PlayerID,int Wanna_move_piece);
void Quad2(int player_row,int player_col, int ROLL,int PlayerID,int Wanna_move_piece);
void Quad3(int player_row,int player_col, int ROLL,int PlayerID,int Wanna_move_piece);
void Quad4(int player_row,int player_col, int ROLL,int PlayerID,int Wanna_move_piece);
void Winner_check();


bool Player_Attack(int Moved_piece,int PlayerID);
bool stackPieces(int PlayerID);
int stackPieces_move(int PlayerID, int pieceIndex);
bool stackPieces_Quad(int PlayerID,int Wanna_move_piece);


void position_check(int PLayerID,int Wanna_move_piece){
        int player_row = players[PLayerID].playerPieces[Wanna_move_piece][0];
        int player_col = players[PLayerID].playerPieces[Wanna_move_piece][1];
        std::cout<<"UPDATED POSITION OF PLAYER PIECES\t"<<Wanna_move_piece<<"\n";
        std::cout<<"\tROW:"<<player_row<<"\tCOL:"<<player_col<<std::endl;
        std::cout<<"\n\n"<<std::endl;
};



int main() {
    int numberOfPlayers;
    std::cout << "\tLUDO GAME\t" << std::endl;
    std::cout << "\nHow many players are playing the game?\n" << std::endl;
    std::cout << "\nWRITE COMPUTER TO PLAY AGAINST COMPUTER\n" << std::endl;
    std::string user_computer_answer;
    std::cin >> user_computer_answer;
    for (char &c: user_computer_answer) {
        c = std::tolower(c);
    }
    if (user_computer_answer == "computer") {
        numberOfPlayers=2;
        Player computerPlayer(0, "Computer", "Red", false);
        game.addPlayer(computerPlayer);
        players.push_back(computerPlayer);
        Player player(1, "Player2", "Green", false);
        game.addPlayer(player);
        players.push_back(player);
        ROll=rollDice();
        if (game.isPlayable()) {
            std::cout << "\tGame is ready to play against computer\t" << std::endl;
        } else {
            std::cout << "Game is not playable. The number of players should be between 2 and 4." << std::endl;
            return -1;
        }
        updated_position_of_Starting_pieces(numberOfPlayers);
        std::cout<<players[0].playerPieces[0][1]<<std::endl;
        /////////////////////////////////////////////////////////////////////

        while(!((players[0].playerHome==4)&&(players[1].playerHome==4))){
            ComputerPLAYER();
            std::cout<< R"(\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\)" << std::endl;
            PLAYER2();

        }
    }

    else{
        std::cout << "\nHow many players are playing the game?\n" << std::endl;
        std::cin >> numberOfPlayers;
    if (numberOfPlayers < 2 || numberOfPlayers > 4) {
        std::cout << "\nInvalid number of players. The number of players should be between 2 and 4.\t" << std::endl;
        return 0;
    }
    for (int i = 0; i < numberOfPlayers; i++) {
        std::string name;
        std::string color = colors[i];
        std::cout << "Enter the name of player " << i + 1 << std::endl;
        std::cin >> name;
        Player player(i, name, color, false);
        game.addPlayer(player);
        players.push_back(player);
    }
    if (game.isPlayable()) {
        std::cout << "\tGame is ready to play.\t" << std::endl;
    } else {
        std::cout << "Game is not playable. The number of players should be between 2 and 4." << std::endl;
        return -1;
    }
    updated_position_of_Starting_pieces(numberOfPlayers);
    ///////////////////////////////////////////////
    switch (numberOfPlayers) {
        case 2: {
            players[2].playerHome = 4;
            players[3].playerHome = 4;
            break;
        }
        case 3: {
            players[3].playerHome = 4;
            break;
        }
        case 4: {
            break;
        }
        default: {
            std::cout << "GAME IS BROKEN" << std::endl;
        }
    }

    while (!((players[0].playerHome == 4) && (players[1].playerHome == 4) && (players[2].playerHome == 4) &&
             (players[3].playerHome == 4))) {

        PLAYER1();
        std::cout<< R"(\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\)" << std::endl;
        PLAYER2();
        std::cout<< R"(\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\)" << std::endl;
        PLAYER3();
        std::cout<< R"(\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\)" << std::endl;
        PLAYER4();
        std::cout<< R"(\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\)" << std::endl;


        for (int i = 0; i < 4; i++) {
            if (players[i].playerHome == 4) {
                if (!players_at_home_pushed[i]) {
                    Winner.push_back(i);
                    players_at_home_pushed[i] = true;
                }
            }

        }

    }

    std::cout << "\n\t\tGAME OVER\t\t\n" << std::endl;
    std::cout << "\n\t\tWINNER LIST\t\t\n" << std::endl;
    Winner_check();
}

    return 0;
}

void Winner_check(){
//loop through Winner vector
    for(int i=0;i<Winner.size();i++){
        std::cout<<i+1<<" WINNER: "<<players[Winner[i]].playerName<<std::endl;
    }

}

int generateRandomNumber() {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 6);

    return distrib(gen); // Generate a random number between 1 and 6
}

int rollDice() {
    return generateRandomNumber();
}

void updated_position_of_Starting_pieces(int NumberOfPlayers){
    switch (NumberOfPlayers) {
        case 2: {
            for (int i = 0; i < 4; i++) {//red
                players[0].playerPieces[i] = {6, 1};
            }
            for (int i = 0; i < 4; i++) {//green
                players[1].playerPieces[i] = {1, 8};
            }
            break;
        }
        case 3: {
            for (int i = 0; i < 4; i++) {//red
                players[0].playerPieces[i] = {6, 1};
            }
            for (int i = 0; i < 4; i++) {//green
                players[1].playerPieces[i] = {1, 8};
            }
            for (int i = 0; i < 4; i++) {//blue
                players[2].playerPieces[i] = {8, 13};
            }
            break;
        }
        case 4: {
            for (int i = 0; i < 4; i++) {//red
                players[0].playerPieces[i] = {6, 1};
            }
            for (int i = 0; i < 4; i++) {//green
                players[1].playerPieces[i] = {1, 8};
            }
            for (int i = 0; i < 4; i++) {//blue
                players[2].playerPieces[i] = {8, 13};
            }
            for (int i = 0; i < 4; i++) {//yellow
                players[3].playerPieces[i] = {13, 6};
            }
            break;
        }
        default:std::cout<<"Invalid number of players"<<std::endl;
    }
}


void Quadrant_moves(int player_row,int player_col, int ROLL,int PlayerID,int Quadrant,int Wanna_move_piece) {
    switch (Quadrant) {
        case 1:{
            Quad1(player_row, player_col, ROLL, PlayerID, Wanna_move_piece);
            break;
        }
        case 2:{
            Quad2(player_row, player_col, ROLL, PlayerID, Wanna_move_piece);
            break;
        }
        case 3:{
            Quad3(player_row, player_col, ROLL, PlayerID, Wanna_move_piece);
            break;
        }
        case 4:{
            Quad4(player_row, player_col, ROLL, PlayerID, Wanna_move_piece);
            break;
        }
        default:{
            std::cout << "Invalid Quadrant" << std::endl;
        }
    }
}





void Quad1(int player_row,int player_col, int ROLL,int PlayerID,int Wanna_move_piece) {
    if(player_col==0){
        if((player_row==6)&&(ROLL==6)){
            players[PlayerID].playerPieces[Wanna_move_piece]={5,6};
        }
        else {
            if (ROLL==1) {
                if(player_row==6){
                    players[PlayerID].playerPieces[Wanna_move_piece] = {6, 1};
                }
                else{
                    players[PlayerID].playerPieces[Wanna_move_piece] = {(player_row+ROLL), player_col};
                }
            } else {
                int NewROLL = ROLL - (player_row-6);
                players[PlayerID].playerPieces[Wanna_move_piece] = {6,0};
                players[PlayerID].playerPieces[Wanna_move_piece] = {6, (0+NewROLL)};
            }
        }
    }
    else if(player_row==8){
        int NewROLL= ROLL-(player_col);
        players[PlayerID].playerPieces[Wanna_move_piece] = {player_row, player_col-(player_col)};
        if(NewROLL<3){
            players[PlayerID].playerPieces[0] = {player_row-NewROLL, player_col};
        }
        else{
            int NewROLL1= NewROLL-(player_row-6);
            players[PlayerID].playerPieces[Wanna_move_piece] = {player_row-(player_row-6), player_col};
            players[PlayerID].playerPieces[Wanna_move_piece] = {player_row, player_col+NewROLL1};
        }
    }
    else{
        if(player_col+ROLL>=6){
            int NewROLL=ROLL-(5-player_col);
            NewROLL--;
            players[PlayerID].playerPieces[Wanna_move_piece] = {5,6};
            if(NewROLL>0){
                players[PlayerID].playerPieces[Wanna_move_piece] = {5-NewROLL,6};
            }
        }
        else{
            players[PlayerID].playerPieces[Wanna_move_piece] = {player_row,(player_col+ROLL)};
        }

    }

}

void Quad3(int player_row,int player_col, int ROLL,int PlayerID,int Wanna_move_piece){
    if(player_col==14){
        if((player_row==8)&&(ROLL==6)){
            players[PlayerID].playerPieces[Wanna_move_piece]={9,8};
        }
        else {
            if (ROLL==1) {
                if(player_row==8){
                    players[PlayerID].playerPieces[Wanna_move_piece] = {1, 8};
                }
                else{
                    players[PlayerID].playerPieces[Wanna_move_piece] = {(player_row+ROLL), player_col};
                }
            } else {
                int NewROLL = ROLL - (8 - player_row);
                players[PlayerID].playerPieces[Wanna_move_piece] = {8,14};
                players[PlayerID].playerPieces[Wanna_move_piece] = {8, (14-NewROLL)};
            }
        }
    }
    else if(player_row==8){
        if(player_col-ROLL<=8){
            int NewROLL=ROLL-(player_col-9);
            players[PlayerID].playerPieces[Wanna_move_piece] = {8,9};
            if(NewROLL>0){
                players[PlayerID].playerPieces[Wanna_move_piece] = {9,8};
                NewROLL--;
                if(NewROLL>0){
                    players[PlayerID].playerPieces[Wanna_move_piece] = {9+NewROLL,8};
                }
            }
        }
        else{
            players[PlayerID].playerPieces[Wanna_move_piece] = {player_row,player_col-ROLL};
        }
    }
    else{
        if(player_col+ROLL>14){
            int NewROLL=ROLL-(14-player_col);
            players[PlayerID].playerPieces[Wanna_move_piece] = {6,14};
            if(NewROLL>2){
                NewROLL=NewROLL-2;
                players[PlayerID].playerPieces[Wanna_move_piece] = {8,14};
                players[PlayerID].playerPieces[Wanna_move_piece] = {8,14-NewROLL};
            }
            else{
                players[PlayerID].playerPieces[Wanna_move_piece] = {(6+NewROLL),14};
            }
        }else{
            players[PlayerID].playerPieces[Wanna_move_piece] = {6,(player_col+ROLL)};
        }
    }

}

void Quad2(int player_row,int player_col, int ROLL,int PlayerID,int Wanna_move_piece) {
    if (player_row == 0) {
        if ((player_col == 8) && (ROLL == 6)) {
            players[PlayerID].playerPieces[Wanna_move_piece] = {6, 9};
        } else {
            if (ROLL==1) {
                if(player_col==8){
                    players[PlayerID].playerPieces[Wanna_move_piece] = {1, 8};
                }
                else{
                    players[PlayerID].playerPieces[Wanna_move_piece] = {player_row, player_col + ROLL};
                }
            } else {
                int NewROLL = ROLL - (8 - player_col);
                players[PlayerID].playerPieces[Wanna_move_piece] = {0,8};
                players[PlayerID].playerPieces[Wanna_move_piece] = {(0 + NewROLL), 8};
            }
        }
    }
    else if (player_col == 6) {
        if ((player_row - ROLL) < 0) {
            int NewROLL = ROLL - (player_row);
            players[PlayerID].playerPieces[Wanna_move_piece] = {0,6};
            if(NewROLL<3){
                players[PlayerID].playerPieces[Wanna_move_piece] = {0, (6+NewROLL)};
            }
            else{
                players[PlayerID].playerPieces[Wanna_move_piece] = {0, 8};
                NewROLL=NewROLL-2;
                players[PlayerID].playerPieces[Wanna_move_piece] = {NewROLL, 8};
            }
        } else {
            players[PlayerID].playerPieces[Wanna_move_piece] = {player_row - ROLL, player_col};
        }
    }
    else {
        if (player_row+ROLL >=6) {
            int NewROLL = ROLL - (5-player_row);
            players[PlayerID].playerPieces[Wanna_move_piece] = {6,9};
            NewROLL--;
            players[PlayerID].playerPieces[Wanna_move_piece] = {6, (9 + NewROLL)};
        } else {
            players[PlayerID].playerPieces[Wanna_move_piece] = {player_row + ROLL, player_col};
        }
    }

}

void Quad4(int player_row,int player_col, int ROLL,int PlayerID,int Wanna_move_piece){
    if (player_row == 14) {
        if ((player_col == 6) && (ROLL == 6)) {
            players[PlayerID].playerPieces[Wanna_move_piece] = {8, 5};
        } else {
            if (ROLL==1) {
                if(player_col==8){
                    players[PlayerID].playerPieces[Wanna_move_piece] = {1, 8};
                }
                else{
                    players[PlayerID].playerPieces[Wanna_move_piece] = {player_row, player_col + ROLL};
                }
            } else {
                int NewROLL = ROLL - (player_col-6);
                players[PlayerID].playerPieces[Wanna_move_piece] = {14,6};
                players[PlayerID].playerPieces[Wanna_move_piece] = {(14 - NewROLL), 6};
            }
        }
    }
    else if (player_col == 6) {
        if (player_row - ROLL < 9) {
            int NewROLL = ROLL - (player_row-9);
            players[PlayerID].playerPieces[Wanna_move_piece] = {8,5};
            NewROLL--;
            if(NewROLL>0){
                players[PlayerID].playerPieces[Wanna_move_piece] = {8, (5 - NewROLL)};
            }
        } else {
            players[PlayerID].playerPieces[Wanna_move_piece] = {player_row - ROLL, player_col};
        }
    }
    else {
        if (player_row+ROLL > 14) {
            int NewROLL = ROLL - (14-player_row);
            players[PlayerID].playerPieces[Wanna_move_piece] = {14,8};
                if(NewROLL<3){
                    players[PlayerID].playerPieces[Wanna_move_piece] = {14, (8-NewROLL)};
                }
                else{
                    players[PlayerID].playerPieces[Wanna_move_piece] = {14,6};
                    NewROLL=NewROLL-2;
                    int x=14-NewROLL;
                    players[PlayerID].playerPieces[Wanna_move_piece] = {x, 6};
                }
        } else {
            players[PlayerID].playerPieces[Wanna_move_piece] = {player_row + ROLL, player_col};
        }
    }
}





bool Player_Attack(int Moved_piece,int PlayerID){
    for(int i=0;i<4;i++){
        if(i!=PlayerID){
            for(int j=0;j<4;j++){
                if(players[i].playerPieces[j]==players[PlayerID].playerPieces[Moved_piece]){
                    //check if players[i].playerPieces[j] is not in safe spot
                    for(const auto& safeSpot : safeSpots){
                        if(players[i].playerPieces[j] == safeSpot){
                            std::cout<<"Player "<<PlayerID<<" piece "<<Moved_piece<<" is safe"<<std::endl;
                            return false;
                        }
                    }
                    if(stackPieces(i)){
                        return false;
                    }
                    std::cout<<"Player "<<PlayerID<<" piece "<<Moved_piece<<" is attacked by Player "<<i<<" piece "<<j<<std::endl;
                    players[i].playerPieces[j]={0,0};
                    players[i].playerPieces_set[j]=false;
                    players[i].playerPieces_count--;
                    return true;
                }
            }
        }
    }
    return false;
}

//write a function where PlayerID two pieces are in same spot it would stack on top of each other
bool stackPieces(int PlayerID) {
    // Loop through all pieces of the player
    for (int i = 0; i < 4; i++) {
        // Check if the piece is set
        if (players[PlayerID].playerPieces_set[i]) {
            // Loop through all other pieces
            for (int j = i + 1; j < 4; j++) {
                // Check if the other piece is set and in the same position
                if (players[PlayerID].playerPieces_set[j] && players[PlayerID].playerPieces[i] == players[PlayerID].playerPieces[j]) {
                     players[PlayerID].at_safe_positions[i] = true;
                     players[PlayerID].at_safe_positions[j] = true;
                    std::cout << "Player " << PlayerID << " has two pieces in the same position (" << players[PlayerID].playerPieces[i][0] << ", " << players[PlayerID].playerPieces[i][1] << "). They are stacked." << std::endl;
                    return true;
                }
            }
        }
    }
    return false;
}

bool stackPieces_Quad(int PlayerID, int Wanna_move_piece) {
    // Check if the piece is set
    if (players[PlayerID].playerPieces_set[Wanna_move_piece]) {
        // Loop through all other pieces
        for (int j = 0; j < 4; j++) {
            // Check if the other piece is set and in the same position
            if (j != Wanna_move_piece && players[PlayerID].playerPieces_set[j] && players[PlayerID].playerPieces[Wanna_move_piece] == players[PlayerID].playerPieces[j]) {
                players[PlayerID].at_safe_positions[Wanna_move_piece] = true;
                players[PlayerID].at_safe_positions[j] = true;
                std::cout << "Player " << PlayerID << " has two pieces in the same position (" << players[PlayerID].playerPieces[Wanna_move_piece][0] << ", " << players[PlayerID].playerPieces[Wanna_move_piece][1] << "). They are stacked." << std::endl;
                return true;
            }
        }
    }
    return false;
}


int stackPieces_move(int PlayerID, int pieceIndex) {
    // Check if the piece is set
    if (players[PlayerID].playerPieces_set[pieceIndex]) {
        // Loop through all other pieces
        for (int j = 0; j < 4; j++) {
            // Check if the other piece is set and in the same position
            if (j != pieceIndex && players[PlayerID].playerPieces_set[j] && players[PlayerID].playerPieces[pieceIndex] == players[PlayerID].playerPieces[j]) {
                // Stack the pieces by updating their status
                // This can be done in various ways depending on your game logic
                // Here we just print a message
                std::cout << "Player " << PlayerID << " has two pieces in the same position (" << players[PlayerID].playerPieces[pieceIndex][0] << ", " << players[PlayerID].playerPieces[pieceIndex][1] << "). They are stacked." << std::endl;
                // Return the index of the stacked piece
                return j;
            }
        }
    }
    // Return -1 if no stack is found
    return -1;
}



void PLAYER1(){
    do {
        ROll = rollDice();
        //PLAYER1
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (players[0].playerHome < 4) {
            std::cout << "01 Player 1: " << players[0].playerName << " rolled a " << ROll << std::endl;
            if (players[0].playerPieces_count == 0) {
                if (ROll == 6) {
                    players[0].playerPieces_set[0] = true;
                    players[0].playerPieces[0] = {6, 1};
                    players[0].playerPieces_count++;
                }
            } else {
                std::cout << "\tPlayer 1: " << players[0].playerName
                          << " \n\tWhich piece you wanna move \t\tEnter -1 for none instead take the piece out of starting position"
                          << std::endl;
                std::cout << "PLAYER pieces out of starting position -->indexing:\t";
                for (int i = 0; i < 4; i++) {
                    std::cout << i << " ";
                    std::cout << (players[0].playerPieces_set[i] ? "true" : "false") << "\t";
                }
                std::cout << std::endl;
                std::cout << "Player 1: " << players[0].playerName << " place count pieces: ";
                for (int i = 0; i < 4; i++) {
                    std::cout << players[0].player_place_count_pieces[i] << " ";
                }
                std::cout << std::endl;
                int Wanna_move_piece = 0;
                do {
                    std::cout << "Enter the piece you want to move (0-3): ";
                    std::cin >> Wanna_move_piece;
                } while ((Wanna_move_piece < -1) || (Wanna_move_piece > 3));
                if ((Wanna_move_piece == -1) && (ROll == 6)) {
                    for (int i = 0; i < 4; i++) {
                        if (!players[0].playerPieces_set[i]) {
                            players[0].playerPieces_set[i] = true;
                            players[0].playerPieces[i] = {6, 1};
                            players[0].playerPieces_count++;
                            break;
                        }
                    }
                } else {
                    if (players[0].playerPieces_almost_home[Wanna_move_piece]) {
                        int player_col_almost_home = players[0].playerPieces[Wanna_move_piece][1];
                        if (player_col_almost_home < ROll) {
                            std::cout << "\nPlayer 1 piece cant enter home\t" << Wanna_move_piece << std::endl;
                        } else {
                            players[0].playerPieces[Wanna_move_piece] = {7, player_col_almost_home + ROll};
                            position_check(0,Wanna_move_piece);
                            if (players[0].playerPieces[Wanna_move_piece][1] == 6) {
                                std::cout << "\n\n" << std::endl;
                                std::cout << "\nPlayer 1 piece Enter home\t" << Wanna_move_piece << std::endl;
                                std::cout << "\n\n" << std::endl;
                                players[0].playerHome++;
                                players[0].player_pieces_at_home[Wanna_move_piece] = true;
                            }
                        }
                    } else if ((players[0].playerPieces_set[Wanna_move_piece])) {
                        int player_row = players[0].playerPieces[Wanna_move_piece][0];
                        int player_col = players[0].playerPieces[Wanna_move_piece][1];
                        int quadrant = board.getQuadrant(player_row, player_col);
                        if (players[0].player_place_count_pieces[Wanna_move_piece] > 0) {
                            if (ROll - player_col >= 0) {
                                ROll = ROll - player_col;
                                players[0].playerPieces[Wanna_move_piece] = {8, 0};
                                if (ROll > 0) {
                                    players[0].playerPieces[Wanna_move_piece] = {7, 0};
                                    ROll--;
                                    if (ROll > 0) {
                                        int x = players[0].playerPieces[Wanna_move_piece][1];
                                        players[0].playerPieces[Wanna_move_piece] = {7, (x + ROll)};
                                        players[0].playerPieces_almost_home[Wanna_move_piece] = true;
                                    }
                                }
                            } else {
                                players[0].playerPieces[Wanna_move_piece] = {8, player_col - ROll};
                            }
                        } else {
                            if(stackPieces_Quad(0,Wanna_move_piece)){
                                int x=stackPieces_move(0,Wanna_move_piece);
                                ROll=ROll/2;
                                Quadrant_moves(player_row, player_col, ROll, 0, quadrant, Wanna_move_piece);
                                Quadrant_moves(player_row, player_col, ROll, 0, quadrant, x);
                                position_check(0,Wanna_move_piece);
                            }
                            else{
                                Quadrant_moves(player_row, player_col, ROll, 0, quadrant, Wanna_move_piece);
                                position_check(0,Wanna_move_piece);
                            }

                        }
                        if(Player_Attack(Wanna_move_piece,0)){
                            std::cout<<"Player Attack successfully"<<std::endl;
                        }
                        int player_row_check = players[0].playerPieces[Wanna_move_piece][0];
                        if ((quadrant == 1) && (player_row_check == 8)) {
                            players[0].player_place_count_pieces[Wanna_move_piece]++;
                        }

                    }
                }

            }
        }
    } while (ROll == 6);
}

void PLAYER2(){
    do{
        ROll = rollDice();
        //PLAYER2
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (players[1].playerHome < 4) {
            std::cout << "02 Player 2: " << players[1].playerName << " rolled a " << ROll << std::endl;
            if (players[1].playerPieces_count == 0) {
                if (ROll == 6) {
                    players[1].playerPieces_set[0] = true;
                    players[1].playerPieces[0] = {1, 8};
                    players[1].playerPieces_count++;
                }
            } else {
                std::cout << "\tPlayer 2: " << players[1].playerName
                          << " \n\tWhich piece you wanna move \t\tEnter -1 for none instead take the piece out of starting position"
                          << std::endl;
                std::cout<<"PLAYER pieces out of starting position -->indexing:\t";
                for (int i = 0; i < 4; i++) {
                    std::cout<<i<<" ";
                    std::cout << (players[1].playerPieces_set[i] ? "true" : "false") << "\t";
                }
                std::cout << std::endl;
                std::cout << "Player 2: " << players[1].playerName << " place count pieces: ";
                for (int i = 0; i < 4; i++) {
                    std::cout << players[1].player_place_count_pieces[i] << " ";
                }
                std::cout << std::endl;
                //Wanna_move_piece should be between 0-3
                int Wanna_move_piece;
                do {
                    std::cout << "Enter the piece you want to move (0-3): ";
                    std::cin >> Wanna_move_piece;
                } while ((Wanna_move_piece < -1) || (Wanna_move_piece > 3));
                if (Wanna_move_piece == -1 && ROll == 6) {
                    for (int i = 0; i < 4; i++) {
                        if (!players[1].playerPieces_set[i]) {
                            players[1].playerPieces_set[i] = true;
                            players[1].playerPieces[i] = {1, 8};
                            players[1].playerPieces_count++;
                            break;
                        }
                    }
                } else {
                    if (players[1].playerPieces_almost_home[Wanna_move_piece]) {
                        int player_row_almost_home= players[1].playerPieces[Wanna_move_piece][0];
                        if((6-player_row_almost_home)<ROll){
                            std::cout<<"\nPlayer 2 piece cant enter home\t"<<Wanna_move_piece<<std::endl;
                        }
                        else{
                            players[1].playerPieces[Wanna_move_piece]= {player_row_almost_home+ROll,7};
                            position_check(1,Wanna_move_piece);
                            if(players[1].playerPieces[Wanna_move_piece][0]==6){
                                std::cout<<"\n\n"<<std::endl;
                                std::cout<<"\nPlayer 2 piece Enter home\t"<<Wanna_move_piece<<std::endl;
                                std::cout<<"\n\n"<<std::endl;
                                players[1].playerHome++;
                                players[1].player_pieces_at_home[Wanna_move_piece]=true;
                            }
                        }
                    }
                    else if ((players[1].playerPieces_set[Wanna_move_piece])){
                        int player_row = players[1].playerPieces[Wanna_move_piece][0];
                        int player_col = players[1].playerPieces[Wanna_move_piece][1];
                        int quadrant = board.getQuadrant(player_row, player_col);
                        if (players[1].player_place_count_pieces[Wanna_move_piece] > 0) {
                            if (ROll - player_row >= 0) {
                                ROll = ROll - player_row;
                                players[1].playerPieces[Wanna_move_piece] = {0, 6};
                                if (ROll > 0) {
                                    players[1].playerPieces[Wanna_move_piece] = {0, 7};
                                    ROll--;
                                    if (ROll > 0) {
                                        int x = players[1].playerPieces[Wanna_move_piece][0];
                                        players[1].playerPieces[Wanna_move_piece] = {(x+ROll),7};
                                        players[1].playerPieces_almost_home[Wanna_move_piece] = true;
                                    }
                                }
                            } else {
                                players[1].playerPieces[Wanna_move_piece] = {player_row-ROll,6};
                            }
                        } else {
                            if(stackPieces_Quad(1,Wanna_move_piece)){
                                int x=stackPieces_move(1,Wanna_move_piece);
                                ROll=ROll/2;
                                Quadrant_moves(player_row, player_col, ROll, 1, quadrant, Wanna_move_piece);
                                Quadrant_moves(player_row, player_col, ROll, 1, quadrant, x);
                                position_check(1,Wanna_move_piece);
                            }
                            else{
                                Quadrant_moves(player_row, player_col, ROll, 1, quadrant, Wanna_move_piece);
                                position_check(1,Wanna_move_piece);
                            }

                        }
                        if(Computer_PLayer_attack(Wanna_move_piece,1)){
                            std::cout<<"Player Attack successfully"<<std::endl;
                        }
                        int player_col_check = players[1].playerPieces[Wanna_move_piece][1];
                        if ((quadrant == 2) && (player_col_check == 8)) {
                            players[1].player_place_count_pieces[Wanna_move_piece]++;
                        }

                    }
                }

            }
        }
        std::cout<<std::endl;

    } while (ROll==6);
}

void PLAYER3(){
    do {
        ROll = rollDice();
        //PLAYER3
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (players[2].playerHome < 4) {
            std::cout << "03 Player 3: " << players[2].playerName << " rolled a " << ROll << std::endl;
            if (players[2].playerPieces_count == 0) {
                if (ROll == 6) {
                    players[2].playerPieces_set[0] = true;
                    players[2].playerPieces[0] = {8, 13};
                    players[2].playerPieces_count++;
                }
            } else {
                std::cout << "\tPlayer 3: " << players[0].playerName
                          << " \n\tWhich piece you wanna move \t\tEnter -1 for none instead take the piece out of starting position"
                          << std::endl;
                std::cout << "PLAYER pieces out of starting position -->indexing:\t";
                for (int i = 0; i < 4; i++) {
                    std::cout << i << " ";
                    std::cout << (players[2].playerPieces_set[i] ? "true" : "false") << "\t";
                }
                std::cout << std::endl;
                std::cout << "Player 3: " << players[2].playerName << " place count pieces: ";
                for (int i = 0; i < 4; i++) {
                    std::cout << players[2].player_place_count_pieces[i] << " ";
                }
                std::cout << std::endl;
                int Wanna_move_piece = 0;
                do {
                    std::cout << "Enter the piece you want to move (0-3): ";
                    std::cin >> Wanna_move_piece;
                } while ((Wanna_move_piece < -1) || (Wanna_move_piece > 3));
                if (Wanna_move_piece == -1 && ROll == 6) {
                    for (int i = 0; i < 4; i++) {
                        if (!players[2].playerPieces_set[i]) {
                            players[2].playerPieces_set[i] = true;
                            players[2].playerPieces[i] = {8, 13};
                            players[2].playerPieces_count++;
                            break;
                        }
                    }
                } else {
                    if (players[2].playerPieces_almost_home[Wanna_move_piece]) {
                        int player_col_almost_home = players[2].playerPieces[Wanna_move_piece][1];
                        if ((player_col_almost_home-8) < ROll) {
                            std::cout << "\nPlayer 3 piece cant enter home\t" << Wanna_move_piece << std::endl;
                        } else {
                            players[2].playerPieces[Wanna_move_piece] = {7, player_col_almost_home - ROll};
                            position_check(2,Wanna_move_piece);
                            if (players[2].playerPieces[Wanna_move_piece][1] == 8) {
                                std::cout << "\n\n" << std::endl;
                                std::cout << "\nPlayer 3 piece Enter home\t" << Wanna_move_piece << std::endl;
                                std::cout << "\n\n" << std::endl;
                                players[2].playerHome++;
                                players[2].player_pieces_at_home[Wanna_move_piece] = true;
                            }
                        }
                    } else if ((players[2].playerPieces_set[Wanna_move_piece])) {
                        int player_row = players[2].playerPieces[Wanna_move_piece][0];
                        int player_col = players[2].playerPieces[Wanna_move_piece][1];
                        int quadrant = board.getQuadrant(player_row, player_col);
                        if (players[2].player_place_count_pieces[Wanna_move_piece] > 0) {
                            if (player_col+ROll >= 14) {
                                ROll = ROll- (14-player_col);
                                players[2].playerPieces[Wanna_move_piece] = {6,14};
                                if (ROll > 0) {
                                    players[2].playerPieces[Wanna_move_piece] = {7,14};
                                    ROll--;
                                    if (ROll > 0) {
                                        int x = players[2].playerPieces[Wanna_move_piece][1];
                                        players[2].playerPieces[Wanna_move_piece] = {7, (x - ROll)};
                                        players[2].playerPieces_almost_home[Wanna_move_piece] = true;
                                    }
                                }
                            } else {
                                players[2].playerPieces[Wanna_move_piece] = {6, player_col + ROll};
                            }
                        } else {
                            if(stackPieces_Quad(2,Wanna_move_piece)){
                                int x=stackPieces_move(2,Wanna_move_piece);
                                ROll=ROll/2;
                                Quadrant_moves(player_row, player_col, ROll, 2, quadrant, Wanna_move_piece);
                                Quadrant_moves(player_row, player_col, ROll, 2, quadrant, x);
                                position_check(2,Wanna_move_piece);
                            }
                            else{
                                Quadrant_moves(player_row, player_col, ROll, 2, quadrant, Wanna_move_piece);
                                position_check(2,Wanna_move_piece);
                            }

                        }
                        if(Player_Attack(Wanna_move_piece,2)){
                            std::cout<<"Player Attack successfully"<<std::endl;
                        }
                        int player_row_check = players[2].playerPieces[Wanna_move_piece][0];
                        if ((quadrant == 3) && (player_row_check == 6)) {
                            players[2].player_place_count_pieces[Wanna_move_piece]++;
                        }

                    }
                }

            }
        }
    } while (ROll == 6);
}

void PLAYER4(){
    do {
        ROll = rollDice();
        //PLAYER4
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (players[3].playerHome < 4) {
            std::cout << "04 Player 4: " << players[2].playerName << " rolled a " << ROll << std::endl;
            if (players[3].playerPieces_count == 0) {
                if (ROll == 6) {
                    players[3].playerPieces_set[0] = true;
                    players[3].playerPieces[0] = {8, 13};
                    players[3].playerPieces_count++;
                }
            } else {
                std::cout << "\tPlayer 4: " << players[3].playerName
                          << " \n\tWhich piece you wanna move \t\tEnter -1 for none instead take the piece out of starting position"
                          << std::endl;
                std::cout << "PLAYER pieces out of starting position -->indexing:\t";
                for (int i = 0; i < 4; i++) {
                    std::cout << i << " ";
                    std::cout << (players[3].playerPieces_set[i] ? "true" : "false") << "\t";
                }
                std::cout << std::endl;
                std::cout << "Player 4: " << players[3].playerName << " place count pieces: ";
                for (int i = 0; i < 4; i++) {
                    std::cout << players[3].player_place_count_pieces[i] << " ";
                }
                std::cout << std::endl;
                int Wanna_move_piece = 0;
                do {
                    std::cout << "Enter the piece you want to move (0-3): ";
                    std::cin >> Wanna_move_piece;
                } while ((Wanna_move_piece < -1) || (Wanna_move_piece > 3));
                if (Wanna_move_piece == -1 && ROll == 6) {
                    for (int i = 0; i < 4; i++) {
                        if (!players[3].playerPieces_set[i]) {
                            players[3].playerPieces_set[i] = true;
                            players[3].playerPieces[i] = {8, 13};
                            players[3].playerPieces_count++;
                            break;
                        }
                    }
                } else {
                    if (players[3].playerPieces_almost_home[Wanna_move_piece]) {
                        int player_row_almost_home = players[3].playerPieces[Wanna_move_piece][0];
                        if ((player_row_almost_home-8) < ROll) {
                            std::cout << "\nPlayer 4 piece cant enter home\t" << Wanna_move_piece << std::endl;
                        } else {
                            players[3].playerPieces[Wanna_move_piece] = {(player_row_almost_home - ROll),7};
                            position_check(2,Wanna_move_piece);
                            if (players[3].playerPieces[Wanna_move_piece][1] == 8) {
                                std::cout << "\n\n" << std::endl;
                                std::cout << "\nPlayer 4 piece Enter home\t" << Wanna_move_piece << std::endl;
                                std::cout << "\n\n" << std::endl;
                                players[3].playerHome++;
                                players[3].player_pieces_at_home[Wanna_move_piece] = true;
                            }
                        }
                    } else if ((players[3].playerPieces_set[Wanna_move_piece])) {
                        int player_row = players[3].playerPieces[Wanna_move_piece][0];
                        int player_col = players[3].playerPieces[Wanna_move_piece][1];
                        int quadrant = board.getQuadrant(player_row, player_col);
                        if (players[3].player_place_count_pieces[Wanna_move_piece] > 0) {
                            if (player_row+ROll >= 14) {
                                ROll = ROll- (14-player_row);
                                players[3].playerPieces[Wanna_move_piece] = {14,8};
                                if (ROll > 0) {
                                    players[3].playerPieces[Wanna_move_piece] = {14,7};
                                    ROll--;
                                    if (ROll > 0) {
                                        int x = players[3].playerPieces[Wanna_move_piece][0];
                                        players[3].playerPieces[Wanna_move_piece] = {(x-ROll),7};
                                        players[3].playerPieces_almost_home[Wanna_move_piece] = true;
                                    }
                                }
                            } else {
                                players[3].playerPieces[Wanna_move_piece] = {player_row+ROll, 8};
                            }
                        } else {
                            if(stackPieces_Quad(3,Wanna_move_piece)){
                                int x=stackPieces_move(3,Wanna_move_piece);
                                ROll=ROll/2;
                                Quadrant_moves(player_row, player_col, ROll, 3, quadrant, Wanna_move_piece);
                                Quadrant_moves(player_row, player_col, ROll, 3, quadrant, x);
                                position_check(2,Wanna_move_piece);
                            }
                            else{
                                Quadrant_moves(player_row, player_col, ROll, 3, quadrant, Wanna_move_piece);
                                position_check(2,Wanna_move_piece);
                            }


                        }
                        if(Player_Attack(Wanna_move_piece,3)){
                            std::cout<<"Player Attack successfully"<<std::endl;
                        }
                        int player_col_check = players[3].playerPieces[Wanna_move_piece][0];
                        if ((quadrant == 4) && (player_col_check == 8)) {
                            players[3].player_place_count_pieces[Wanna_move_piece]++;
                        }

                    }
                }

            }
        }
    } while (ROll == 6);
}



int Computer_Move(int PlayerID,int Roll){
    std::vector<int> Computer_set;
    std::vector<int> Enemy_set;
    if((Roll==6)&&(players[0].playerPieces_count<4)){
        return -1;
    }
    int Piece_count=0;
    int Enemy_piece_count=0;
    for(int i=0;i<4;i++){
        if (players[0].playerPieces_set[i]){
            Piece_count++;
            Computer_set.push_back(i);
        }
    }
    if(Piece_count==1) {
        return 0;
    }
    else{
        for(int i=0;i<4;i++){
            if (players[1].playerPieces_set[i]){
                Enemy_piece_count++;
                Enemy_set.push_back(i);
            }
        }
        if(Enemy_piece_count==0){
            return 0;
        }
        else{
            int Attack_piece=Computer_Attack(Computer_set,Enemy_set,Roll);
            if(Attack_piece!=-1){
                return Attack_piece;
            }
            else{
                int Safe_piece=ComputerSafeSpots(Computer_set,Roll);
                if(Safe_piece!=-1){
                    return Safe_piece;
                }
                else{
                    int AlmostHome_piece=ComputerAlmostHome(Computer_set,Roll);
                    if(AlmostHome_piece!=-1){
                        return AlmostHome_piece;
                    }
                    else{
                            return 0;
                    }
                }
            }
        }

    }

}


int getRandomIndex(const std::vector<bool>& playerPieces_set) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<int> validIndices;

    // Find indices where playerPieces_set is true
    for (int i = 0; i < playerPieces_set.size(); ++i) {
        if (playerPieces_set[i]) {
            validIndices.push_back(i);
        }
    }

    // Generate a random index from the valid indices
    if (!validIndices.empty()) {
        std::uniform_int_distribution<> dis(0, validIndices.size() - 1);
        return validIndices[dis(gen)];
    } else {
        // Return -1 if no valid index is found
        return -1;
    }
}

int Computer_Attack(const std::vector<int>& Computer_set,const std::vector<int>& Enemy_set,int ROLL){
    std::vector<std::vector<int>> Dummy_Computer_pieces;
    int Attack_piece=0;
    for(int i=0;i<4;i++){
        if(players[0].playerPieces_set[i]){
            Dummy_Computer_pieces.push_back(players[0].playerPieces[i]);
        }
    }
    for(auto i:Computer_set){
        for(auto j:Enemy_set){
            int Quadrant=board.getQuadrant(players[0].playerPieces[i][0],players[0].playerPieces[i][1]);
            Quadrant_moves(players[0].playerPieces[i][0],players[0].playerPieces[i][1], ROLL,0,Quadrant,i);
            if(players[0].playerPieces[i]==players[1].playerPieces[j]){
                //if(stackPieces(1)){
                //    return false;
                //}
                std::cout<<"Player "<<0<<" piece "<<i<<" is attacked by Player "<<1<<" piece "<<j<<std::endl;
                players[0].playerPieces[i]=Dummy_Computer_pieces[i];
                Attack_piece=i;
            }
            else{
                players[0].playerPieces[i]=Dummy_Computer_pieces[i];
                continue;
            }
        }
    }
    if(Attack_piece!=0){
        return Attack_piece;
    }
    else{
        return -1;
    }
}

int ComputerSafeSpots(const std::vector<int>& Computer_set,int ROLL){
    std::vector<std::vector<int>> Dummy_Computer_pieces;
    int safe_piece=0;
    for(int i=0;i<4;i++){
        if(players[0].playerPieces_set[i]){
            Dummy_Computer_pieces.push_back(players[0].playerPieces[i]);
        }
    }
    for(auto i:Computer_set){
            int Quadrant=board.getQuadrant(players[0].playerPieces[i][0],players[0].playerPieces[i][1]);
            Quadrant_moves(players[0].playerPieces[i][0],players[0].playerPieces[i][1], ROLL,0,Quadrant,i);
            for(const auto& safeSpot : safeSpots){
                if(players[0].playerPieces[i] == safeSpot){
                    std::cout<<"Player "<<0<<" piece "<<i<<" is safe"<<std::endl;
                    safe_piece=i;
                }
            }
        players[0].playerPieces[i]=Dummy_Computer_pieces[i];
    }
    if(safe_piece!=0){
        return safe_piece;
    }
    else{
        return -1;
    }
}


int ComputerAlmostHome(const std::vector<int>& Computer_set,int ROLL){
    std::vector<std::vector<int>> Dummy_Computer_pieces;
    int AlmostHome_piece=0;
    for(int i=0;i<4;i++){
        if(players[0].playerPieces_set[i]){
            Dummy_Computer_pieces.push_back(players[0].playerPieces[i]);
        }
    }
    for(auto i:Computer_set){
        if((players[0].player_place_count_pieces[i])||!(players[0].playerPieces_almost_home[i])){
            std::cout<<"Player "<<0<<" piece "<<i<<" is almost home"<<std::endl;
            AlmostHome_piece=i;
        }
        //players[0].playerPieces[i]=Dummy_Computer_pieces[i];
    }
    if(AlmostHome_piece!=0){
        return AlmostHome_piece;
        //return AlmostHome_piece;
    }
    else{
        return -1;
    }

}




void ComputerPLAYER(){
    do {
        ROll = rollDice();
        //COMPUTER_PLAYER1
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (players[0].playerHome < 4) {
            std::cout << "01 COMPUTER Player 1: " << players[0].playerName << " rolled a " << ROll << std::endl;
            if (players[0].playerPieces_count == 0) {
                if (ROll == 6) {
                    players[0].playerPieces_set[0] = true;
                    players[0].playerPieces[0] = {6, 1};
                    players[0].playerPieces_count++;
                }
            } else {
                std::cout << "\tCOMPUTER Player 1: " << players[0].playerName
                          << std::endl;
                std::cout << "PLAYER pieces out of starting position -->indexing:\t";
                for (int i = 0; i < 4; i++) {
                    std::cout << i << " ";
                    std::cout << (players[0].playerPieces_set[i] ? "true" : "false") << "\t";
                }
                std::cout << std::endl;
                int Wanna_move_piece = 0;
                Wanna_move_piece=Computer_Move(0,ROll);
                std::cout<<Wanna_move_piece<<std::endl;
                if (Wanna_move_piece == -1 && ROll == 6) {
                    for (int i = 0; i < 4; i++) {
                        if (!players[0].playerPieces_set[i]) {
                            players[0].playerPieces_set[i] = true;
                            players[0].playerPieces[i] = {6, 1};
                            players[0].playerPieces_count++;
                            break;
                        }
                    }
                } else {
                    if ((players[0].playerPieces_almost_home[Wanna_move_piece])&&!(players[0].player_pieces_at_home[Wanna_move_piece])) {
                        int player_col_almost_home = players[0].playerPieces[Wanna_move_piece][1];
                        if (player_col_almost_home < ROll) {
                            std::cout << "\nComputer Player 1 piece cant enter home\t" << Wanna_move_piece << std::endl;
                        } else {
                            players[0].playerPieces[Wanna_move_piece] = {7, player_col_almost_home + ROll};
                            position_check(0,Wanna_move_piece);
                            if (players[0].playerPieces[Wanna_move_piece][1] == 6) {
                                std::cout << "\n\n" << std::endl;
                                std::cout << "\nComputer Player 1 piece Enter home\t" << Wanna_move_piece << std::endl;
                                std::cout << "\n\n" << std::endl;
                                players[0].playerHome++;
                                players[0].player_pieces_at_home[Wanna_move_piece] = true;
                            }
                        }
                    } else if ((players[0].playerPieces_set[Wanna_move_piece])) {
                        int player_row = players[0].playerPieces[Wanna_move_piece][0];
                        int player_col = players[0].playerPieces[Wanna_move_piece][1];
                        int quadrant = board.getQuadrant(player_row, player_col);
                        if (players[0].player_place_count_pieces[Wanna_move_piece] > 0) {
                            if (ROll - player_col >= 0) {
                                ROll = ROll - player_col;
                                players[0].playerPieces[Wanna_move_piece] = {8, 0};
                                if (ROll > 0) {
                                    players[0].playerPieces[Wanna_move_piece] = {7, 0};
                                    ROll--;
                                    if (ROll > 0) {
                                        int x = players[0].playerPieces[Wanna_move_piece][1];
                                        players[0].playerPieces[Wanna_move_piece] = {7, (x + ROll)};
                                        players[0].playerPieces_almost_home[Wanna_move_piece] = true;
                                    }
                                }
                            } else {
                                players[0].playerPieces[Wanna_move_piece] = {8, player_col - ROll};
                            }
                        } else {
                            if(stackPieces_Quad(0,Wanna_move_piece)){
                                int x=stackPieces_move(0,Wanna_move_piece);
                                ROll=ROll/2;
                                Quadrant_moves(player_row, player_col, ROll, 0, quadrant, Wanna_move_piece);
                                Quadrant_moves(player_row, player_col, ROll, 0, quadrant, x);
                                position_check(0,Wanna_move_piece);
                            }
                            else{
                                Quadrant_moves(player_row, player_col, ROll, 0, quadrant, Wanna_move_piece);
                                position_check(0,Wanna_move_piece);
                            }

                        }
                        if(Computer_PLayer_attack(Wanna_move_piece,0)){
                            std::cout<<"Player Attack successfully"<<std::endl;
                        }
                        int player_row_check = players[0].playerPieces[Wanna_move_piece][0];
                        if ((quadrant == 1) && (player_row_check == 8)) {
                            players[0].player_place_count_pieces[Wanna_move_piece]++;
                            std::cout<<"player_place_count_pieces"<<players[0].player_place_count_pieces[Wanna_move_piece]<<std::endl;
                        }

                    }
                }

            }
        }
    } while (ROll == 6);
}

bool Computer_PLayer_attack(int Moved_piece,int PlayerID){
    for(int i=0;i<2;i++){
        if(i!=PlayerID){
            for(int j=0;j<4;j++){
                if(players[i].playerPieces[j]==players[PlayerID].playerPieces[Moved_piece]){
                    //check if players[i].playerPieces[j] is not in safe spot
                    for(const auto& safeSpot : safeSpots){
                        if(players[i].playerPieces[j] == safeSpot){
                            std::cout<<"Player "<<PlayerID<<" piece "<<Moved_piece<<" is safe"<<std::endl;
                            return false;
                        }
                    }
                    //if(stackPieces(i)){
                    //    return false;
                    //}
                    std::cout<<"Player "<<PlayerID<<" piece "<<Moved_piece<<" is attacked by Player "<<i<<" piece "<<j<<std::endl;
                    players[i].playerPieces[j]={0,0};
                    players[i].playerPieces_set[j]=false;
                    players[i].playerPieces_count--;
                    return true;
                }
            }
        }
    }
    return false;
}