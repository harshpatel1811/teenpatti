#include "game.hpp"
#include "functions.hpp"

using namespace std;

int main()
{
    functions fun;
    srand(unsigned(time(0)));
    Game g;
    Player* player;
    int balance = 10000;
    Player* winner_player;

    int choice;
    do
    {
        fun.clear_screen();
        cout << "Welcome to the teen-Patti\n";
        cout << "x-------------------------x\n\n";
        //cout << "Money Balance (" <<balance<< ")\n";
        cout << "(1)->Start the Game\n";
        cout << "(2)->Quit the Game\n";
        cout << "choice: ";
        cin >> choice;

        if(choice == 1)
        {
            fun.clear_screen();
            std::cout << "Serving Cards...\n\n";
            std::cout << "\tCPU1 = (🃏🃏🃏)\n";
            fun.sleepcp(200);
            std::cout << "\tCPU2 = (🃏🃏🃏)\n";
            fun.sleepcp(200);
            std::cout << "\tCPU3 = (🃏🃏🃏)\n";
            fun.sleepcp(200);
            std::cout << "\tCPU4 = (🃏🃏🃏)\n\n";
            fun.sleepcp(200);
            fun.clear_screen();
            player = g.Init();
            g.Window(player);

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

        } 
    }
    while(choice != 2);
}