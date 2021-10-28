#include "Menu.hpp"

#include <iostream>

using namespace std;

static void toDots(const Grafo& g, std::ofstream& out)
{
    g.toDots(out);
}

static struct MenuOption {
    const char *optName;
    void (*action)(const Grafo& g, std::ofstream&);
} menuOpts[] = {
    { "To dots", toDots }
};

#define OPTS_SIZE (sizeof(menuOpts) / sizeof(MenuOption))

#define IS_VALID(opt) (opt <= OPTS_SIZE)

#define SAIR 0

void Menu::run(const Grafo& g, std::ofstream &out)
{
    std::string tmpBuf;
    size_t selectedOpt;

    while (true) {
        std::cout << "*********************************************\n";
        std::cout << "** Efficient Distribution System Algorithm **\n";
        std::cout << "*********************************************\n";

        for (size_t i = 0; i < OPTS_SIZE; ++i) {
            std::cout << (i + 1) << " - " << menuOpts[i].optName << '\n';
        }
        std::cout << SAIR << " - Sair\n";

        std::cout << "\nR: ";

        std::getline(std::cin, tmpBuf);

        try {
            selectedOpt = std::stoul(tmpBuf);
        } catch (const std::invalid_argument& e) {
            std::cerr << "** Entrada inválida **\n\n";
            continue;
        }

        if (IS_VALID(selectedOpt)) {
            if (selectedOpt == SAIR) {
                return;
            }
            (*menuOpts[selectedOpt - 1].action)(g, out);
            out.flush();
        } else {
            std::cerr << " ** OPÇÃO INVÁLIDA **\n\n";
        }
    }
}
