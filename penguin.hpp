/**************************************************************************************
** Program name: penguin.hpp
** Author: Michael Nutt
** Date: 10/16/2019
** Description: Declaration and header file for the Penguin class.
**************************************************************************************/

#ifndef PENGUIN_HPP
#define PENGUIN_HPP

#include "animal.hpp"

class Penguin : public Animal
{
public:
    Penguin();
    Penguin(int);
};

#endif