/**************************************************************************************
** Program name: randomNum.cpp
** Author: Michael Nutt
** Date: 10/20/2019
** Description: Implementation file for the randomNum function. The randomNum function 
** generates a random number between the range passed in.
**************************************************************************************/

#include <random>
#include "randomNum.hpp"

using std::mt19937;
using std::random_device;
using std::uniform_int_distribution;

/*
 * Summary: Generates a random number between the min and max passed in
 * Param: N/A
 * Return: integer value representing the randomly-generated number
 */
int randomNum(int min, int max)
{
    // Obtain random number
    static random_device randNum;
    // Seed generator
    static mt19937 seed(randNum());
    // Set range for random number
    uniform_int_distribution<> distribution(min, max);

    return distribution(seed);
}
