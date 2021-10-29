#ifndef GRAFO_HPP
#define GRAFO_HPP

#include <map>
#include <vector>
#include <ostream>
#include <istream>

#include "Vertice.hpp"

class Grafo {
    public:
        using vertexcontainer_t = std::map<sitecode_t, Vertice>;

    private:
        // Atributos
        vertexcontainer_t listaVertices;
        size_t _numeroDeArestas;

    public:
        Grafo();

        static Grafo fromCsv(std::istream& csvFile);

        size_t numeroDeVertices() const;
        size_t numeroDeArestas() const;

        void addVertice(Vertice&& v);
        void fazerAresta(sitecode_t id1, sitecode_t id2, product_t produto, 
                doc_t minDoc, doc_t rP, doc_t maxDoc, doc_t cS, doc_t dO);
        void toDots(std::ostream& arqSaida) const;


        void cenario1();
    private:
        const Vertice *getVerticeById(const sitecode_t& id) const;
        Vertice *getVerticeById(const sitecode_t& id);
};

#endif // GRAFO_HPP
