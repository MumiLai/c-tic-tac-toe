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

// 增加勝利條件
// 有人連成一線就回傳那個人的棋子 'X' 或 'O'，沒有就回傳 ' '
char check_winner(char board[3][3]) {
    // 檢查 3 列：同一列的三格不是空格，而且三格都一樣
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' &&
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2]) {
            return board[i][0];
        }
    }

    // 檢查 3 行：同一行的三格（列編號 0、1、2）都一樣
    for (int i = 0; i < 3; i++) {
        if (board[0][i] != ' ' &&
            board[0][i] == board[1][i] &&
            board[1][i] == board[2][i]) {
            return board[0][i];
        }
    }

    // 檢查 2 條對角線：兩條都會經過正中間 board[1][1]
    if (board[1][1] != ' ') {
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            return board[1][1];   // 左上到右下
        }
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            return board[1][1];   // 右上到左下
        }
    }

    return ' '; 
}

int main(void) {
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    char player = 'X';
    char winner = ' ';   // ' ' 代表目前還沒有贏家

    for (int turn = 0; turn < 9; turn++) {
        print_board(board);

        int pos;
        printf("Player %c, choose a position (1-9): ", player);
        scanf("%d", &pos);

        int row = (pos - 1) / 3;
        int col = (pos - 1) % 3;
        board[row][col] = player;

        // 每下一手就檢查一次，有贏家就提前跳出迴圈
        winner = check_winner(board);
        if (winner != ' ') {
            break;   // break 會立刻離開這個 for 迴圈
        }

        player = (player == 'X') ? 'O' : 'X';
    }

    print_board(board);

    if (winner != ' ') {
        printf("Player %c wins!\n", winner);
    } else {
        printf("It's a draw!\n");   // 9 手都下完還沒有贏家
    }

    return 0;
}