libgrafo.so: main.cpp ./src/*
	g++ -shared -Wl,-soname,$@ -fPIC -o $@ $^ -I ./include

clean:
	rm -f execGrupo4

.PHONY: clean
