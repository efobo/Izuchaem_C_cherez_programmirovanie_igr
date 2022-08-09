#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
    vector<string> commands = { "help", "show", "add", "delete", "quit" };
    vector<string> gamesLib;
    gamesLib.push_back("Everlasting Summer");
    gamesLib.push_back("Serious Sam 3");
    gamesLib.push_back("Sims");
    vector<string>::iterator myIterator;
    vector<string>::const_iterator iter;

    cout << "Hi! Welcome to my programm!\n";
    cout << "Write 'help' to see available commands\n";
    string userIO;

    do {
        cout << "\n> ";
        cin >> userIO;
        if (userIO == "help")
        {
            cout << "\nYou can use following commands:";
            for (iter = commands.begin(); iter < commands.end(); ++iter)
            {
                cout << "\n" << *iter;
            }
            continue;
        }
        else if (userIO == "show")
        {
            cout << "\nYour library:";
            for (iter = gamesLib.begin(); iter < gamesLib.end(); ++iter)
            {
                cout << "\n" << *iter;
            }
            continue;
        }
        else if (userIO == "add")
        {
            string newItem;
            cout << "Name of new item: ";
            cin >> newItem;
            gamesLib.push_back(newItem);
            continue;
        }
        else if (userIO == "delete")
        {
            string delItem;
            cout << "Name of item to delete: ";
            cin >> delItem;
            iter = find(gamesLib.begin(), gamesLib.end(), delItem);
            if (iter != gamesLib.end())
            {
                gamesLib.erase(iter);
                cout << "\nSuccessfully deleted!";
            }
            else
            {
                cout << "\nNothing was found";
            }
            continue;
        }
        else if (userIO == "quit")
        {
            cout << "\nBye!";
        }
        else
        {
            cout << "\nUnknown command";
            continue;
        }

    } while (userIO != "quit");


    return 0;
}