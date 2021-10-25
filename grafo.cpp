/************************************************************
*   EDSA - EFFICIENT DISTRIBUTION SYSTEM ALGORITHM
*       Igor Correa Rodrigues       - UFJF
*       João Stephan Silva Maurício - UFJF
*       Marcelo Ian Rezende Menezes - UFJF
************************************************************/

#include <iostream>

#include "Grafo.hpp"

extern "C" {
    Grafo *grafo_new(size_t size) { return new Grafo(size); }

    size_t grafo_numero_de_vertices(const Grafo *g)
    {
        return g->numeroDeVertices();
    }
}
