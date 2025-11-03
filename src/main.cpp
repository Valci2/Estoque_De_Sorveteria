#include "../inc/interface/UIestoque.h"
#include <iostream>

// adm = usuario e senha
// usuario = usuario e senha

int main(){
    std::cout << "Ola usuario" << std::endl;
    int escolha = 0;

    while (escolha != 1 && escolha != 2) {

        std::cout << "Voce eh usuario ou adm?" << std::endl;
        std::cout << "[1] usuario" << std::endl;
        std::cout << "[2] adm" << std::endl;
        std::cin >> escolha;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
        }

        switch (escolha) {
            case 1:
                break;
            case 2:
                UIestoque estoque;
                estoque.iniciar();
                break;
        }
    }

    return 0;    
}
