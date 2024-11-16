# Hangman Game

## Overview
This is a simple implementation of the Hangman game in C++. The game selects a random word from a dictionary of words stored in a file and challenges the player to guess it by suggesting letters within a limited number of attempts. The game includes a visual representation of the hangman figure that updates with each wrong guess.

## Features
- **Random Word Selection**: The game picks a random word from a predefined list of words stored in a text file (`words.txt`).
- **Interactive Gameplay**: Players input their guesses, and the game responds with feedback on whether the guess was correct or incorrect.
- **Hangman Figure**: As players make incorrect guesses, a hangman figure is drawn to show the progress of the game.
- **Win/Loss Conditions**: The game ends when the player either guesses the word correctly or exhausts their allowed number of incorrect guesses.

## How to Play
1. The game will present a series of underscores representing the letters of the word.
2. The player guesses one letter at a time.
3. If the guess is correct, the corresponding letters in the word are revealed.
4. If the guess is incorrect, a part of the hangman is drawn.
5. The game continues until the word is guessed or the hangman figure is fully drawn.

## Game Mechanics
- The player is allowed to guess a letter repeatedly.
- The maximum number of wrong guesses is determined by the length of the longest word in the dictionary file.
- The game is played in a loop where the player continues to guess until either they win or lose.

## Instructions to Run
1. Make sure you have a C++ compiler installed (e.g., GCC or Clang).
2. Create a `words.txt` file with a list of words (one word per line).
3. Compile the program using the command:
   ```bash
   g++ main.cpp -o hangman
