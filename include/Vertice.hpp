#ifndef VERTICE_HPP
#define VERTICE_HPP

#include <list>
#include <string>
#include <map>

#include "Aresta.hpp"

using loctype_t = std::string;

class Vertice {
    private:
        std::list<Aresta> listaAresta;
        sitecode_t _id;
        loctype_t _loctype;
        std::map<product_t, doc_t> availableToDeploy;

    public:
        Vertice() {};
        Vertice(sitecode_t id, loctype_t loctype);
        Vertice(sitecode_t id, loctype_t loctype, product_t produto, doc_t availableToDeploy);

        bool ehIsolado() const;
        sitecode_t id() const;
        loctype_t locationType() const;
        void adicionarProduto(const product_t& produto, doc_t available);
        doc_t available(const product_t& produto) const;
        void setAvailable(const product_t& produto, doc_t newAvailable);
        const std::list<Aresta>& listaDeAdjacencia() const;

        void addAdjacente(sitecode_t id, product_t produto,
                doc_t minDoc, doc_t rP, doc_t maxDoc, doc_t cS, doc_t dO);
};

#endif // VERTICE_HPP
