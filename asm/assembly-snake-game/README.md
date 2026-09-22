# Snake Game

| **Course** | Computer Organization and Assembly Language (COAL) |
| **Language** | x86 Assembly (MASM, 8086, DOS) |
| **Type** | Real-time console game |

The classic Snake arcade game written entirely in 8086 assembly for DOS. The snake, food and walls are drawn straight into text-mode video memory at `B800h`, the game runs on a counted-delay loop, and the arrow keys are read without blocking so the snake stays responsive. Everything lives in a single `.asm` file with no libraries.

## Features
- **Direct video-memory graphics:** every cell is written to `B800h` as a character + colour-attribute pair, so the board is drawn by hand with no BIOS text calls in the play field
- **Real-time game loop:** speed is paced by a counted delay loop of nested decrements, with the keyboard polled during the wait
- **Non-blocking input:** `INT 16h` service `01h` checks for a key and `00h` reads it, so movement never freezes the game
- **Growing snake:** eating food lengthens the body by one and raises the score; the snake is stored as two parallel byte arrays (head at index 0)
- **Collision detection:** hitting a wall or the snake's own body ends the game
- **No 180-degree turns:** direction changes are buffered per tick and a reversal into the neck is rejected
- **Pseudo-random food:** a 16-bit linear-congruential generator, seeded from the BIOS tick counter, places food on a free cell
- **Flicker-free rendering:** only the cells that change (new head, vacated tail) are redrawn each tick
- **Score display:** numbers are converted to ASCII by repeated division by 10 using the stack
- **Game over + replay:** banner with the final score; press `R` to play again or any other key to exit to DOS

## Controls
- **Arrow keys** - steer the snake
- **Esc** - quit the current game
- **R / Enter** - play again after game over

## How it works
- **`plot`** turns a (row, column) into the byte offset `(row*80 + column)*2` and writes the character/attribute word to `B800h`; all drawing is built on it.
- **Main loop:** apply the buffered direction -> compute the new head -> test walls and body -> grow if on food -> shift every segment toward the tail and install the new head -> erase the vacated tail -> wait one speed interval while polling keys.
- **Procedures** (`moveSnake`, `checkCollide`, `placeFood`, `itoa`, `delay`, `handleInput`, ...) each do one job and save/restore the registers they use with `push`/`pop`.

## Files
- `snake_game.asm`: the complete game source (MASM / 8086 / DOS)
- `Snake_Game_Documentation.docx`: full project documentation

