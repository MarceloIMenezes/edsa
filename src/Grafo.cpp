#include "Grafo.hpp"
#include "Aresta.hpp"
#include "utils.hpp"

#ifdef DEBUG
#include <iostream>
#endif

#define PDEBUG(var) /* nothing */;

#ifdef DEBUG
#undef PDEBUG
#define PDEBUG(var) std::cerr << #var << ": " << (var) << '\n'
#endif

using namespace std;

Grafo::Grafo()
{
}

Grafo Grafo::fromCsv(std::istream& csvFile)
{
#define REMOVE_CSV_HEADER(csvFile) \
    do { std::string __l; std::getline(csvFile, __l); } while (0)

#define FIELD_TO_DOC_T(field)                                                  \
    do {                                                                       \
        csvFieldParser(linha, tmp, &pos);                                      \
        PDEBUG(tmp);                                                           \
        field = stod(tmp);                                                     \
    } while (0)

    std::string linha;
    Grafo g;

#ifndef DEBUG
    int __nvezes = 10;
#endif

    REMOVE_CSV_HEADER(csvFile);

    while (std::getline(csvFile, linha)
#ifndef DEBUG
            && __nvezes--
#endif
          ) {
        sitecode_t ssc;
        product_t produto;
        sitecode_t locationCode;
        loctype_t locationType; 
        doc_t minDoc;
        doc_t rop;
        doc_t maxDoc;
        doc_t closingStock;
        doc_t distributorOrder;
        doc_t availableToDeploy;

        std::string tmp;
        size_t pos = 0;

        csvFieldParser(linha, ssc, &pos);
        csvFieldParser(linha, produto, &pos);
        csvFieldParser(linha, locationCode, &pos);
        csvFieldParser(linha, locationType, &pos);
        FIELD_TO_DOC_T(minDoc);
        FIELD_TO_DOC_T(rop);
        FIELD_TO_DOC_T(maxDoc);
        FIELD_TO_DOC_T(closingStock);
        FIELD_TO_DOC_T(distributorOrder);
        FIELD_TO_DOC_T(availableToDeploy);

#ifdef DEBUG
        PDEBUG(ssc);
        PDEBUG(produto);
        PDEBUG(locationCode);
        PDEBUG(minDoc);
        PDEBUG(rop);
        PDEBUG(maxDoc);
        PDEBUG(closingStock);
        PDEBUG(distributorOrder);
        PDEBUG(availableToDeploy);
        std::cerr << '\n';
#endif

        g.addVertice({ ssc,  "DEP", produto, availableToDeploy });
        g.addVertice({ locationCode, locationType });

        g.fazerAresta(
            ssc,
            locationCode,
            produto,
            minDoc,
            rop,
            maxDoc,
            closingStock,
            distributorOrder
        );
    }
    return g;
}

#define GET_BY_ID()                                                            \
    do {                                                                       \
        auto it = this->listaVertices.find(id);                                \
        return (it == this->listaVertices.end()) ? nullptr : &it->second;      \
    } while (0)

Vertice *Grafo::getVerticeById(const sitecode_t& id)
{
    GET_BY_ID();
}

const Vertice *Grafo::getVerticeById(const sitecode_t& id) const
{
    GET_BY_ID();
}

size_t Grafo::numeroDeVertices() const
{
    return this->listaVertices.size();
}

size_t Grafo::numeroDeArestas() const
{
    return this->_numeroDeArestas;
}

void Grafo::addVertice(Vertice&& v)
{
    if (this->getVerticeById(v.id()) == nullptr) {
        this->listaVertices[v.id()] = std::move(v);
    }
}

void Grafo::fazerAresta(sitecode_t id1, sitecode_t id2, product_t produto,
                doc_t minDoc, doc_t rP, doc_t maxDoc, doc_t cS, doc_t dO)
{
#define TEST_VERTICE(v, id)                                                    \
    do {                                                                       \
        if ((v) == nullptr) {                                                  \
            throw std::invalid_argument(                                       \
                    std::string("não foi possível encontrar grafo com id ") += \
                    (id));                                                     \
        }                                                                      \
    } while (0)

    if (id1 != id2) {
        Vertice *origem = this->getVerticeById(id1);
        Vertice *destino = this->getVerticeById(id2);

        TEST_VERTICE(origem, id1);
        TEST_VERTICE(destino, id2);

        origem->addAdjacente(id2, produto,
                minDoc, rP, maxDoc, cS, dO);
    } else {
        Vertice *v = this->getVerticeById(id1);

        TEST_VERTICE(v, id1);
        v->addAdjacente(id1, produto,
                minDoc, rP, maxDoc, cS, dO);
    }
    this->_numeroDeArestas++;
}

void Grafo::toDots(std::ostream& arqSaida) const
{
#ifdef DEBUG
    size_t count = 0;
#endif
    auto begin = this->listaVertices.cbegin();
    auto end = this->listaVertices.cend();
    arqSaida << "digraph {\n";
    for (auto it = begin; it != end; ++it) {
        const Vertice& v = it->second;
#ifdef DEBUG
        ++count;
        std::cerr << "Número de arestas do vértice `" << v.id() << "`: "
            << v.listaDeAdjacencia().size() << '\n';
#endif
        if (v.ehIsolado()) {
            arqSaida << "\t\"" << v.id() << "\";\n";
            continue;
        }
        for (const Aresta& a : v.listaDeAdjacencia()) {
            arqSaida << "\t\"" << v.id() << "\" -> \"" << a.idDestino() << "\";\n";
        }
    }
    arqSaida << "}";
#ifdef DEBUG
    std::cerr << __PRETTY_FUNCTION__ << " Número de vértices:"<< count << '\n';
#endif
}
