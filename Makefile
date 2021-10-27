libgrafo.so: grafo.cpp ./src/*
	g++ -shared -Wl,-soname,$@ -fPIC -o $@ $^ -I ./include

clean:
	rm -f libgrafo.so

.PHONY: clean
