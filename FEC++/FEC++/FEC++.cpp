// FEC++.cpp : This file contains the 'main' function. Program execution begins and ends there.

// Need to add code for outputting total cost, and list of visited towns with quantities

#include <iostream>

#include "myTools.h"
#include "db.h"
#include "Session.h"


// login function
// at the moment this function simply asks for a username input - the input only acts a placeholder
// for the user while they use the main feature of the program.
// accounts and passwords saved to the db are planned

std::string login()
{
    std::string username;
    
    std::cout << "Please enter a username: ";
    std::getline(std::cin, username);

    return username;
}

// menu function
// there is only 1 option
// still validates for an int
int menu()
{
    int convertedInput{ 0 };

    bool validInput{ false };
    // loop around menuy options 
    // so the user can retry the input until they input a valid integer
    while (!validInput)
    {

        // stores the raw input grabbed from cin
        std::string optionInput;
        // display the options to the user
        std::cout << "FEC++ options:\n"
            << "1: Calculate total cost from a delivery shift\n"
            << "2: Exit"
            << std::endl;
        std::getline(std::cin, optionInput);

        // validate raw input as a integer
        nsMyTools::TRetIntPair retIntPair = nsMyTools::stringToInt(optionInput);
        //extract contents to separate variables for readability
        nsMyTools::TSuccess operationSuccess{ retIntPair.first };
        convertedInput = retIntPair.second;

        // check if successful
        if (operationSuccess && 1 <= convertedInput && convertedInput <= 2) {
            validInput = true;
        }
        else {
            std::cout << "Invalid Entry, please try again\n" << std::endl;
        }

    }

    return convertedInput;

}


int start()
{
    std::string username{ login() };
    //std::string username{ "Test" };

    //main program loop
    bool running{ true };
    while (running)
    {
        std::cout << std::endl;
        int switchCase = menu();

        switch (switchCase)
        {
        case 1: // Run main feature
            nsInfo::totalCostCalculator(username);
            break;
        case 2: // Exit
            running = false;
            break;
        default:
            break;
        }
    }


    return 0;
}

int main()
{
    //std::cout << "Removed" << std::endl;

    start();
    
    return 0;
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
