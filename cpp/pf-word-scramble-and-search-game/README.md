# Word Scramble and Search Game

| **Course** | Programming Fundamentals (PF) |
| **Language** | C++ |
| **Type** | Console application |

A menu-based console game with two mini-games: unscrambling a set of jumbled words, and finding hidden words inside a 20x20 letter grid loaded from a file.

## Features
- **Word Scramble:** decode 4 scrambled words (umbrella, jacket, right, mango), with one hint allowed per word
- **Word Search:** find 5 hidden words (snake, ruler, better, caring, swing) in a 20x20 grid by entering start/end coordinates within 30 seconds
- Score increases for correct answers, decreases for wrong guesses or hints
- Score can be saved to a file and reloaded to show the last saved result
- Input checking: entering a non-numeric value where a number is expected ends the game safely

## How scoring works
- Correct word / correctly found word: +1
- Wrong word / wrong coordinates / already-used hint attempt: no repeat deduction, message shown
- Wrong guess or hint used: -1
- Score is never saved as negative (clamped to 0)

## Files
- `word_scramble_and_search_game.cpp`: the source code
- `wordgrid.txt`: the 20x20 letter grid used by the Word Search game (must stay in the same folder as the program)
- `savescore`: stores the last saved score from the Word Search game
- `scramblescore`: stores the last saved score from the Word Scramble game
- `Word_Scramble_and_Search_Game_Documentation.docx`: full project documentation

