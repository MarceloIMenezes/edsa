/************************************************************
*   EDSA - EFFICIENT DISTRIBUTION SYSTEM ALGORITHM
*       Igor Correa Rodrigues       - UFJF
*       João Stephan Silva Maurício - UFJF
*       Marcelo Ian Rezende Menezes - UFJF
************************************************************/
#include <iostream>
#include <fstream>

#include "Menu.hpp"

#define EXIT_INVAL_ARGC 1
#define EXIT_FILE_FAIL  2
#define EXIT_READ_FAIL  3

#define OPEN_FILE(fileObj, fileName)                                           \
    do {                                                                       \
        fileObj.open(fileName);                                                \
                                                                               \
        if (!fileObj.is_open()) {                                              \
            std::cerr << programName                                           \
                << ": não foi possível abrir o arquivo `"                      \
                << fileName << "`\n";                                          \
            return EXIT_FILE_FAIL;                                             \
        }                                                                      \
    } while (0)

int main(int argc, char *argv[])
{
    const char *programName = *argv;

    if (argc != 3) {
        std::cerr << "Uso: " << programName
                  << " ARQUIVO_ENTRADA ARQUIVO_SAIDA\n";
        return EXIT_INVAL_ARGC;
    }

    std::ifstream infile;
    std::ofstream outfile;

    OPEN_FILE(infile,  argv[1]);
    OPEN_FILE(outfile, argv[2]);

    Grafo g = Grafo::fromCsv(infile);
    try {
        std::cin.exceptions(std::istream::failbit | std::istream::badbit);
        Menu::run(g, outfile);
    } catch (const std::istream::failure& e) {
        std::cerr << "Falha de leitura\n";
        std::cerr << "Saindo...\n";
        return EXIT_READ_FAIL;
    }
    return 0;
}
