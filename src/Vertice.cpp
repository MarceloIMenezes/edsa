#include "Vertice.hpp"

Vertice::Vertice(sitecode_t id, loctype_t loctype):
    _id(id),
    _loctype(loctype)
{
}

sitecode_t Vertice::id() const
{
    return this->_id;
}

loctype_t Vertice::loctype() const
{
    return this->_loctype;
}

doc_t Vertice::available(product_t produto) const
{
    if (this->availableToDeploy.find(produto) != this->availableToDeploy.end())
        return this->availableToDeploy.at(produto);
    return 0;
}

void Vertice::setAvailable(product_t produto, doc_t newAvailable)
{
    this->availableToDeploy.at(produto) = newAvailable;
}

void Vertice::addAdjacente(sitecode_t id)
{
    for (const Aresta& a : this->listaAresta) {
        if (a.idDestino() == id) {
            return;
        }
    }
    this->listaAresta.push_back(Aresta(this->id(), id, "0", 0, 0, 0, 0, 0)); // TODO: add os parametros das arestas aqui
}

const std::list<Aresta>& Vertice::listaDeAdjacencia() const
{
    return this->listaAresta;
}
