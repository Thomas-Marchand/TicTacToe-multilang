#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// create and return an initialized board
char* create_board() {
    char* board = (char*)malloc(9 * sizeof(char));
    for (int i = 0; i < 9; i++) {
        board[i] = ' ';
    }
    return board;
}

// print the board, with a reference board on the right (1-9)
void print_board(char* board) {
    for (int i = 0; i < 9; i += 3) {
        printf(" %c | %c | %c    %d | %d | %d\n", board[i], board[i+1], board[i+2], i+1, i+2, i+3);
        if (i < 6) {
            printf("---|---|---  ---|---|---\n");
        }
    }
}

// check if the board is full
int is_full(char* board) {
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            return 0;
        }
    }
    return 1;
}

// check if the player has won
int has_won(char* board, char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i] == player && board[i+3] == player && board[i+6] == player) {
            return 1;
        }
        if (board[3*i] == player && board[3*i+1] == player && board[3*i+2] == player) {
            return 1;
        }
    }
    if (board[0] == player && board[4] == player && board[8] == player) {
        return 1;
    }
    if (board[2] == player && board[4] == player && board[6] == player) {
        return 1;
    }
    return 0;
}

// get move input from player
int get_move(char* board) {
    int move;
    while (1) {
        printf("Enter your move (1-9): ");
        scanf("%d", &move);
        if (move >= 1 && move <= 9 && board[move-1] == ' ') {
            return move;
        }
        printf("Invalid move.\n");
    }
}

// bot random move
int bot_move(char* board) {
    int move;
    while (1) {
        move = rand() % 9;
        if (board[move-1] == ' ') {
            return move;
        }
    }
}

// minimax algorithm
int minimax(char* board, int depth, int is_maximizing) {
    if (has_won(board, 'X')) {
        return -10;
    }
    if (has_won(board, 'O')) {
        return 10;
    }
    if (is_full(board)) {
        return 0;
    }
    if (is_maximizing) { // bot's turn
        int best_score = -1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] == ' ') {
                board[i] = 'O';
                int score = minimax(board, depth+1, 0);
                board[i] = ' ';
                if (score > best_score) {
                    best_score = score;
                }
            }
        }
        return best_score;
    } else { // player's turn
        int best_score = 1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] == ' ') {
                board[i] = 'X';
                int score = minimax(board, depth+1, 1);
                board[i] = ' ';
                if (score < best_score) {
                    best_score = score;
                }
            }
        }
        return best_score;
    }
}

// bot minimax (don't forget to check the current move)
int bot_minimax(char* board) {
    int best_score = -1000;
    int best_move;
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            board[i] = 'O';
            if (has_won(board, 'O')) { // check winning move
                board[i] = ' ';
                return i+1;
            }
            int score = minimax(board, 0, 0);
            printf("Move %d: %d\n", i+1, score); // debug
            board[i] = ' ';
            if (score > best_score) {
                best_score = score;
                best_move = i+1;
            }
        }
    }
    return best_move;
}


// play the game
void play_game(char initial) {
    char* board = create_board();
    char player = initial;
    int move;
    while (1) {
        print_board(board);
        if (player == 'X') {
            move = get_move(board);
        } else {
            move = bot_minimax(board);
        }
        board[move-1] = player;
        if (has_won(board, player)) {
            print_board(board);
            printf("%c wins!\n", player);
            break;
        }
        if (is_full(board)) {
            print_board(board);
            printf("It's a draw!\n");
            break;
        }
        player = (player == 'X') ? 'O' : 'X';
    }
    free(board);
}


int main() {
    srand(time(NULL));
    play_game('O');
    return 0;
}