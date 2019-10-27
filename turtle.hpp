/**************************************************************************************
** Program name: turtle.hpp
** Author: Michael Nutt
** Date: 10/16/2019
** Description: Declaration and header file for the Turtle class.
**************************************************************************************/

#ifndef TURTLE_HPP
#define TURTLE_HPP

#include "animal.hpp"

class Turtle : public Animal
{
public:
    Turtle();
    Turtle(int);
};

#endif