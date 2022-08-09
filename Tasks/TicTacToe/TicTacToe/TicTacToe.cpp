// Программа Крестики-нолики
// Компьютер играет в "Крестики-нолики" против пользователя

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// глобальные константы
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

// прототипы функций
void instructions();
char askYesNo(string question);
int askNumber(string question, int high, int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(const vector<char>* const board);
char winner(const vector<char>* const board);
bool isLegal(int move, const vector<char>* const board);
int humanMove(const vector<char>* const board, char human);
int computerMove(vector<char>* const board, char computer);
void announceWinner(char winner, char computer, char human);


int main()
{
    int move;
    const int NUM_SQUARES = 9;
    vector<char> board(NUM_SQUARES, EMPTY);
    instructions();

    char human = humanPiece();
    char computer = opponent(human);

    char turn = X;
    displayBoard(&board);

    while (winner(&board) == NO_ONE)
    {
        if (turn == human)
        {
            move = humanMove(&board, human);
            board[move] = human;
        }
        else
        {
            move = computerMove(&board, computer);
            board[move] = computer;
        }
        displayBoard(&board);
        turn = opponent(turn);
    }
    announceWinner(winner(&board), computer, human);
    return 0;
}

/*
Отображает правила игры
*/
void instructions()
{
    cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";
    cout << "--where human brain is pit against silicon processor\n\n";
    cout << "Make yourmove known by entering a number, 0-8. The number\n";
    cout << "corresponds to the desired board position as illustrated:\n\n";
    cout << " 0 | 1 | 2 \n";
    cout << " --------- \n";
    cout << " 3 | 4 | 5 \n";
    cout << " --------- \n";
    cout << " 6 | 7 | 8 \n";
    cout << "Prepare yourself, human. The battle is about to begin.\n\n";

}

/*
Задает вопрос, предполагающий "да" или "нет".
Получает вопрос.
Возвращает символ y или n.
*/
char askYesNo(string question)
{
    char response;
    do
    {
        cout << question << " (y/n): ";
        cin >> response;
    } while (response != 'y' && response != 'n');

    return response;
}

/*
Запрашивает число из диапазона. Получает вопрос, малое число
и большое число. Возвращает число из диапазона от low до high
*/
int askNumber(string question, int high, int low)
{
    int number;
    do
    {
        cout << question << " (" << low << " - " << high << "): ";
        cin >> number;
    } while (number > high || number < low);
    return number;
}

/*
Определяет, какими фигурами будет ходить пользователь.
Возвращает X или O
*/
char humanPiece()
{
    char go_first = askYesNo("Do you require the first move?");
    if (go_first == 'y')
    {
        cout << "\nThen take the first move. You will need it.\n";
        return X;
    }
    else
    {
        cout << "\nYour bravery will be your undoing... I will go first.\n";
        return O;
    }
}

/*
Зная, какими фигурами будет ходить пользователь, определяет
фигуру для компьютера. Получает X или O. Возвращает X или O
*/
char opponent(char piece)
{
    if (piece == X)
    {
        return O;
    }
    else
    {
        return X;
    }
}

/*
Отображает поле на экране. Получает поле.
*/
void displayBoard(const vector<char>* const board)
{
    cout << "\n\t" << (*board)[0] << " | " << (*board)[1] << " | " << (*board)[2];
    cout << "\n\t---------";
    cout << "\n\t" << (*board)[3] << " | " << (*board)[4] << " | " << (*board)[5];
    cout << "\n\t---------";
    cout << "\n\t" << (*board)[6] << " | " << (*board)[7] << " | " << (*board)[8];
    cout << "\n\n";
}

/*
Определяет победитель игры. Получает поле. Возвращает символ X,
или O, или T (этот случай соответствует ничьей), или N(означает, 
что пока у обоих соперников остаются шансы на победу)
*/
char winner(const vector<char>* const board)
{
    // все возможные выигрышные ряды
    const int WINNING_ROWS[8][3] = { {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6} };

    const int TOTAL_ROWS = 8;
    // если в 1 из выигрышных рядов уже присутствуют 3 одинаковых значения
    // (причем они не равны EMPTY), то победитель определился
    for (int row = 0; row < TOTAL_ROWS; ++row)
    {
        if (((*board)[WINNING_ROWS[row][0]] != EMPTY) &&
            ((*board)[WINNING_ROWS[row][0]] == (*board)[WINNING_ROWS[row][1]]) &&
            ((*board)[WINNING_ROWS[row][1]] == (*board)[WINNING_ROWS[row][2]]))
        {
            return (*board)[WINNING_ROWS[row][0]];
        }
    }
    // поскольку победитель не определился, проверяем, не наступила ли ничья
    // (остались ли на поле пустые клетки)
    if (count((*board).begin(), (*board).end(), EMPTY) == 0)
    {
        return TIE;
    }

    // Поскольку победитель не определился, но ничья еще не наступила,
    // игра продолжается
    return NO_ONE;
}


/*
Определяет, по правилам ли сделан ход. Получает поле и ход.
Возвращает true или false.
*/
inline bool isLegal(int move, const vector<char>* const board)
{
    return ((*board)[move] == EMPTY);
}


/*
Узнает ход пользователя. Получает поле и фигуру, которой ходит 
пользователь. Возвращает ход пользователя.
*/
int humanMove(const vector<char>* const board, char human)
{
    int move = askNumber("Where will you move?", ((*board).size() - 1));
    while (!isLegal(move, board))
    {
        cout << "\nThat square is already occupied, follish human.\n";
        move = askNumber("Where will you move?", ((*board).size() - 1));
    }
    cout << "Fine...\n";
    return move;
}


/*
Узнает ход компьютера. Получает поле и фигуру, которой
ходит компьютер. Возвращает ход компьютера.
*/
int computerMove(vector<char>* const board, char computer)
{
    unsigned int move = 0;
    bool found = false;
    // если компьютер может выиграть следующим ходом, то он делает этот ход
    while (!found && move < (*board).size())
    {
        if (isLegal(move, board))
        {
            (*board)[move] = computer;
            found = winner(board) == computer;
            (*board)[move] = EMPTY;
        }
        if (!found)
        {
            ++move;
        }
    }

    // иначе, если человек может победить следующим ходом, блокировать этот ход
    if (!found)
    {
        move = 0;
        char human = opponent(computer);
        while (!found && move < (*board).size())
        {
            if (isLegal(move, board))
            {
                (*board)[move] = human;
                found = winner(board) == human;
                (*board)[move] = EMPTY;
            }
            if (!found)
            {
                ++move;
            }
        }
    }

    // иначе занять следующим ходом оптимальную свободную клетку
    if (!found)
    {
        move = 0;
        unsigned int i = 0;
        const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
        // выбрать оптимальную свободную клетку
        while (!found && i < (*board).size())
        {
            move = BEST_MOVES[i];
            if (isLegal(move, board))
            {
                found = true;
            }
            ++i;
        }
    }
    cout << "I shall take square number " << move << endl;
    return move;
}


/*
Поздравляет победителя или объявляет ничью. Получает победившую
сторону, фигуру, которой ходил пользователь, и фигуру,
которой ходил пользователь, и фигуру, которой ходил
компьютер.

*/
void announceWinner(char winner, char computer, char human)
{
    if (winner == computer)
    {
        cout << winner << "'s won!\n";
        cout << "As I predicted, human. I am triumphant once more -- proof\n";
        cout << "that computers are superior to humans in all regards\n";
    }
    else if (winner == human)
    {
        cout << winner << "'s won!\n";
        cout << "No, no! It cannot be! Somehow you tricked me, human\n";
        cout << "But never again! I, the computer, so swear it!\n";
    }
    else
    {
        cout << "It's a tie\n";
        cout << "You were most lucky, human, and somehow managed to tie me\n";
        cout << "Celebrate...for this is the best you will ever achieve\n";
    }
}