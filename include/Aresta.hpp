#ifndef ARESTA_HPP
#define ARESTA_HPP

#include <string>

using idvertice_t = size_t;

class Aresta {
    private:
        idvertice_t _idDestino;

    public:
        Aresta(idvertice_t idVertice);

        idvertice_t idDestino() const;
};

#endif // ARESTA_HPP
