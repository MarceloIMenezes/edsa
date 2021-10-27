#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <map>
#include <vector>
#include <ostream>
#include <istream>
#include <unordered_map>

#include "Vertice.hpp"

class Grafo {
    public:
        using vertexcontainer_t = std::unordered_map<sitecode_t, Vertice>;

    private:
        // Atributos
        vertexcontainer_t listaVertices;
        size_t _numeroDeArestas;

    public:
        Grafo();

        static Grafo gerarDoArquivo(std::istream& arqEntrada);

        size_t numeroDeVertices() const;
        size_t numeroDeArestas() const;

        void fazerAresta(sitecode_t id1, sitecode_t id2);
        void toDots(std::ostream& arqSaida) const;

        Grafo algoritmoGulosoRandomizadoReativo(
                const std::vector<double>& alfas, size_t nIteracoes,
                size_t tamanhoBloco, size_t cenario);

    private:
        Grafo algoritmoGulosoHelper(double alfa, size_t cenario);
        const Vertice *getVerticeById(const sitecode_t& id) const;
        Vertice *getVerticeById(const sitecode_t& id);
};

#endif // GRAFO_HPP
