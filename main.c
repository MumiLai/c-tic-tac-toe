#include <stdio.h>

// 把棋盤印出來
void print_board(char board[3][3]) {
    printf("\n");
    for (int row = 0; row < 3; row++) {
        printf(" %c | %c | %c \n", board[row][0], board[row][1], board[row][2]);
        if (row < 2) {
            printf("---+---+---\n");
        }
    }
    printf("\n");
}

int main(void) {
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    char player = 'X';   // 目前輪到誰，X 先手

    // 棋盤有 9 格，所以最多下 9 手
    for (int turn = 0; turn < 9; turn++) {
        print_board(board);

        int pos;
        printf("Player %c, choose a position (1-9): ", player);
        scanf("%d", &pos);

        // 把 1~9 的編號換算成二維陣列的 [列][行]
        // 例如 pos = 5：列 = (5-1)/3 = 1，行 = (5-1)%3 = 1，正中間
        int row = (pos - 1) / 3;
        int col = (pos - 1) % 3;

        board[row][col] = player;   // 把棋子放上去

        // 換人：如果現在是 X 就換成 O，否則換成 X
        player = (player == 'X') ? 'O' : 'X';
    }

    print_board(board);   // 9 手下完，印出最後的棋盤
    return 0;
}