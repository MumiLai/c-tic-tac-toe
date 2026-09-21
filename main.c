#include <stdio.h>
#include <time.h>
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

// 電腦下棋(隨機亂數）：從所有空格中隨機挑一格，回傳位置 1~9
int computer_move(char board[3][3]) {
    int empty[9];    // 存放所有空格的編號
    int count = 0;   // 目前找到幾個空格

    for (int pos = 1; pos <= 9; pos++) {
        int row = (pos - 1) / 3;
        int col = (pos - 1) % 3;
        if (board[row][col] == ' ') {
            empty[count] = pos;
            count++;
        }
    }

    // rand() % count 會得到 0 到 count-1，剛好可以當作 empty 陣列的索引
    return empty[rand() % count];
}

// 讓玩家選擇模式：1 是雙人對戰，2 是對電腦
int choose_mode(void) {
    int mode;
    int result;

    while (1) {
        printf("Select mode: 1) Two players  2) Play against computer: ");
        result = scanf("%d", &mode);

        if (result == EOF) {
            exit(0);
        }

        clear_input();

        if (result == 1 && (mode == 1 || mode == 2)) {
            return mode;
        }
        printf("Please enter 1 or 2.\n");
    }
}

int main(void) {
    srand((unsigned int)time(NULL));   // 亂數種子只設定一次
    char again = 'n';

    do {
        int mode = choose_mode();   // 每一局開始前選擇模式

        char board[3][3] = {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
        };

        char player = 'X';
        char winner = ' ';

        for (int turn = 0; turn < 9; turn++) {
            print_board(board);

            int pos;
            // 對電腦模式時，人類是 X，電腦是 O
            if (mode == 2 && player == 'O') {
                pos = computer_move(board);
                printf("Computer (O) chooses position %d.\n", pos);
            } else {
                pos = read_position(board, player);
            }

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

        printf("Play again? (y/n): ");
        scanf(" %c", &again);
        clear_input();

    } while (again == 'y' || again == 'Y');

    printf("Thanks for playing!\n");
    return 0;
}