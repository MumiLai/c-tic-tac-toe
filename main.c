#include <stdio.h>
#include <stdlib.h>

// 清除輸入緩衝區：把這一行剩下的字元讀掉，直到換行為止
void clear_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

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

// 反覆要求玩家輸入，直到輸入一個「1 到 9、而且還是空格」的位置才回傳
int read_position(char board[3][3], char player) {
    int pos;
    int result;

    while (1) {
        printf("Player %c, choose a position (1-9): ", player);
        result = scanf("%d", &pos);

        // 輸入來源關閉（例如按了 Ctrl+Z），沒辦法再讀，直接結束程式
        if (result == EOF) {
            exit(0);
        }

        clear_input();   // 不論成功失敗，都把這一行剩下的內容清掉

        // 檢查 1：有沒有讀到整數
        if (result != 1) {
            printf("That's not a number. Try again.\n");
            continue;   // continue：跳過這一輪剩下的部分，回到迴圈開頭重新問
        }

        // 檢查 2：範圍。一定要在存取陣列「之前」檢查，不然會讀到陣列外面
        if (pos < 1 || pos > 9) {
            printf("Please enter a number between 1 and 9.\n");
            continue;
        }

        // 檢查 3：走到這裡 pos 一定是 1~9，可以安全地換算成 [列][行]
        int row = (pos - 1) / 3;
        int col = (pos - 1) % 3;
        if (board[row][col] != ' ') {
            printf("That spot is already taken. Try again.\n");
            continue;
        }

        return pos;   // 三項檢查都通過，回傳這個位置
    }
}

// 檢查有沒有人獲勝（和上一版相同）
char check_winner(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' &&
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2]) {
            return board[i][0];
        }
    }

    for (int i = 0; i < 3; i++) {
        if (board[0][i] != ' ' &&
            board[0][i] == board[1][i] &&
            board[1][i] == board[2][i]) {
            return board[0][i];
        }
    }

    if (board[1][1] != ' ') {
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            return board[1][1];
        }
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            return board[1][1];
        }
    }

    return ' ';
}

int main(void) {
    char again = 'n';   // 存放「要不要再玩」的回答

    // 外圈迴圈：每跑一輪就是完整的一局遊戲
    do {
        // 宣告在外圈裡面，每一局開始都會重新建立：棋盤清空、X 先手、還沒有贏家
        char board[3][3] = {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
        };

        char player = 'X';
        char winner = ' ';

        // 內圈：一局裡最多下 9 手
        for (int turn = 0; turn < 9; turn++) {
            print_board(board);

            int pos = read_position(board, player);

            int row = (pos - 1) / 3;
            int col = (pos - 1) % 3;
            board[row][col] = player;

            winner = check_winner(board);
            if (winner != ' ') {
                break;
            }

            player = (player == 'X') ? 'O' : 'X';
        }

        print_board(board);

        if (winner != ' ') {
            printf("Player %c wins!\n", winner);
        } else {
            printf("It's a draw!\n");
        }

        // 詢問是否再玩一局
        printf("Play again? (y/n): ");
        scanf(" %c", &again);   // %c 前面的空格會略過殘留的換行
        clear_input();          // 把這一行剩下的字元清掉，避免影響下一局的輸入

    } while (again == 'y' || again == 'Y');

    printf("Thanks for playing!\n");
    return 0;
}