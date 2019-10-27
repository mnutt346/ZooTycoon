/**************************************************************************************
** Program name: zoo.cpp
** Author: Michael Nutt
** Date: 10/16/2019
** Description: Implementation file for the Zoo class. The Zoo class defines the logical
** flow and tracks the state of the game. 
**************************************************************************************/

#include <random>
#include <iostream>
#include <iomanip>
#include "zoo.hpp"
#include "cstdlib"
#include "menu.hpp"
#include "randomNum.hpp"
#include "string"

using std::cin;
using std::cout;
using std::endl;
using std::exit;
using std::fixed;
using std::setprecision;
using std::string;

const double BASE_FOOD = 10.00;
const double TIGER_COST = 10000.00;
const double PENGUIN_COST = 1000.00;
const double TURTLE_COST = 100;
const int TIGER_BABIES = 1;
const int PENGIUN_BABIES = 5;
const int TURTLE_BABIES = 10;
const double TIGER_FOOD_MULTIPLIER = 5.00;
const double PENGIUN_FOOD_MULTIPLIER = 1.00;
const double TURTLE_FOOD_MULTIPLIER = 0.50;
const double TIGER_PAY_MULTIPLIER = 0.20;
const double PENGUIN_PAY_MULTIPLIER = 0.10;
const double TURTLE_PAY_MULTIPLIER = 0.05;

/*
 * Summary: Zoo default constructor creates arrays for each animal and initializes
 * all elements to NULL
 * Param: N/A
 * Return: N/A
 */
Zoo::Zoo()
{
    tigers = new Animal *[10];
    penguins = new Animal *[10];
    turtles = new Animal *[10];
    bank = 100000;
    dailyBonus = 0.00;
    maxTigers = 10;
    maxPenguins = 10;
    maxTurtles = 10;

    // Initialize all animal arrays to NULL
    for (int i = 0; i < 10; i++)
    {
        tigers[i] = NULL;
        penguins[i] = NULL;
        turtles[i] = NULL;
    }
}

/*
 * Summary: Defines the logical flow of the game and tracks its current state.
 * Param: N/A
 * Return: N/A
 */
void Zoo::play()
{
    const string TITLE = "Zoo Tycoon";
    const int MIN_ANIMALS = 1;
    const int MAX_ANIMALS = 2;
    const int MAX_DAYS = 50;

    // Prompt user to either play the game or quit
    int programSelection = startMenu(TITLE);

    while (programSelection)
    {
        int currentDay = 1;
        double dailyFoodExpense = 0.00;
        double dailyAnimalPayoff = 0.00;
        double dailyProfit = 0.00;

        // Prompt user to purchase starting tigers
        buyStartingTigers();

        // Prompt user to purhcase starting penguins
        buyStartingPenguins();

        // Prompt user to purhcase starting turtles
        buyStartingTurtles();

        while (currentDay <= MAX_DAYS)
        {
	    dailyBonus = 0;
		
            cout << "__________________________________" << endl
                 << "***** Day " << currentDay << " *****" << endl;

            // Increase age of all animals
            incrementAges();

            // Calculate expenses
            dailyFoodExpense = calcFoodCost();

            // Reduce bank value for expense amount
            manageBank(-dailyFoodExpense);

            // Execute random event
            executeRandomEvent();

            // Print number of each type of animal
            cout << endl;
            printTigers();
            printPenguins();
            printTurtles();

            // Calculate animal payoff
            dailyAnimalPayoff = calcAnimalPayoff();

            // Calculate profit
            dailyProfit = calcDailyProfit(dailyAnimalPayoff, dailyFoodExpense, dailyBonus);

            // Add animal payoff and any bonuses to the bank
            manageBank((dailyAnimalPayoff + dailyBonus));

            // Print daily details
            cout << "Results: " << endl
                 << "Payoff from animals today: $" << dailyAnimalPayoff << endl
                 << "Food expenses for the day: $(" << dailyFoodExpense << ")" << endl
                 << "Bonuses for the day: $" << dailyBonus << endl
                 << "=================" << endl
                 << "Profit for today: $" << dailyProfit << endl
                 << "Current bank balance: $" << getBankValue() << endl
                 << endl;

            // If the user is out of money	
	    if (getBankValue() <= 0)
	    {
	      // Tell them the game is over and exit the current game
              cout << "Oh no! The zoo has gone bankrupt!" << endl
                   << "----- GAME OVER -----" << endl;
              break;
            }


            // Prompt the user to purchase an adult animal
            int purchaseOption = gameMenuBinary("Would you like to purchase an adult animal?", "1. Yes", "2. No");

            // If the user decides to purchase an animal
            if (purchaseOption == 1)
            {
                int animalSelection = gameMenuThreeOptions("Select one animal to purchase: ", "1. Tiger", "2. Penguin", "3. Turtle");

                // Purchase the selected animal
                purchaseAnimal(animalSelection);

                cout << "Your remaining bank balance is: $" << getBankValue() << endl;
            }

            // Prompt the player to continue playing or quit, and increment the day
            int continuePrompt = gameMenuBinary("Continue playing?", "1. Yes", "2. Get me outta here!");
            currentDay++;
            if (continuePrompt == 2)
            {
                exit(0);
            }
        }

        programSelection = startMenu(TITLE);
    }
    
    deallocateMemory();
}

/*
 * Summary: Gives the current value of the user's bank
 * Param: N/A
 * Return: double value representing the value of the user's bank
 */
double Zoo::getBankValue()
{
    return this->bank;
}

/*
 * Summary: Adds or subtracts the given amount from the user's bank
 * Param: double amount => represents the amount to be added or subtracted
 * Return: N/A
 */
void Zoo::manageBank(double amount)
{
    this->bank += amount;
}

/*
 * Summary: Prompts the user to purchase either 1 or 2 tigers. Adds one or two
 * tigers to the zoo and reduces the bank value by the cost of the tigers purchased
 * Param: N/A
 * Return: N/A
 */
void Zoo::buyStartingTigers()
{
    cout << endl
         << fixed << setprecision(2)
         << "Tigers cost $" << TIGER_COST << ". You currently have $" << getBankValue() << " remaining." << endl;

    int startTigers = gameMenuBinary("Please select how many tigers you wish to start with:", "* 1 Tiger", "* 2 Tigers");

    if (startTigers == 1)
    {
        // Reduce the bank value by the purchase price of a tiger
        manageBank(-(TIGER_COST));

        // Print the results of the transaction
        cout << "You have purchased one tiger for $" << TIGER_COST << "." << endl
             << "You have $" << getBankValue() << " remaining." << endl;

        // Add one new tiger to the zoo
        addTiger(new Tiger());
    }
    else
    {
        // Reduce the bank value by the purchase price of two tigers
        manageBank(-(TIGER_COST * 2));

        // Print the results of the transaction
        cout << "You have purchased two tigers for $" << TIGER_COST * 2 << "." << endl
             << "You have $" << getBankValue() << " remaining." << endl;

        // Add two new tigers to the zoo
        addTiger(new Tiger());
        addTiger(new Tiger());
    }
}

/*
 * Summary: Prompts the user to purchase either 1 or 2 penguins. Adds one or two
 * penguins to the zoo and reduces the bank value by the cost of the penguins purchased
 * Param: N/A
 * Return: N/A
 */
void Zoo::buyStartingPenguins()
{
    cout << endl
         << fixed << setprecision(2)
         << "Pengiuns cost $" << PENGUIN_COST << ". You currently have $" << getBankValue() << " remaining." << endl;

    int startPenguins = gameMenuBinary("Please select how many penguins you wish to start with:", "* 1 Penguin", "* 2 Penguins");

    if (startPenguins == 1)
    {
        // Reduce the bank value by the purchase price of a penguin
        manageBank(-(PENGUIN_COST));

        // Print the results of the transaction
        cout << "You have purchased one penguin for $" << PENGUIN_COST << "." << endl
             << "You have $" << getBankValue() << " remaining." << endl;

        // Add one new penguin to the zoo
        addPenguin(new Penguin());
    }
    else
    {
        // Reduce the bank value by the purchase price of two penguins
        manageBank(-(PENGUIN_COST * 2));

        // Print the results of the transaction
        cout << "You have purchased two penguins for " << PENGUIN_COST * 2 << "." << endl
             << "You have $" << getBankValue() << " remaining." << endl;

        // Add two new penguins to the zoo
        addPenguin(new Penguin());
        addPenguin(new Penguin());
    }
}

/*
 * Summary: Prompts the user to purchase either 1 or 2 turtles. Adds one or two
 * turtles to the zoo and reduces the bank value by the cost of the turtles purchased
 * Param: N/A
 * Return: N/A
 */
void Zoo::buyStartingTurtles()
{
    cout << endl
         << fixed << setprecision(2)
         << "Turtles cost $" << TURTLE_COST << ". You currently have $" << getBankValue() << " remaining." << endl;

    int startTurtles = gameMenuBinary("Please select how many turtles you wish to start with:", "* 1 Turtle", "* 2 Turtles");

    if (startTurtles == 1)
    {
        // Reduce the bank value by the purchase price of a turtle
        manageBank(-(TURTLE_COST));

        // Print the results of the transaction
        cout << "You have purchased one turtle for $" << TURTLE_COST << "." << endl
             << "You have $" << getBankValue() << " remaining." << endl;

        // Add one new turtle to the zoo
        addTurtle(new Turtle());
    }
    else
    {
        // Reduce the bank value by the purchase price of two turtles
        manageBank(-(TURTLE_COST * 2));

        // Print the results of the transaction
        cout << "You have purchased two turtles for " << TURTLE_COST * 2 << "." << endl
             << "You have $" << getBankValue() << " remaining." << endl;

        // Add two new turtles to the zoo
        addTurtle(new Turtle());
        addTurtle(new Turtle());
    }
}

/*
 * Summary: Checks whether more space must be allocated, then adds the given
 * tiger to the zoo.
 * Param: N/A
 * Return: N/A
 */
void Zoo::addTiger(Animal *animal)
{
    // If the tigers array is full
    if (speciesIsFull(tigers, maxTigers))
    {
        increaseSize(tigers, maxTigers);
    }

    int currentTigerIndex = 0;

    // Implemented using while-loop since the use of "break" is prohibited
    // Iterate through the array of Tigers until the last Tiger is found
    while (tigers[currentTigerIndex] != NULL)
    {
        ++currentTigerIndex;
    }

    // Add the new Tiger to the next available index
    tigers[currentTigerIndex] = animal;
}

/*
 * Summary: Checks whether more space must be allocated, then adds the given
 * penguin to the zoo.
 * Param: N/A
 * Return: N/A
 */
void Zoo::addPenguin(Animal *animal)
{
    // If the penguins array is full
    if (speciesIsFull(penguins, maxPenguins))
    {
        increaseSize(penguins, maxPenguins);
    }

    int currentPenguinIndex = 0;

    // Implemented using while-loop since the use of "break" is prohibited
    // Iterate through the array of Penguins until the last Penguin is found
    while (penguins[currentPenguinIndex] != NULL)
    {
        ++currentPenguinIndex;
    }

    // Add the new Penguin to the next available index
    penguins[currentPenguinIndex] = animal;
}

/*
 * Summary: Checks whether more space must be allocated, then adds the given
 * turtle to the zoo.
 * Param: N/A
 * Return: N/A
 */
void Zoo::addTurtle(Animal *animal)
{
    // If the turtles array is full
    if (speciesIsFull(turtles, maxTurtles))
    {
        increaseSize(turtles, maxTurtles);
    }

    int currentTurtleIndex = 0;

    // Implemented using while-loop since the use of "break" is prohibited
    // Iterate through the array of Turtles until the last Turtle is found
    while (turtles[currentTurtleIndex] != NULL)
    {
        ++currentTurtleIndex;
    }

    // Add the new Turtle to the next available index
    turtles[currentTurtleIndex] = animal;
}

/*
 * Summary: Determines wheter more memory needs to be allocated to a specific
 * animal array
 * Param: Animal **animal => a pointer to an array of animal objects
 * Param: int animalCount => the current size of the animal array
 * Return: bool value representing whether an array is full
 */
bool Zoo::speciesIsFull(Animal **animal, int animalCount)
{
    // for each element in the array of animals:
    for (int i = 0; i < animalCount; i++)
    {
        // If the element is points to NULL
        if (animal[i] == NULL)
        {
            return false;
        }
    }
    return true;
}

/*
 * Summary: Makes a new array that is twice the size of the one passed in, copies the
 * values of the old array into the new array, deallocates the memory used by the old
 * array, and doubles the previous variable used to track the size of the array.
 * Param: Animal **&animals -> a pointer to the reference for the dynamic array used to
 * store the animals
 * Param: int &animalCount -> a reference to the integer value used to track the number
 * of animals in a given array 
 * Return: N/A
 */
void Zoo::increaseSize(Animal **&animals, int &animalCount)
{
    int doubleCount = animalCount * 2;
    // Create a new dynamic array of animals twice the size of the previous
    Animal **moreAnimals = new Animal *[doubleCount];

    // Initialize all elements to NULL
    for (int i = 0; i < doubleCount; i++)
    {
        moreAnimals[i] = NULL;
    }

    // Copy elements of previous array
    for (int i = 0; i < animalCount; i++)
    {
        moreAnimals[i] = animals[i];
    }

    // delete previous array
    delete[] animals;

    // re-assign the original array to the new, larger array
    animals = moreAnimals;

    // increase the total animal count to the new amount
    animalCount = doubleCount;
}

/*
 * Summary: Counts and prints the current number of tigers in the zoo
 * Param: N/A
 * Return: N/A
 */
void Zoo::printTigers()
{
    int tigerCount = 0;
    int animalIndex = 0;

    // While there are tigers:
    while (tigers[animalIndex] != NULL)
    {
        // Increment tigerCount and the current index
        tigerCount++;
        animalIndex++;
    }

    cout << "Tigers remaining: " << tigerCount << endl;
}

/*
 * Summary: Counts and prints the current number of penguins in the zoo
 * Param: N/A
 * Return: N/A
 */
void Zoo::printPenguins()
{
    int penguinCount = 0;
    int animalIndex = 0;

    // While there are penguins:
    while (penguins[animalIndex] != NULL)
    {
        // Increment penguinCount and the current index
        penguinCount++;
        animalIndex++;
    }

    cout << "Penguins remaining: " << penguinCount << endl;
}

/*
 * Summary: Counts and prints the current number of turtles in the zoo
 * Param: N/A
 * Return: N/A
 */
void Zoo::printTurtles()
{
    int turtleCount = 0;
    int animalIndex = 0;

    // While there are turtles:
    while (turtles[animalIndex] != NULL)
    {
        // Increment turtleCount and the current index
        turtleCount++;
        animalIndex++;
    }

    cout << "Turtles remaining: " << turtleCount << endl;
}

/*
 * Summary: Increases the ages of all animals in the zoo by 1 day
 * Param: N/A
 * Return: N/A
 */
void Zoo::incrementAges()
{
    int currentAnimal = 0;

    // while a tiger exists
    while (tigers[currentAnimal] != NULL)
    {
        tigers[currentAnimal]->incrementAge();
        currentAnimal++;
    }

    // reset index to 0
    currentAnimal = 0;

    // while a penguin exists
    while (penguins[currentAnimal] != NULL)
    {
        penguins[currentAnimal]->incrementAge();
        currentAnimal++;
    }

    // reset index to 0;
    currentAnimal = 0;

    // while a turtle exists
    while (turtles[currentAnimal] != NULL)
    {
        turtles[currentAnimal]->incrementAge();
        currentAnimal++;
    }
}

/*
 * Summary: Calculates the total food costs for all animals
 * Param: N/A
 * Return: double value representing the total food costs for all animals
 */
double Zoo::calcFoodCost()
{
    double total = 0.00;
    int currentAnimal = 0;

    while (tigers[currentAnimal] != NULL)
    {
        total += tigers[currentAnimal]->getBaseFoodCost();
        currentAnimal++;
    }

    currentAnimal = 0;

    while (penguins[currentAnimal] != NULL)
    {
        total += penguins[currentAnimal]->getBaseFoodCost();
        currentAnimal++;
    }

    currentAnimal = 0;

    while (turtles[currentAnimal] != NULL)
    {
        total += turtles[currentAnimal]->getBaseFoodCost();
        currentAnimal++;
    }

    return total;
}

/*
 * Summary: Randomly selects an event to be executed
 * Param: N/A
 * Return: N/A
 */
void Zoo::executeRandomEvent()
{
    int randomEvent = randomNum(1, 3);

    switch (randomEvent)
    {
    // Sickness occurs
    case 1:
        cout << "An animal has gotten sick and must be quarantined!" << endl;
        diseaseOutbreak();
        break;

    // Boost in attendance
    case 2:
        cout << "There has been a boom in attendance!" << endl;
        generateBonus();
        break;

    // A baby is born
    case 3:
        babyBorn();
        break;
    }
}

/*
 * Summary: Randomly selects an animal to remove from the zoo
 * Param: N/A
 * Return: N/A
 */
void Zoo::diseaseOutbreak()
{
    int randomAnimal = randomNum(1, 3);
    
    if (checkForAnimals())
    {
              
    switch (randomAnimal)
    {
    case 1:
        // If there are no tigers
        if (tigers[0] == NULL)
        {
            // call diseaseOutbreak again
            diseaseOutbreak();
            break;
        }
        else
        {
            // Otherwise, remove a tiger from the zoo
            cout << "A tiger has been removed from the zoo and quarantined." << endl;
            quarantineAnimal(1);
        }
        break;

    case 2:
        // If there are no penguins
        if (penguins[0] == NULL)
        {
            // call diseaseOutbreak again
            diseaseOutbreak();
            break;
        }
        else
        {
            // Otherwise, remove a penguin from the zoo
            cout << "A penguin has been removed from the zoo and quarantined." << endl;
            quarantineAnimal(2);
        }
        break;
    case 3:
        // If there are no turtles
        if (turtles[0] == NULL)
        {
            // Call disease outbreak again
            diseaseOutbreak();
            break;
        }
        else
        {
            // Otherwise, remove a turtle from the zoo
            cout << "A turtle has been removed from the zoo and quarantined." << endl;
            quarantineAnimal(3);
        }
        break;
    }
  }
  else
  {
    cout << "No animals left in the zoo..." << endl;
  }
}

/*
 * Summary: Removes the given animal from the zoo
 * Param: N/A
 * Return: N/A
 */
void Zoo::quarantineAnimal(int animal)
{
    int currentAnimal = 0;
    // 1 => tigers, 2 => penguins, 3 => turtles
    switch (animal)
    {
    case 1:
        // while not the last tiger in tigers
        while (tigers[currentAnimal] != NULL)
        {
            currentAnimal++;
        }
        // delete and dereference the last tiger in tigers
        delete tigers[currentAnimal - 1];
        tigers[currentAnimal - 1] = NULL;
        break;
    case 2:
        // while not the last penguin in penguins
        while (penguins[currentAnimal] != NULL)
        {
            currentAnimal++;
        }

        // delete and dereference the last penguin in penguins
        delete penguins[currentAnimal - 1];
        penguins[currentAnimal - 1] = NULL;
        break;
    case 3:
        // while not the last turtle in turtles
        while (turtles[currentAnimal] != NULL)
        {
          currentAnimal++;
        }

        // delete and dereference the last turtle in turtles
        delete turtles[currentAnimal - 1];
        turtles[currentAnimal - 1] = NULL;
        break;
    };
 
}

/*
 * Summary: Generates a random bonus between $250-$500 per tiger and adds
 * the amount to the user's bank
 * Param: N/A
 * Return: N/A
 */
void Zoo::generateBonus()
{
    int currentTiger = 0;
    int tigerCount = 0;
    int currentBonus = 0;

    // Count tigers
    while (tigers[currentTiger] != NULL)
    {
        tigerCount++;
        currentTiger++;
    }

    if (tigerCount != 0)
    {
        currentBonus = randomNum(250, 500);
        currentBonus *= tigerCount;

        cout << "You received a bonus of $" << currentBonus << " for your " << tigerCount << " tigers!" << endl;

        dailyBonus = currentBonus;
    }
    else
    {
        cout << "Bummer! There was a boom in attendance, but you don't have any tigers." << endl;
    }
}

/*
 * Summary: Checks if there are any adult animals in the zoo then randomly selects
 * an animal to have a baby. If there are no adult animals of the selected type, the 
 * function is called again.
 * Param: N/A
 * Return: N/A
 */
void Zoo::babyBorn()
{
    int randomAnimal = randomNum(1, 3);
    int currentAnimal = 0;
    bool babyWasBorn = false;

    if (checkForAdults())
    {

        switch (randomAnimal)
        {
        case 1:
            while (tigers[currentAnimal] != NULL)
            {
                // If an adult tiger exists
                if (tigers[currentAnimal]->getAge() >= 3)
                {
                    cout << "Congratulations! A baby tiger was born!" << endl;
                    // Add a new baby tiger to the zoo
                    addTiger(new Tiger(0));
                    babyWasBorn = true;
                    break;
                }
                currentAnimal++;
            }
            // No adult tigers were found. Try again with penguins or turtles
            if (!babyWasBorn)
            {
                babyBorn();
            }
            break;

        case 2:
            while (penguins[currentAnimal])
            {
                // If an adult penguin exists
                if (penguins[currentAnimal]->getAge() >= 3)
                {
                    cout << "Congratulations! " << PENGIUN_BABIES << " baby penguins were born!" << endl;
                    // Add 5 new baby penguins to the zoo
                    for (int i = 0; i < PENGIUN_BABIES; i++)
                    {
                        addPenguin(new Penguin(0));
                    }
                    babyWasBorn = true;
                    break;
                }
                currentAnimal++;
            }
            // No adult tigers were found. Try again with penguins or turtles
            if (!babyWasBorn)
            {
                babyBorn();
            }
            break;

        case 3:
            while (turtles[currentAnimal] != NULL)
            {
                if (turtles[currentAnimal]->getAge() >= 3)
                {
                    cout << "Congratulations! " << TURTLE_BABIES << " baby turtles were born!" << endl;
                    // Add 10 new baby turtles to the zoo
                    for (int i = 0; i < TURTLE_BABIES; i++)
                    {
                        addTurtle(new Turtle(0));
                    }
                    babyWasBorn = true;
                    break;
                }
                currentAnimal++;
            }
            // No adult tigers were found. Try again with penguins or turtles
            if (!babyWasBorn)
            {
                babyBorn();
            }
            break;
        }
    }
    else
    {
        cout << "There are currently no adult animals in the zoo." << endl;
    }
}

/*
 * Summary: Determines whether any adult animals exist
 * Param: N/A
 * Return: boolean value representing whether any adult animals exist
 */
bool Zoo::checkForAdults()
{
    int currentAnimal = 0;

    while (tigers[currentAnimal] != NULL)
    {
        // If an adult tiger exists
        if (tigers[currentAnimal]->getAge() >= 3)
        {
            return true;
        }
        currentAnimal++;
    }

    currentAnimal = 0;

    while (penguins[currentAnimal] != NULL)
    {
        // If an adult penguin exists
        if (penguins[currentAnimal]->getAge() >= 3)
        {
            return true;
        }
        currentAnimal++;
    }

    currentAnimal = 0;

    while (turtles[currentAnimal] != NULL)
    {
        // If an adult turtle exists
        if (turtles[currentAnimal]->getAge() >= 3)
        {
            return true;
        }
        currentAnimal++;
    }

    return false;
}

/*
 * Summary: Calculates the total daily payoff for all animals
 * Param: N/A
 * Return: boolean value representing the total daily payoff for all animals
 */
double Zoo::calcAnimalPayoff()
{
    double totalPayoff = 0;
    int currentAnimal = 0;
    int tigerCount = 0;
    int penguinCount = 0;
    int turtleCount = 0;

    while (tigers[currentAnimal] != NULL)
    {
        tigerCount++;
        currentAnimal++;
    }

    totalPayoff += (tigerCount * (TIGER_COST * TIGER_PAY_MULTIPLIER));

    currentAnimal = 0;

    while (penguins[currentAnimal] != NULL)
    {
        penguinCount++;
        currentAnimal++;
    }

    totalPayoff += (penguinCount * (PENGUIN_COST * PENGUIN_PAY_MULTIPLIER));

    currentAnimal = 0;

    while (turtles[currentAnimal] != NULL)
    {
        turtleCount++;
        currentAnimal++;
    }

    totalPayoff += (turtleCount * (TURTLE_COST * TURTLE_PAY_MULTIPLIER));

    return totalPayoff;
}

/*
 * Summary: Calculates the profit for the current day
 * Param: N/A
 * Return: double value representing the profit for the current day
 */
double Zoo::calcDailyProfit(double payoff, double expenses, double bonus)
{
    return payoff - expenses + bonus;
}

/*
 * Summary: Adds an animal of the given type to the zoo and reduces the bank value
 * by the respective cost of the animal being purchased
 * Param: N/A
 * Return: N/A
 */
void Zoo::purchaseAnimal(int animal)
{
    switch (animal)
    {
    case 1:
        cout << "You have purchased a Tiger for $" << TIGER_COST << "!" << endl;
        manageBank(-(TIGER_COST));
        addTiger(new Tiger(3));
        break;

    case 2:
        cout << "You have pruchased a Penguin for $" << PENGUIN_COST << "!" << endl;
        addPenguin(new Penguin(3));
        manageBank(-(PENGUIN_COST));
        break;

    case 3:
        cout << "You have pruchased a Turtle for $" << TURTLE_COST << "!" << endl;
        addTurtle(new Turtle(3));
        manageBank(-(TURTLE_COST));
        break;
    }
}

/*
 * Summary: Deallocates the memory used by the various animal arrays
 * Param: N/A
 * Return: N/A
 */
void Zoo::deallocateMemory()
{
    int currentAnimal = 0;

    while (tigers[currentAnimal] != NULL)
    {
        delete tigers[currentAnimal];
        currentAnimal++;
    }

    currentAnimal = 0;

    while (penguins[currentAnimal] != NULL)
    {
        delete penguins[currentAnimal];
        currentAnimal++;
    }

    currentAnimal = 0;

    while (turtles[currentAnimal] != NULL)
    {
        delete turtles[currentAnimal];
        currentAnimal++;
    }

    delete[] tigers;
    tigers = NULL;
    delete[] penguins;
    penguins = NULL;
    delete[] turtles;
    turtles = NULL;
}

/*
 * Summary: Checks if there are any animals in the zoo.
 * Param: N/A
 * Return: boolean value determining whether there are any animals in the zoo
 */
bool Zoo::checkForAnimals()
{
  if (tigers[0] != NULL)
  {
    return true;
  }
	
  if (penguins[0] != NULL)
  {
    return true;
  }

  if (turtles[0] != NULL)
  {
    return true;
  }

  return false;	
}

/*
 * Summary: Zoo deconstructor
 * Param: N/A
 * Return: N/A
 */
Zoo::~Zoo()
{
}
