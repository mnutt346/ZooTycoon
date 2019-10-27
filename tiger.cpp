/**************************************************************************************
** Program name: tiger.cpp
** Author: Michael Nutt
** Date: 10/16/2019
** Description: Implementation file for the Tiger class. The Tiger class constructor 
** initializes the Tiger's age, cost, numberOfBabies, baseFoodCost, and payoff to the
** respective values passed in.
**************************************************************************************/

#include <string>
#include "tiger.hpp"
#include "animal.hpp"

using std::string;

const double BASE_FOOD = 10.00;
const double TIGER_COST = 10000.00;
const int TIGER_BABIES = 1;
const double TIGER_FOOD_MULTIPLIER = 5.00;
const double TIGER_PAY_MULTIPLIER = 0.20;

/*
 * Summary: The Tiger default constructor initializes a Tiger object with its respective
 * cost, numberOfBabies, baseFoodCost, payoff, and species. The default age is set to 1. 
 * Param: N/A
 * Return: N/A
 */
Tiger::Tiger() : Animal()
{
    cost = TIGER_COST;
    numberOfBabies = TIGER_BABIES;
    baseFoodCost = BASE_FOOD * TIGER_FOOD_MULTIPLIER;
    payoff = TIGER_COST * TIGER_PAY_MULTIPLIER;
    species = "Tiger";
}

/*
 * Summary: The Tiger constructor initializes a Tiger object with its respective
 * cost, numberOfBabies, baseFoodCost, payoff, and species. The age is set to the int
 * value passed in. 
 * Param: int days -> represents the age of the Tiger
 * Return: N/A
 */
Tiger::Tiger(int days) : Animal(days)
{
    age = days;
    cost = TIGER_COST;
    numberOfBabies = TIGER_BABIES;
    baseFoodCost = BASE_FOOD * TIGER_FOOD_MULTIPLIER;
    payoff = TIGER_COST * TIGER_PAY_MULTIPLIER;
    species = "Tiger";
}