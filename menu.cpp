/**************************************************************************************
** Program name: menu.cpp
** Author: Michael Nutt
** Date: 10/14/2019
** Description: Definition of the menu functions. The menu functions determine whether
** to start a new game or exit the program, and define all necessary parameters for the
** game to run by prompting the user for their desired settings.
**************************************************************************************/

#include "menu.hpp"
#include "inputValidation.hpp"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

/* Summary: Prompts the user to either start the program or quit
 * Param: string program -> represents the title of the program; used to inform the user
 * as to which program they are starting
 * Return: boolean value representing the user's decision (true = start the program, false = quit)
 */
bool startMenu(string program)
{
    int selection;

    cout << endl
         << "Select one of the following options by entering the number representing your selection." << endl;
    cout << "1: Start program: " << program << "." << endl;
    cout << "2: Quit." << endl;

    // Validate input
    selection = convertInputToInt();

    // While the user enter's input other than 1 or 2:
    while (selection != 1 && selection != 2)
    {
        cout << "Invalid input. Please enter either 1 or 2." << endl;
        selection = convertInputToInt();
    }

    if (selection == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* Summary: Prompts the user to to enter a range of values to be used as game settings.
 * Param: string setting -> tells the user which setting they are selecting
 * Param: int minVal -> minimum allowable value
 * Param: int maxVal -> maximum allowable alue
 * Return: integer value representing the users choice
 */
int gameMenuRange(string setting, int minVal, int maxVal)
{
    int input;

    cout << endl
         << "Please select " << setting << " between " << minVal << " and " << maxVal << "." << endl;

    // Validate input
    input = convertInputToInt();

    // While the input is out of range
    while (input < minVal || input > maxVal)
    {
        cout << "Invalid input." << endl
             << "Please enter an integer between " << minVal << " and " << maxVal << "." << endl;

        // Re-validate input
        input = convertInputToInt();
    }

    return input;
}

/* Summary: Prompts the user to to enter select between two options.
 * Param: string setting -> tells the user which setting they are selecting
 * Param: string option1 -> first option
 * Param: string option2 -> second option
 * Return: integer value representing the users choice
 */
int gameMenuBinary(string setting, string option1, string option2)
{
    int input;

    cout << endl
         << setting << endl
         << option1 << endl
         << option2 << endl;

    // validate input
    input = convertInputToInt();

    // While input is invalid
    while (input != 1 && input != 2)
    {
        cout << "Invalid input." << endl
             << "Please select one of the following:" << endl
             << option1 << endl
             << option2 << endl;

        // revalidate input
        input = convertInputToInt();
    }

    return input;
}

/* Summary: Prompts the user to to enter select between three options.
 * Param: string setting -> tells the user which setting they are selecting
 * Param: string option1 -> first option
 * Param: string option2 -> second option
 * Param: string option3 -> third option
 * Return: integer value representing the users choice
 */
int gameMenuThreeOptions(string setting, string option1, string option2, string option3)
{
    int input;

    cout << endl
         << setting << endl
         << option1 << endl
         << option2 << endl
         << option3 << endl;

    // validate input
    input = convertInputToInt();

    // While input is invalid
    while (input != 1 && input != 2 && input != 3)
    {
        cout << "Invalid input." << endl
             << "Please select one of the following:" << endl
             << option1 << endl
             << option2 << endl
             << option3 << endl;

        // revalidate input
        input = convertInputToInt();
    }

    return input;
}