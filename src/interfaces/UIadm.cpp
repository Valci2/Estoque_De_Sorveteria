#include "interface/UIadm.h"
#include "negocio/Adm.h"
#include <iostream>

void UIadm::iniciar() {
    Adm adm;

    int escolha = 0;
    while (escolha != 5) {
        std::cout << "[1] Criar novo adm" << std::endl;
        std::cout << "[2] Logar com conta adm" << std::endl;
        std::cout << "[3] Atualizar conta adm" << std::endl;
        std::cout << "[4] Deletar Algum adm" << std::endl;
        std::cout << "[5] Sair" << std::endl;
        std::cin >> escolha;
        switch (escolha) {
            case 1: ui_criar(); break;
            case 2: ui_logar(); break;
            case 3: ui_atualizar(); break;
            case 4: ui_deletar(); break;
            default: std::cout << "Opcao invalida" << std::endl; break;
        }
    }
}

void ui_criar() {
}

void logar() {
}