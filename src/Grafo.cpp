#include "Grafo.hpp"
#include "Aresta.hpp"
#include "utils.hpp"

#include <cmath>
#include <memory>
#include <limits>
#include <algorithm>
#include <stdexcept>

using namespace std;

Grafo::Grafo(size_t numeroDeVertices)
{
    // Inicializa a lista de vértice com seus respectivos IDs.
    this->listaVertices.reserve(numeroDeVertices);
    for (sitecode_t id = 0; id < numeroDeVertices; ++id) {
        this->listaVertices.push_back(Vertice(id));
    }
}

Grafo Grafo::gerarDoArquivo(std::istream& arqEntrada)
{
    size_t nVertices;

    Grafo g(nVertices);
    return g;
}

Vertice *Grafo::getVerticeById(sitecode_t id)
{
    return &this->listaVertices[id];
}

const Vertice *Grafo::getVerticeById(sitecode_t id) const
{
    return &this->listaVertices[id];
}

size_t Grafo::numeroDeVertices() const
{
    return this->listaVertices.size();
}

void Grafo::fazerAresta(sitecode_t id1, sitecode_t id2)
{
    /* Testa se um vértice existe. Caso contrário, lança uma excessão
     * do tipo std::invalid_argument
     */
#define TEST_VERTICE(v, id)                                                    \
    do {                                                                       \
        if ((v) == nullptr) {                                                  \
            throw std::invalid_argument(                                       \
                    std::string("não foi possível encontrar grafo com id ") += \
                    (id));                                                     \
        }                                                                      \
    } while (0)

    if (id1 != id2) {
        Vertice *v1 = this->getVerticeById(id1);
        Vertice *v2 = this->getVerticeById(id2);

        TEST_VERTICE(v1, id1);
        TEST_VERTICE(v2, id2);

        v1->addAdjacente(id2);
        v2->addAdjacente(id1);
    } else {
        Vertice *v = this->getVerticeById(id1);

        TEST_VERTICE(v, id1);
        v->addAdjacente(id1);
    }
}

void Grafo::toDots(std::ostream& arqSaida) const
{
    arqSaida << "graph {\n";
    for (const Vertice& v : this->listaVertices) {
        for (const Aresta& a : v.listaDeAdjacencia()) {
            if (v.id() < a.idDestino()) {
                arqSaida << "\t" << v.id() << " -- " << a.idDestino() << "\n";
            }
        }
    }
    arqSaida << "}";
}

Grafo Grafo::algoritmoGulosoHelper(double alfa) const
{
    Grafo F(this->numeroDeVertices());
    return F;
}

/* Estrutura auxiliar usada no algoritmoGulosoRandomizadoReativo para calcular
 * a média de um alfa
 */
struct Media {
    size_t total;
    size_t nVezes;

    Media():
        total(0),
        nVezes(0)
    {}

    // Calcula a média
    inline operator double() const
    {
        return (this->nVezes == 0) ? 0 : (double) this->total / this->nVezes;
    }
};

static size_t selecionaAlfa(unique_ptr<double[]>& P, size_t m) 
{
    double rng = (double) (rand() % 1000) / 1000;
    double aux = 0;

    for (size_t i = 0; i < m; i++) {
        aux += P[i];
        if (rng <= aux) {
            return i;
        }
    }
    return m - 1;
}

static inline void atualizarMedias(unique_ptr<Media[]>& A,size_t i)
{
    // TODO
}

static inline void atualizarProbabilidades(unique_ptr<double[]>& P,
        unique_ptr<Media[]>& A, size_t m, size_t melhorSol)
{
#define SIGMA 10

    unique_ptr<double[]> q(new double[m]);
    double somatorioDeQjs = 0;

    for (size_t i = 0; i < m; ++i) {
        q[i] = std::pow(melhorSol / A[i], SIGMA);
        somatorioDeQjs += q[i];
    }

    for (size_t i = 0; i < m; ++i) {
        P[i] = q[i] / somatorioDeQjs;
    }
}

Grafo Grafo::algoritmoGulosoRandomizadoReativo(const vector<double>& alfas,
        size_t nIteracoes, size_t bloco) const
{
    Grafo melhorSol(this->numeroDeVertices());
    Grafo solAux(this->numeroDeVertices());

    unique_ptr<double[]> P(new double[alfas.size()]);
    unique_ptr<Media[]> A(new Media[alfas.size()]);

    bool isPrimeiraVez = true;
    size_t i;

    do {
        double pInicial = (double) 1 / alfas.size();

        for (size_t i = 0; i < alfas.size(); ++i) {
            P[i] = pInicial;
        }
    } while (0);

    for (i = 1; i <= alfas.size() && i <= nIteracoes; ++i) {
        size_t alfaidx = i - 1;

        solAux = this->algoritmoGulosoHelper(alfas[alfaidx]);

    //    atualizarMedias(A, alfaidx);


    //     if (isPrimeiraVez || solAux.eficiencia() < melhorSol.eficiencia()) {
    //         isPrimeiraVez = false;
    //         melhorSol = std::move(solAux);
    //     }
    }

    //atualizarProbabilidades(P, A, alfas.size(), melhorSol.eficiencia());

    for (; i <= nIteracoes; ++i) {
        // if (i % bloco == 0) {
        //     atualizarProbabilidades(P, A, alfas.size(), melhorSol.eficiencia());
        // }

        size_t alfaidx = selecionaAlfa(P, alfas.size());

        solAux = this->algoritmoGulosoHelper(alfas[alfaidx]);

    //    atualizarMedias(A, solAux.eficiencia(), alfaidx);


        // if (solAux.eficiencia() < melhorSol.eficiencia()) {
        //     isPrimeiraVez = false;
        //     melhorSol = std::move(solAux);
        // }
    }
    return melhorSol;
}