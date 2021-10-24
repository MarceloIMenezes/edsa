#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <map>
#include <vector>
#include <ostream>
#include <istream>

#include "Vertice.hpp"

class Grafo {
    private:
        using vertexlist_t = std::vector<Vertice>;

        // Atributos
        vertexlist_t listaVertices;

    public:
        Grafo(size_t numeroDeVertices);

        static Grafo gerarDoArquivo(std::istream& arqEntrada);

        size_t numeroDeVertices() const;

        void fazerAresta(idvertice_t id1, idvertice_t id2);
        void toDots(std::ostream& arqSaida) const;

        Grafo algoritmoGuloso() const;
        Grafo algoritmoGulosoRandomizado(double alfa, size_t nIteracoes) const;
        Grafo algoritmoGulosoRandomizadoReativo(
                const std::vector<double>& alfas, size_t nIteracoes,
                size_t tamanhoBloco) const;

    private:
        Grafo algoritmoGulosoHelper(double alfa) const;
        const Vertice *getVerticeById(idvertice_t id) const;
        Vertice *getVerticeById(idvertice_t id);
};

#endif // GRAFO_HPP
