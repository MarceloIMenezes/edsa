#include "Vertice.hpp"
#include <utility>

#ifdef DEBUG
#include <iostream>

static size_t addAdjacenteCalls = 0;
#endif

Vertice::Vertice(sitecode_t id, loctype_t loctype):
    _id(id),
    _loctype(loctype)
{
}

Vertice::Vertice(sitecode_t id, loctype_t loctype, product_t produto, doc_t availableToDeploy):
    _id(id),
    _loctype(loctype)
{
    this->adicionarProduto(produto, availableToDeploy);
}

bool Vertice::ehIsolado() const
{
    return (this->listaAresta.size() == 0);
}

sitecode_t Vertice::id() const
{
    return this->_id;
}

loctype_t Vertice::locationType() const
{
    return this->_loctype;
}

doc_t Vertice::available(const product_t& produto) const
{
    if (this->availableToDeploy.find(produto) != this->availableToDeploy.end())
        return this->availableToDeploy.at(produto);
    return 0;
}

void Vertice::adicionarProduto(const product_t& produto, doc_t available)
{
    this->availableToDeploy.insert(std::make_pair(produto, available));
}

void Vertice::setAvailable(const product_t& produto, doc_t newAvailable)
{
    this->availableToDeploy.at(produto) = newAvailable;
}

void Vertice::addAdjacente(sitecode_t id, product_t produto, 
                doc_t minDoc, doc_t rP, doc_t maxDoc, doc_t cS, doc_t dO)
{
#ifdef DEBUG
    extern size_t addAdjacenteCalls;

    std::cerr << __PRETTY_FUNCTION__ << '\n';
    std::cerr << "Vértice: `" << this->id() << "`\n";
    std::cerr << "listaArestaSize: " << this->listaAresta.size() << '\n';
    std::cerr << " número de chamadas: " <<  ++addAdjacenteCalls << '\n';
#endif

    this->listaAresta.push_back(Aresta(this->id(), id, produto, minDoc, rP, maxDoc, cS, dO));

#ifdef DEBUG
    std::cerr << "listaArestaSize: " << this->listaAresta.size() << "\n\n";
#endif
}

const std::list<Aresta>& Vertice::listaDeAdjacencia() const
{
    return this->listaAresta;
}
