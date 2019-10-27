/**************************************************************************************
** Program name: turtle.cpp
** Author: Michael Nutt
** Date: 10/14/2019
** Description: Implementation file for the Turtle class. The Turtle class constructor 
** initializes the Turtle's age, cost, numberOfBabies, baseFoodCost, species, and payoff 
** to their respective values.
**************************************************************************************/

#include "turtle.hpp"
#include "animal.hpp"

const double BASE_FOOD = 10.00;
const double TURTLE_COST = 100.00;
const int TURTLE_BABIES = 10;
const double TURTLE_FOOD_MULTIPLIER = 0.50;
const double TURTLE_PAY_MULTIPLIER = 0.05;

/*
 * Summary: The Turtle default constructor initializes a Turtle object with its respective
 * cost, numberOfBabies, baseFoodCost, payoff, and species. The default age is set to 1. 
 * Param: N/A
 * Return: N/A
 */
Turtle::Turtle() : Animal()
{
    cost = TURTLE_COST;
    numberOfBabies = TURTLE_BABIES;
    baseFoodCost = BASE_FOOD * TURTLE_FOOD_MULTIPLIER;
    payoff = TURTLE_COST * TURTLE_PAY_MULTIPLIER;
    species = "Turtle";
};

/*
 * Summary: The Turtle constructor takes a given number of days initialize a Turtle object. 
 * Param: int days -> represents the age of the Turtle
 * Return: N/A
 */
Turtle::Turtle(int days) : Animal(days)
{
    age = days;
    cost = TURTLE_COST;
    numberOfBabies = TURTLE_BABIES;
    baseFoodCost = BASE_FOOD * TURTLE_FOOD_MULTIPLIER;
    payoff = TURTLE_COST * TURTLE_PAY_MULTIPLIER;
    species = "Turtle";
};