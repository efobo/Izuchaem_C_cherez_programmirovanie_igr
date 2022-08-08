#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
    cout << "Come up with a secret number (1-100)\n";
    char answer = 'n';
    while (answer != 'y')
    {
        cout << "\nAre you ready?(y/n) ";
        cin >> answer;
    }

    srand(static_cast<unsigned int>(time(0)));
    int computerGuessNumber = rand() % 100 + 1;
    int highLimit = 100;
    int lowLimit = 1;

    do
    {
        cout << "\nIs " << computerGuessNumber << " your secret number?";
        cout << "\n\t1.You're right!";
        cout << "\n\t2.It's lower then mine";
        cout << "\n\t3.It's higher then mine";
        cout << "\nWrite the number of your answer, please (1-3): ";
        cin >> answer;

        switch (answer) {
        case '1':
            cout << "\nPerfect! Your secret number is " << computerGuessNumber;
            break;
        case '2':
            cout << "\nOK, let's guess further...";
            lowLimit = computerGuessNumber;
            computerGuessNumber = rand() % (highLimit - lowLimit) + lowLimit;
            break;
        case '3':
            cout << "\nOK, let's guess further...";
            highLimit = computerGuessNumber;
            computerGuessNumber = rand() % highLimit + lowLimit;
            break;
        default:
            cout << "\n Incorrect answer! ";
            cout << "You can only write numbers from 1 to 3.";
            continue;
        }

    } while (answer != '1');
    cout << "\nGame over!";
    return 0;
}

