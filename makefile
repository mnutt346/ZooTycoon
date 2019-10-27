###
### @file - project2_makefile
### @author - Michael Nutt <nuttm@oregonstate.edu>
### @description - makefile for Project 2 - Zoo Tycoon

#
# Zoo Tycoon
#

CXX = g++

CFLAGS = -std=c++11

.PHONY: clean

zooTycoon: zooTycoon.o menu.o inputValidation.o randomNum.o zoo.o animal.o tiger.o penguin.o turtle.o
	$(CXX) $(CFLAGS) -g zooTycoon.o menu.o inputValidation.o randomNum.o zoo.o animal.o tiger.o penguin.o turtle.o -o zooTycoon

zooTycoon.o: zooTycoon.cpp
	$(CXX) $(CFLAGS) -c zooTycoon.cpp

menu.o: menu.cpp menu.hpp
	$(CXX) $(CFLAGS) -c menu.cpp

inputValidation.o: inputValidation.cpp inputValidation.hpp
	$(CXX) $(CFLAGS) -c inputValidation.cpp

randomNum.o: randomNum.cpp randomNum.hpp
	$(CXX) $(CFLAGS) -c randomNum.cpp

zoo.o: zoo.cpp zoo.hpp
	$(CXX) $(CFLAGS) -c zoo.cpp

animal.o: animal.cpp animal.hpp
	$(CXX) $(CFLAGS) -c animal.cpp

tiger.o: tiger.cpp tiger.hpp
	$(CXX) $(CFLAGS) -c tiger.cpp

penguin.o: penguin.cpp penguin.hpp
	$(CXX) $(CFLAGS) -c penguin.cpp

turtle.o: turtle.cpp turtle.hpp
	$(CXX) $(CFLAGS) -c turtle.cpp

clean:
	rm *.o zooTycoon 
