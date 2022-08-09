// Виселица
// Классическая игра "Виселица"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>

using namespace std;

const int MAX_WRONG = 8;// максимально допустимое кол-во ошибок
int wrong = 0;

char userGuess();
string check(string THE_WORD, char guess, string soFar);
void end(string THE_WORD);

int main()
{
    // подготовка
    vector<string> words;//подборка слов для загадывания
    words.push_back("GUESS");
    words.push_back("HANGMAN");
    words.push_back("DIFFICULT");
    srand(static_cast<unsigned int>(time(0)));
    random_shuffle(words.begin(), words.end());
    const string THE_WORD = words[0]; //слово для отгадывания
    string soFar(THE_WORD.size(), '-'); // часть слова, открытая на данный момент
    string used = ""; // уже отгаданные слова
    cout << "Welcome to Hangman. Good luck!\n";

    // основной цикл
    while ((wrong < MAX_WRONG) && (soFar != THE_WORD))
    {
        cout << "\n\nYou have " << (MAX_WRONG - wrong);
        cout << " incorrect guesses left\n";
        cout << "\nYou've used the following letters:\n" << used << endl;
        cout << "\nSo far, the word is:\n" << soFar << endl;
        char guess = userGuess();

        while (used.find(guess) != string::npos)
        {
            cout << "\nYou've already guessed " << guess << endl;
            guess = userGuess();
        }
        used += guess;
        soFar = check(THE_WORD, guess, soFar);
    }

    // конец игры
    end(THE_WORD);

    return 0;
}

char userGuess()
{
    char guess;
    cout << "\n\nEnter your guess: ";
    cin >> guess;
    guess = toupper(guess); // перевод в верхний регистр
    // т.к. загаданное слово записано в верхнем регистре
    return guess;
}

string check(string THE_WORD, char guess, string soFar)
{
    if (THE_WORD.find(guess) != string::npos)
    {
        cout << "That's right! " << guess << " is in the word.\n";

        //Обновить переменную soFar, включив в нее новую угаданную букву
        for (int i = 0; i < THE_WORD.length(); ++i)
        {
            if (THE_WORD[i] == guess)
            {
                soFar[i] = guess;
            }
        }
    }
    else
    {
        cout << "Sorry, " << guess << " isn't in the word.\n";
        ++wrong;
    }
    return soFar;
}

void end(string THE_WORD)
{
    if (wrong == MAX_WRONG)
    {
        cout << "\nYou've been hanged!";
    }
    else
    {
        cout << "\nYou've guessed it!";
    }
    cout << "\nThe word was " << THE_WORD << endl;
}


