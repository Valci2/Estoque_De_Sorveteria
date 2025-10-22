#include "Loja.h"
#include <iostream>

void Loja::iniciar(){
    int escolha = 0;
    do {
        std::cout << "====== Loja ======" << std::endl;
        std::cout << "[1] Adicionar Produtos" << std::endl;
        std::cout << "[2] Listar Produtos" << std::endl;
        std::cout << "[3] Atualizar Produtos" << std::endl;
        std::cout << "[4] Apagar Produtos" << std::endl;
        std::cout << "[5] Sair do programa" << std::endl;
        std::cin >> escolha;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
        }
    } while (escolha != 5);
}