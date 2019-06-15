CC = g++
FLAGS = -Wall -g
LINKS = -lsfml-graphics -lsfml-window -lsfml-system -lm
main = basic
objects = utils ball sim 

all: $(objects) $(main)


ball: ball.hpp ball.cpp utils.hpp
	$(CC) $@.cpp -c $(FLAGS) $(LINKS)


utils: utils.cpp utils.hpp
	$(CC) $@.cpp -c $(FLAGS) $(LINKS)

sim: sim.cpp sim.hpp
	$(CC) $@.cpp -c $(FLAGS) $(LINKS)

basic: basic.hpp basic.cpp ball
	$(CC) $@.cpp ball.o utils.o sim.o $(FLAGS) -o basic $(LINKS)


run: all
	./basic

clean:
	rm basic

