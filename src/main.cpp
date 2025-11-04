#include "interface/UIestoque.h"
#include "interface/UIadm.h"
#include <iostream>

// adm = usuario e senha
// usuario = usuario e senha

int main() {
    std::cout << "Ola usuario" << std::endl;
    int escolha = 0;

    while (escolha != 1 && escolha != 2) {
        std::cout << "{=========================}" << std::endl;
        std::cout << "|           OLA           |" << std::endl;
        std::cout << "|                         |" << std::endl;
        std::cout << "| Voce eh Usuario ou Adm? |" << std::endl;
        std::cout << "| [1] usuario             |" << std::endl;
        std::cout << "| [2] adm                 |" << std::endl;
        std::cout << "{=========================}" << std::endl;
        std::cout << "escolha: ";
        std::cin >> escolha;


        if (std::cin.fail()) {
            std::cout << "opcao invalida" << std::endl;
            std::cin.clear();
            std::cin.ignore();
        }

        switch (escolha) {
            case 1:
                break;
            case 2:
                UIadm interface_adm;
                interface_adm.iniciar(); // senha e user do adm é adm.
                break;
            default: std::cout << "opcao invalida" << std::endl;
        }
    }

    return 0;
}
