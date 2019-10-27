/**************************************************************************************
** Program name: zoo.hpp
** Author: Michael Nutt
** Date: 10/16/2019
** Description: Declaration and header file for the Zoo class.
**************************************************************************************/

#ifndef ZOO_HPP
#define ZOO_HPP

#include <string>
#include "animal.hpp"
#include "tiger.hpp"
#include "penguin.hpp"
#include "turtle.hpp"

class Zoo
{
private:
    Animal **tigers;
    Animal **penguins;
    Animal **turtles;
    double bank;
    double dailyBonus;
    int maxTigers;
    int maxPenguins;
    int maxTurtles;

public:
    Zoo();
    ~Zoo();
    void play();
    void buyStartingTigers();
    void buyStartingPenguins();
    void buyStartingTurtles();
    double getBankValue();
    void manageBank(double);
    void addTiger(Animal *);
    void addPenguin(Animal *);
    void addTurtle(Animal *);
    bool speciesIsFull(Animal **, int);
    void increaseSize(Animal **&, int &);
    void printTigers();
    void printPenguins();
    void printTurtles();
    void incrementAges();
    double calcFoodCost();
    void executeRandomEvent();
    void diseaseOutbreak();
    void quarantineAnimal(int);
    void generateBonus();
    void babyBorn();
    bool checkForAdults();
    double calcAnimalPayoff();
    double calcDailyProfit(double, double, double);
    void purchaseAnimal(int);
    void deallocateMemory();
    bool checkForAnimals();
};

#endif
