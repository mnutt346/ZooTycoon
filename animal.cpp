/**************************************************************************************
** Program name: animal.cpp
** Author: Michael Nutt
** Date: 10/16/2019
** Description: Implementation file for the Animal class. The Animal class constructor 
** initializes the animal's age, cost, numberOfBabies , baseFoodCost, and payoff. The
** get methods for baseFoodCost, age, and species are also defined, along with the 
** increment age function. 
**************************************************************************************/

#include <string>
#include "animal.hpp"

using std::string;

/* 
 * Summary: The Animal default constructor sets the attributes for the animal being
 * initialized.
 * Param: N/A
 * Return: N/A
 */
Animal::Animal()
{
    age = 1;
    cost = 10.00;
    numberOfBabies = 1;
    baseFoodCost = 10.00;
    payoff = 5.00;
    species = "Animal";
}

/* 
 * Summary: The Animal constructor takes a given number of days to set the age.
 * Param: int days -> sets the age of the animal
 * Return: N/A
 */
Animal::Animal(int days)
{
    age = days;
}

/* 
 * Summary: getAge returns the value of the animal's age.
 * Param: N/A
 * Return: int value representing the animal's age in days.
 */
int Animal::getAge()
{
    return this->age;
}

/* 
 * Summary: =incrementAge increases the animal's age by 1.
 * Param: N/A
 * Return: N/A.
 */
void Animal::incrementAge()
{
    this->age++;
}


/* 
 * Summary: getBaseFoodCost returns the cost to feed the animal.
 * Param: N/A
 * Return: double value representing the cost to feed the animal.
 */
double Animal::getBaseFoodCost()
{
    return this->baseFoodCost;
}

/* 
 * Summary: getSpecies returns the species of the calling animal.
 * Param: N/A
 * Return: string value representig the species of the calling animal.
 */
string Animal::getSpecies()
{
    return this->species;
}
