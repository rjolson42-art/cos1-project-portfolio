// Portfolio Project.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "../h Files/CombatLogic.h"
#include <iostream>

int main()
{

    //header for application
    std::cout << "\n====================================\n";
    std::cout << "  WELCOME TO THE COMBAT SIMULATOR     \n";
    std::cout << "====================================\n";
    
    //CombatLogic object
    CombatLogic combatEngine(10, 10);

    //variables for menu selection
    int menuChoice = 0;
    std::string inputChoice;

    //initiating menu loop
    while (menuChoice != 3) {

        //listing menu options
        std::cout << "1. Start New Battle\n";
        std::cout << "2. View Instructions\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter and integer 1-3\n";
        std::cout << "Selection: ";

        //getting user input
        std::cin >> inputChoice;

        //attempting to convert string to int
        try {

            menuChoice = std::stoi(inputChoice);
        }
        catch (...) {

            //informing user input is invalid
            std::cout << "Input is not an integer. Please enter an integer to select a menu option.\n";
            
            //setting menu choice to 0 to continue menu loop
            menuChoice = 0;

            //returning to top of loop
            continue;
        }

        //switch to operate menu
        switch (menuChoice) {
        case 1:
            
            combatEngine.StartNewBattle();

            std::cout << "Combat logic to be added\n";
            break;

        case 2:
            
            //TODO: display instructions
            std::cout << "Instructions yet to be added\n\n";
            break;

        case 3:

            //informing user the application is exiting
            std::cout << "Exiting application. Goodbye!\n";
            break;

        default:

            //informing user input is out of range
            std::cout << "Selection is not a valid option. Please enter an integer between 1 and 3\n";
            break;
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
