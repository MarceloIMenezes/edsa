CXX=g++
INC=-I ./include
CPPFLAGS=
CFLAGS=-std=c++11 -W -Wall -pedantic $(INC) $(CPPFLAGS)

all: dataset edsa

edsa: main.cpp ./src/*
	$(CXX) $(CFLAGS) -o $@ $^

dataset:
	mkdir -p dataset
	python3 data_polish.py

clean:
	rm -f edsa

.PHONY: clean all dataset
