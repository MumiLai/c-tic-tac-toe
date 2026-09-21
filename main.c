#include <stdio.h>

// 把棋盤印出來
// char board[3][3] 是 3 列 3 行的二維陣列，每一格存一個字元
void print_board(char board[3][3]) {
    printf("\n");
    for (int row = 0; row < 3; row++) {
        // board[row][0]、[1]、[2] 就是這一列的三個格子
        printf(" %c | %c | %c \n", board[row][0], board[row][1], board[row][2]);
        if (row < 2) {
            printf("---+---+---\n");   // 列與列之間的分隔線，最後一列後面不用
        }
    }
    printf("\n");
}

int main(void) {
    // 二維陣列：' ' 代表空格，之後 'X' 和 'O' 代表玩家的棋子
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    board[1][1] = 'X';   // 正中間
    board[0][2] = 'O';   // 第一列的最右邊

    print_board(board);
    return 0;
}