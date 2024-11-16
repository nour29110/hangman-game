#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // for rand and srand
#include <ctime>   // for time function
#include <unistd.h>  // for Mac

using namespace std;

// Constants for hangman body parts
const string HEAD = "(\"\")";
const string RARM = "\\";
const string LARM = "/";
const string BODY = "|";
const string LLEG = "/";
const string RLEG = " \\";
const int MAX_WORDS = 100; // Maximum number of words to read from the file

// Messages
const string FILE_ERROR_MESSAGE = "Error: Could not open words.txt";
const string WELCOME_MESSAGE = "Welcome to Hangman game!\n\n";
const string REPEAT_GUESS_MESSAGE = "You've already guessed this letter!\n";
const string CORRECT_GUESS_MESSAGE = "Correct guess!\n";
const string INCORRECT_GUESS_MESSAGE = "Incorrect guess!\n";
const string WIN_MESSAGE = "Congratulations! You've guessed the word: ";
const string LOSS_MESSAGE = "Game Over! The correct word was: ";

// Function prototypes
void drawBody(int numWrong);
string selectWord(const string dictionary[], int wordCount);
void displayProgress(const string& correctLetters);
bool isWordGuessed(const string& correctLetters);

int main() {
    // Load words from file
    ifstream file("words.txt");
    if (!file) {
        cerr << FILE_ERROR_MESSAGE << endl;
        return 1;
    }

    // Read words into dictionary array
    string dictionary[MAX_WORDS];
    int wordCount = 0;
    string word;
    while (file >> word && wordCount < MAX_WORDS) {
        dictionary[wordCount++] = word;
    }
    file.close();

    // Find the longest word length for maxGuesses
    int maxGuesses = 0;
    for (int i = 0; i < wordCount; i++) {
        if (dictionary[i].length() > maxGuesses) {
            maxGuesses = dictionary[i].length();
        }
    }

    // Initialize game variables
    srand(time(0)); // Seed for random number generation
    string selectedWord = selectWord(dictionary, wordCount);
    string correctLetters(selectedWord.length(), '_'); // Initialize with underscores
    string guessedLetters = ""; // Track guessed letters
    int numWrong = 0; // Wrong guesses counter
    string gameState = "playing";

    // Main game loop
    cout << WELCOME_MESSAGE;

    while (gameState == "playing") {
        drawBody(numWrong);
        displayProgress(correctLetters);

        // Display wrong letters guessed
        cout << "Wrong letters guessed: ";
        for (char c : guessedLetters) {
            cout << c << ' ';
        }
        cout << endl;

        // Prompt user for a guess
        char guess;
        cout << "Enter a letter: ";
        cin >> guess;
        guess = tolower(guess); // Convert guess to lowercase

        // Check if letter has already been guessed
        if (guessedLetters.find(guess) != string::npos) {
            cout << REPEAT_GUESS_MESSAGE;
            continue;
        }

        // Add guess to guessed letters
        guessedLetters += guess;

        // Check if guess is in the selected word
        bool correctGuess = false;
        for (size_t i = 0; i < selectedWord.size(); i++) {
            if (selectedWord[i] == guess) {
                correctLetters[i] = guess;
                correctGuess = true;
            }
        }

        // Display message based on guess accuracy
        cout << (correctGuess ? CORRECT_GUESS_MESSAGE : INCORRECT_GUESS_MESSAGE);

        if (!correctGuess) {
            numWrong++;
        }

        // Check game state
        if (numWrong == maxGuesses) {
            gameState = "lost";
        } else if (isWordGuessed(correctLetters)) {
            gameState = "won";
        }
    }

    // End of game message
    drawBody(numWrong);
    displayProgress(correctLetters);

    if (gameState == "won") {
        cout << WIN_MESSAGE << selectedWord << "\n";
    } else if (gameState == "lost") {
        cout << LOSS_MESSAGE << selectedWord << "\n";
    }

    return 0;
}

// Function to select a random word from the dictionary
string selectWord(const string dictionary[], int wordCount) {
    int index = rand() % wordCount;
    return dictionary[index];
}

// Function to display the current progress with guessed letters
void displayProgress(const string& correctLetters) {
    cout << "\nCurrent word: ";
    for (char c : correctLetters) {
        cout << c << ' ';
    }
    cout << "\n\n";
}

// Function to check if the word is fully guessed
bool isWordGuessed(const string& correctLetters) {
    return correctLetters.find('_') == string::npos;
}

// Function to display hangman body parts based on the number of wrong guesses
void drawBody(int numWrong) {
    string head = (numWrong > 0) ? HEAD : "  ";
    string leftArm = (numWrong > 1) ? LARM : " ";
    string body = (numWrong > 2) ? BODY : " ";
    string rightArm = (numWrong > 3) ? RARM : " ";
    string leftLeg = (numWrong > 4) ? LLEG : " ";
    string rightLeg = (numWrong > 5) ? RLEG : " ";

    string image = "########\n"
                   "#     " + head + "\n"
                   "#     " + leftArm + body + rightArm + "\n"
                   "#     " + leftLeg + " " + rightLeg + "\n"
                   "#\n################\n";
    cout << image << endl;

    // Pause for a moment
    sleep(1); // 1-second pause on Mac
}