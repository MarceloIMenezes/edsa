#include "Grafo.hpp"
#include "Aresta.hpp"
#include "utils.hpp"

using namespace std;

Grafo::Grafo()
{
}

Grafo Grafo::gerarDoArquivo(std::istream& arqEntrada)
{
    return Grafo();
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
    // TODO: adaptar pra usar com novo container
    /* arqSaida << "graph {\n"; */
    /* for (const Vertice& v : this->listaVertices) { */
    /*     for (const Aresta& a : v.listaDeAdjacencia()) { */
    /*         if (v.id() < a.idDestino()) { */
    /*             arqSaida << "\t" << v.id() << " -- " << a.idDestino() << "\n"; */
    /*         } */
    /*     } */
    /* } */
    /* arqSaida << "}"; */
}
