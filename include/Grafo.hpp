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
        size_t _numeroDeArestas;

    public:
        Grafo(size_t numeroDeVertices);

        static Grafo gerarDoArquivo(std::istream& arqEntrada);

        size_t numeroDeVertices() const;
        size_t numeroDeArestas() const;

        void fazerAresta(sitecode_t id1, sitecode_t id2);
        void toDots(std::ostream& arqSaida) const;

        Grafo algoritmoGuloso() const;
        Grafo algoritmoGulosoRandomizadoReativo(
                const std::vector<double>& alfas, size_t nIteracoes,
                size_t tamanhoBloco, size_t cenario) const;

    private:
        Grafo algoritmoGulosoHelper(double alfa, size_t cenario);
        const Vertice *getVerticeById(sitecode_t id) const;
        Vertice *getVerticeById(sitecode_t id);
};

#endif // GRAFO_HPP
