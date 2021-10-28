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

        size_t pos = 0;

        std::string tmp;

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

void Grafo::addVertice(sitecode_t _id, loctype_t locationType)
{
    this->listaVertices[_id] = Vertice(_id, locationType);
}

void Grafo::fazerAresta(sitecode_t id1, sitecode_t id2) // TODO: adicionar o resto dos parametros
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

        origem->addAdjacente(id2);
    } else {
        Vertice *v = this->getVerticeById(id1);

        TEST_VERTICE(v, id1);
        v->addAdjacente(id1);
    }
    this->_numeroDeArestas++;
}

void Grafo::toDots(std::ostream& arqSaida) const
{
    arqSaida << "graph {\n";
    for (const std::pair<sitecode_t, Vertice> it : this->listaVertices) {
        const Vertice& v = it.second;
        for (const Aresta& a : v.listaDeAdjacencia()) {
            if (v.id() < a.idDestino()) {
                arqSaida << "\t" << v.id() << " -- " << a.idDestino() << "\n";
            }
        }
    }
    arqSaida << "}";
}
