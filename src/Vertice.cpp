#include "Vertice.hpp"

Vertice::Vertice(sitecode_t id):
    _id(id)
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

doc_t Vertice::available(product_t produto)
{
    if (this->availableToDeploy.find(produto) != this->availableToDeploy.end())
        return this->availableToDeploy.at(produto);
    return 0;
}

void Vertice::addAdjacente(sitecode_t id)
{
    // TODO: add os parametros das arestas aqui
    for (const Aresta& a : this->listaAresta) {
        if (a.idDestino() == id) {
            return;
        }
    }
    this->listaAresta.push_back(Aresta(id, "0", 0, 0, 0, 0, 0));
}

const std::list<Aresta>& Vertice::listaDeAdjacencia() const
{
    return this->listaAresta;
}
