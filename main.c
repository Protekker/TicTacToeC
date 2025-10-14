#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_board(const char b[9]) {
    printf("\n");
    for (int i = 0; i < 9; i++) {
        printf(" %c ", b[i]);
        if (i % 3 != 2) printf("|");
        if (i % 3 == 2 && i != 8) printf("\n---+---+---\n");
    }
    printf("\n\n");
}

int check_winner(const char b[9]) {
    //Returns 'X' or 'O' as int or 0 for no winner
    const int lines[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8}, //rows
        {0,3,6}, {1,4,7}, {2,5,8}, //cols
        {0,4,8}, {2,4,6}           //diag
    };
    for (int i = 0; i < 8; ++i) {
        int a = lines[i][0], c = lines[i][1], d = lines[i][2];
        if (b[a] == b[c] && b[c] == b[d]) return (int)b[a];
    }
    return 0;
}

int is_draw(const char b[9]) {
    for (int i = 0; i < 9; ++i) {
        if (b[i] != 'X' && b[i] != 'O') return 0;
    }
    return 1; 
}

int main(void) {
    char board[9];
    for (int i = 0; i < 9; ++i) board[i] = '1' + i;

    char player = 'X';
    char input[18];

    while (1) {
        print_board(board);
        printf("Player %c, enter a position (1-9): ", player);

        if (!fgets(input, sizeof(input), stdin)) {
            printf("\nNo input detected. Exiting.\n");
            return 0;
        }
        char *p = input;
        while (*p == ' ' || *p == '\t') ++p;

        int pos = 0;
        if (sscanf(p, "%d", &pos) != 1) {
            printf("Invalid input. Please enter a number from 1 to 9.\n");
            continue;
        }

        if (pos < 1 || pos > 9) {
            printf("Position must be between 1 and 9.\n");
            continue;
        }

        int idx = pos - 1;
        if (board[idx] == 'X' || board[idx] == 'O') {
            printf("That position is already taken. Try again.\n");
            continue;
        }

        board[idx] = player;

        int winner = check_winner(board);
        if (winner) {
            print_board(board);
            printf("Player %c wins!\n", (char)winner);
            break;
        }

        if (is_draw(board)) {
            print_board(board);
            printf("It's a draw!\n");
            break;
        }

        // switch player
        player = (player == 'X') ? 'O' : 'X'; //If player X then change to O, else X (ternary operator)
    }

    return 0;
}