#include "Aresta.hpp"

Aresta::Aresta(idvertice_t idVertice):
    _idDestino(idVertice)
{
}


idvertice_t Aresta::idDestino() const
{
    return this->_idDestino;
}
