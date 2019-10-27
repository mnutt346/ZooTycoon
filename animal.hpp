/**************************************************************************************
** Program name: animal.hpp
** Author: Michael Nutt
** Date: 10/16/2019
** Description: Declaration and header file for the Animal class.
**************************************************************************************/

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <string>

class Animal
{
protected:
    int age;
    double cost;
    int numberOfBabies;
    double baseFoodCost;
    double payoff;
    std::string species;

public:
    Animal();
    Animal(int);
    int getAge();
    void incrementAge();
    double getBaseFoodCost();
    std::string getSpecies();
};

#endif
