CXX=g++
INC=-I ./include
CFLAGS=-std=c++11 -W -Wall -O2 -pedantic $(INC)

execGrupo4: main.cpp ./src/*
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	rm -f execGrupo4

.PHONY: clean