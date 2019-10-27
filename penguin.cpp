/**************************************************************************************
** Program name: penguin.cpp
** Author: Michael Nutt
** Date: 10/14/2019
** Description: Implementation file for the Penguin class. The Penguin class constructor 
** initializes the Penguin's age, cost, numberOfBabies, baseFoodCost, and payoff.
**************************************************************************************/

#include "penguin.hpp"
#include "animal.hpp"

const double BASE_FOOD = 10.00;
const double PENGUIN_COST = 1000.00;
const int PENGUIN_BABIES = 5;
const double PENGUIN_FOOD_MULTIPLIER = 1.00;
const double PENGUIN_PAY_MULTIPLIER = 0.10;

/*
 * Summary: The Penguin default constructor initializes a Penguin object with its respective
 * cost, numberOfBabies, baseFoodCost, payoff, and species. The default age is set to 1. 
 * Param: N/A
 * Return: N/A
 */
Penguin::Penguin() : Animal()
{
    cost = PENGUIN_COST;
    numberOfBabies = PENGUIN_BABIES;
    baseFoodCost = BASE_FOOD * PENGUIN_FOOD_MULTIPLIER;
    payoff = PENGUIN_COST * PENGUIN_PAY_MULTIPLIER;
    species = "Penguin";
}

/*
 * Summary: The Penguin constructor takes a given number of days, cost, numberOfBabies, 
 * baseFoodCost, and payoff to initialize a Penguin object. 
 * Param: N/A
 * Return: N/A
 */
Penguin::Penguin(int days) : Animal(days)
{
    age = days;
    cost = PENGUIN_COST;
    numberOfBabies = PENGUIN_BABIES;
    baseFoodCost = BASE_FOOD * PENGUIN_FOOD_MULTIPLIER;
    payoff = PENGUIN_COST * PENGUIN_PAY_MULTIPLIER;
    species = "Penguin";
};
