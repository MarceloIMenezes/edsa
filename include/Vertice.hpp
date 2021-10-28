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
        Vertice(sitecode_t id, loctype_t loctype);

        sitecode_t id() const;
        loctype_t loctype() const;
        doc_t available(product_t produto) const;
        void setAvailable(product_t produto, doc_t newAvailable);
        const std::list<Aresta>& listaDeAdjacencia() const;

        void addAdjacente(sitecode_t id, product_t produto, 
                doc_t minDoc, doc_t rP, doc_t maxDoc, doc_t cS, doc_t dO);
};

#endif // VERTICE_HPP
