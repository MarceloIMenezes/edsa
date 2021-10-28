CXX=g++
INC=-I ./include
CPPFLAGS=
CFLAGS=-std=c++11 -W -Wall -pedantic $(INC) $(CPPFLAGS)

edsa: main.cpp ./src/*
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	rm -f edsa

.PHONY: clean
