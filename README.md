English | [繁體中文](README.zh-TW.md)

# c-tic-tac-toe

A command-line tic-tac-toe game written in C, with a two-player mode and a computer opponent.

## Features

- Two modes: two players, or play against the computer
- Computer opponent with a rule-based strategy: it wins when it can, blocks your winning move, and prefers the center and corners
- Win and draw detection (rows, columns, and both diagonals)
- Input validation: rejects letters, numbers outside 1-9, and spots that are already taken
- Play again option after each game

## Requirements

- A C compiler such as `gcc`

## Build and Run

```bash
gcc -Wall -o tictactoe main.c
```

Run on Windows (PowerShell):

```powershell
.\tictactoe.exe
```

Run on macOS / Linux:

```bash
./tictactoe
```

## How to Play

Choose a mode at the start. Then pick a square by entering a number from 1 to 9:

```
 1 | 2 | 3
---+---+---
 4 | 5 | 6
---+---+---
 7 | 8 | 9
```

In computer mode, you play X (first) and the computer plays O.

## Example

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

## How the Computer Works

On its turn, the computer checks these rules in order and uses the first one that applies:

1. Take a winning move if there is one
2. Block the opponent's winning move
3. Take the center
4. Take a random corner
5. Take a random edge

It only looks one move ahead, so it is hard to beat but not unbeatable.

## What I Learned

- Two-dimensional arrays and converting between a 1-9 position and `[row][col]`
- Splitting code into functions
- Safe input handling with `scanf` and clearing the input buffer
- Simple rule-based game AI

## License

MIT