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

// 找出 symbol 下一手能贏的位置，找不到就回傳 0
int find_winning_move(char board[3][3], char symbol) {
    for (int pos = 1; pos <= 9; pos++) {
        int row = (pos - 1) / 3;
        int col = (pos - 1) % 3;

        if (board[row][col] == ' ') {
            board[row][col] = symbol;               // 先試著放下去
            char winner = check_winner(board);      // 看有沒有連成一線
            board[row][col] = ' ';                  // 一定要還原，這只是模擬

            if (winner == symbol) {
                return pos;
            }
        }
    }
    return 0;   // 位置是 1~9，所以 0 可以代表「沒找到」
}

// 從候選位置中，隨機挑一個還是空格的；候選都被佔滿就回傳 0
int pick_random_from(char board[3][3], const int candidates[], int n) {
    int empty[9];
    int count = 0;

    for (int i = 0; i < n; i++) {
        int pos = candidates[i];
        int row = (pos - 1) / 3;
        int col = (pos - 1) % 3;
        if (board[row][col] == ' ') {
            empty[count] = pos;
            count++;
        }
    }

    if (count == 0) {
        return 0;
    }
    return empty[rand() % count];
}

// 電腦下棋（規則版）：電腦固定是 O，對手是 X
int computer_move(char board[3][3]) {
    int pos;

    // 規則 1：自己能贏就贏
    pos = find_winning_move(board, 'O');
    if (pos != 0) {
        return pos;
    }

    // 規則 2：對手下一手會贏，就擋住
    pos = find_winning_move(board, 'X');
    if (pos != 0) {
        return pos;
    }

    // 規則 3：中間是空的就佔中間（位置 5）
    if (board[1][1] == ' ') {
        return 5;
    }

    // 規則 4 和 5：先挑角落，角落都滿了才挑邊
    const int corners[] = {1, 3, 7, 9};
    const int edges[] = {2, 4, 6, 8};

    pos = pick_random_from(board, corners, 4);
    if (pos != 0) {
        return pos;
    }
    return pick_random_from(board, edges, 4);
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