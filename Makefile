all: teenpatti

teenpatti: main.o functions.o game.o cards_rank.o 
	g++ -o teenpatti main.o functions.o game.o cards_rank.o

main.o: main.cpp
	g++ -c main.cpp

cards_rank.o: cards_rank.cpp cards_rank.hpp
	g++ -c cards_rank.cpp

game.o: game.cpp game.hpp
	g++ -c game.cpp

functions.o: functions.cpp functions.hpp
	g++ -c functions.cpp
	
.PHONY: all clean

clean: 
	rm *.o teenpatti