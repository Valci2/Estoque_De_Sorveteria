#include "interface/UIadm.h"
#include "negocio/Adm.h"
#include <iostream>

void UIadm::iniciar() {
    Adm adm;
    std::cout << "[1] Criar novo adm" << std::endl;
    std::cout << "[2] Logar com conta adm" << std::endl;
    std::cout << "[4] Atualizar conta adm" << std::endl;
    std::cout << "[3] Deletar Algum adm" << std::endl;
    std::cout << "[5] Sair" << std::endl;
    int escolha = 0;
    while (escolha != 5) {
        switch (escolha) {
            case 1: ui_criar(); break;
                case 2: ui_logar(); break;
        }
    }
}

void ui_criar() {
}

void logar() {

}