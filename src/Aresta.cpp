#include "Aresta.hpp"

Aresta::Aresta(sitecode_t idOrigem, sitecode_t idDestino, product_t produto, doc_t minDoc, doc_t rP, doc_t maxDoc, doc_t cS, doc_t dO):
    _idOrigem(idOrigem),
    _idDestino(idDestino),
    _produto(produto),
    _minDoc(minDoc),
    _reorderPoint(rP),
    _maxDoc(maxDoc),
    _closingStock(cS),
    _distributionOrder(dO)
{
}


sitecode_t Aresta::idDestino() const
{
    return this->_idDestino;
}

product_t Aresta::produto() const
{
    return this->_produto;
}

doc_t Aresta::minDoc() const
{
    return this->_minDoc;
}

doc_t Aresta::reorderPoint() const
{
    return this->_reorderPoint;
}

doc_t Aresta::maxDoc() const
{
    return this->_maxDoc;
}

doc_t Aresta::closingStock() const
{
    return this->_closingStock;
}

doc_t Aresta::distributionOrder() const
{
    return this->_distributionOrder;
}

void Aresta::setDistributionOrder(doc_t newOrder)
{
    this->_distributionOrder = newOrder;
}