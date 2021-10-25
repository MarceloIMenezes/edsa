#ifndef ARESTA_HPP
#define ARESTA_HPP

#include <string>

using sitecode_t = size_t;
using doc_t = size_t;
using product_t = std::string;

class Aresta {
    private:
        sitecode_t _idDestino;
        product_t _produto;
        doc_t _minDoc;
        doc_t _reorderPoint;
        doc_t _maxDoc;
        doc_t _closingStock;
        doc_t _distributionOrder;

    public:
        Aresta(sitecode_t idVertice, product_t produto, doc_t minDoc, doc_t rP, doc_t maxDoc, doc_t cS, doc_t dO);

        sitecode_t idDestino() const;
        product_t produto() const;
        doc_t minDoc() const;
        doc_t reorderPoint() const;
        doc_t maxDoc() const;
        doc_t closingStock() const;
        doc_t distributionOrder() const;
};

#endif // ARESTA_HPP
