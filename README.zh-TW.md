[English](README.md) | 繁體中文

# c-tic-tac-toe

用 C 語言寫的井字遊戲，有雙人模式，也有跟電腦玩的。

## 功能

- 兩種模式：雙人&電腦
- 電腦採用規則式策略：能贏就贏、會擋住你的下一步、優先佔中間和角落的位置
- 勝負與平手判斷（橫列、直行、兩條對角線）
- 輸入檢查：拒絕英文字母、超出 1 到 9 的數字，以及已經被佔用的格子
- 每局結束後可以選擇再玩一局

## 環境需求

- C 編譯器，例如 `gcc`

## 編譯與執行

```bash
gcc -Wall -o tictactoe main.c
```

Windows（PowerShell）執行：

```powershell
.\tictactoe.exe
```

macOS / Linux 執行：

```bash
./tictactoe
```

## 玩法

開始時先選擇模式，之後輸入 1 到 9 的數字來選格子：

```
 1 | 2 | 3
---+---+---
 4 | 5 | 6
---+---+---
 7 | 8 | 9
```

對電腦模式中，你是 X（先手），電腦是 O。

## 執行範例

程式的提示訊息是英文，所以範例輸出和英文版相同：

```
Select mode: 1) Two players  2) Play against computer: 2

   |   |   
---+---+---
   |   |   
---+---+---
   |   |   

Player X, choose a position (1-9): 1
Computer (O) chooses position 5.
...
 X | X | O 
---+---+---
 O | O | X 
---+---+---
 X | X | O 

It's a draw!
Play again? (y/n): n
Thanks for playing!
```

## 電腦怎麼下棋

輪到電腦時，它會依序檢查下面的規則，用第一條符合的：

1. 有能贏的一步就下那格
2. 擋住對手的致勝一步
3. 佔中間
4. 隨機佔一個角落
5. 隨機佔一個邊

它只會往前看一步，所以很難贏但不是無敵。

## 我學到了什麼

- 二維陣列，以及 1 到 9 的位置和 `[列][行]` 之間的換算
- 把程式拆成函式
- 用 `scanf` 安全地讀取輸入，並清除輸入緩衝區
- 簡單的rule-based AI

## 授權

MIT