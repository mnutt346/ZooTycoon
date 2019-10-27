/**************************************************************************************
** Program name: menu.hpp
** Author: Michael Nutt
** Date: 10/16/2019
** Description: Declaration and header file for the Menu class.
**************************************************************************************/

#ifndef MENU_HPP
#define MENU_HPP

#include <string>

bool startMenu(std::string);

int gameMenuRange(std::string, int, int);

int gameMenuBinary(std::string, std::string, std::string);

int gameMenuThreeOptions(std::string, std::string, std::string, std::string);

#endif
