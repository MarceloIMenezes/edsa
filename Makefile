CXX=g++
INC=-I ./include
CFLAGS=-std=c++11 -W -Wall -pedantic $(INC)

edsa: main.cpp ./src/*
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	rm -f edsa

.PHONY: clean
