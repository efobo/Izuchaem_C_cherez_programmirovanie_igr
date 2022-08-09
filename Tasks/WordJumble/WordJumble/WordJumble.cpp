// Игра Word Jumble
// Классическая игра-головоломка, в которой пользователь разгадывает слова. 
// С подсказками или без них

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    enum fields {WORD, HINT, NUM_FIELDS};
    const int NUM_WORDS = 5;
    const string WORDS[NUM_WORDS][NUM_FIELDS] =
    {
        {"wall", "Do you feel you're banging your head against something?"},
        {"glasses","These might help you see the answer"},
        {"labored", "Going slowly, is it?"},
        {"persistent", "Keep at it"},
        {"jumble","It's what the game is all about"}
    };

    int points = 0;

    char again = 'y';

    while (again != 'n')
    {
        srand(static_cast<unsigned int>(time(0)));
        int choice = (rand() % NUM_WORDS);
        string theWord = WORDS[choice][WORD]; // слово, которое нужно угадать
        string theHint = WORDS[choice][HINT]; // подсказка для слова

        string jumble = theWord; // перемешанный вариант
        int length = jumble.size();
        for (int i = 0; i < length; ++i)
        {
            int index1 = (rand() % length);
            int index2 = (rand() % length);
            char temp = jumble[index1];
            jumble[index1] = jumble[index2];
            jumble[index2] = temp;
        }

        cout << "\t\tWelcome to Word Jumble!\n\n";
        cout << "Unscramble the letters to make a word.\n";
        cout << "Enter 'hint' for a hint.\n";
        cout << "Enter 'quit' to quit the game\n\n";
        cout << "The jumble is: " << jumble;

        string guess;
        cout << "\n\nYour guess: ";
        cin >> guess;

        while ((guess != theWord) && (guess != "quit"))
        {
            if (guess == "hint")
            {
                cout << theHint;
                points -= 2;
            }
            else
            {
                cout << "Sorry, that's not it.";
            }
            cout << "\n\nYour guess: ";
            cin >> guess;
        }

        if (guess == theWord)
        {
            cout << "\nThat's it! You guessed it!";
            points += guess.size();
        }
        cout << "\nYour points: " << points;
        cout << "\nThanks for playing.";
       do
        {
            cout << "\nPlay again?(y/n) ";
            cin >> again;
       } while (again != 'y' && again != 'n');
       cout << "\n";
    }
    return 0;
}

