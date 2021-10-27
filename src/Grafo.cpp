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
        this->listaVertices.push_back(Vertice(id)); // TODO: fazer uma hash ligando o location/supply code nesse id aqui
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

size_t Grafo::numeroDeArestas() const
{
    return this->_numeroDeArestas;
}

void Grafo::fazerAresta(sitecode_t id1, sitecode_t id2) // TODO: adicionar o resto dos parametros
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
    for (const Vertice& v : this->listaVertices) {
        for (const Aresta& a : v.listaDeAdjacencia()) {
            if (v.id() < a.idDestino()) {
                arqSaida << "\t" << v.id() << " -- " << a.idDestino() << "\n";
            }
        }
    }
    arqSaida << "}";
}

std::vector<Aresta> ordenaCandidatos(const std::vector<Vertice> &listaVertices, size_t numeroDeArestas)
{
    std::vector<Aresta> lc;
    lc.reserve(numeroDeArestas);
    for (const Vertice v : listaVertices) {
        for (const Aresta a : v.listaDeAdjacencia()) {
            lc.push_back(a);
        }
    }
    std::sort(lc.begin(), lc.end(),
              [](const Aresta &a, const Aresta &b)
              {
                  if (a.distributionOrder() > b.distributionOrder())
                  {
                      return false;
                  }
                  if (a.distributionOrder() < b.distributionOrder())
                  {
                      return true;
                  }
                  if ((a.reorderPoint() - a.closingStock()) > (b.reorderPoint() - b.closingStock()))
                  {
                      return false;
                  }
                  return true;
              });
    return lc;
}

Grafo Grafo::algoritmoGulosoHelper(double alfa, size_t cenario)
{
#define AVAILABLETODEPLOY(origem, produto)          \
this->getVerticeById(origem)->available(produto)
   
    Grafo F(this->numeroDeVertices());
    std::vector<Aresta> lc = ordenaCandidatos(this->listaVertices, this->numeroDeArestas());
    
    int i;
    do {
        size_t aux = lc.size() * alfa;
        size_t idx = (aux < 2) ? 0 : (rand() % aux);

        Aresta& a = lc[idx];
        // TODO: distribuir pro candidato (ver no map do vertice origem se tem produto availableToDeploy)
        // * cenario 1: 
        // Entregar a todos as cervejarias (exceto Hubs) a capacidade máxima (maxDOC) 
        // e distribuir aos distribuidores (DIST) sua demanda completa e deixar oq sobrar num Hub
        Vertice *origemAux = this->getVerticeById(a.idOrigem()); 
        if (a.distributionOrder() != 0 && AVAILABLETODEPLOY(a.idOrigem(), a.produto())>= a.distributionOrder()) { // ignora maxDoc das DIST
            origemAux->setAvailable(a.produto() , origemAux->available(a.produto()) - a.distributionOrder());
            a.setDistributionOrder(0);
        } else if (a.distributionOrder() != 0) {
            // distribui tudo q tem disponivel
            a.setDistributionOrder(a.distributionOrder() - origemAux->available(a.produto()));
            origemAux->setAvailable(a.produto(), 0);
        } else if (this->getVerticeById(a.idDestino())->loctype() == "DIST") { // distribuir para nao hub o maxDOC

        }
    } while (false); // TODO: condição de parada
    return F;
}

/*  Estrutura auxiliar usada no algoritmoGulosoRandomizadoReativo para calcular
   a média de um alfa
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
        size_t nIteracoes, size_t bloco, size_t cenario) const
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

        solAux = this->algoritmoGulosoHelper(alfas[alfaidx], cenario);

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

        solAux = this->algoritmoGulosoHelper(alfas[alfaidx], cenario);

    //    atualizarMedias(A, solAux.eficiencia(), alfaidx);


        // if (solAux.eficiencia() < melhorSol.eficiencia()) {
        //     isPrimeiraVez = false;
        //     melhorSol = std::move(solAux);
        // }
    }
    return melhorSol;
}