#include "interface/UIadm.h"
#include "interface/UIestoque.h"

#include <iostream>

void UIadm::iniciar() {
    std::cout << "+=====================================================+" << std::endl;
    std::cout << "| Ola adm, para confirmar que e voce, digite eu login |" << std::endl;
    std::cout << "+=====================================================+" << std::endl;
    short tentativas = 0;

     do {
        if (ui_logar()) {
            UIestoque estoque;
            estoque.iniciar();
            return;
        }
        tentativas++;
        std::cout << "Senha ou Usuario incorreto" << std::endl;
        std::cout << "Tente Novamente!" << std::endl;
    } while (tentativas < 3);
}

bool UIadm::ui_logar() {
    std::string nome = "";
    std::string senha = "";
    Adm entrar;
    std::cout << "+===================================================+" << std::endl;
    std::cout << "|Nome : ";
    std::cin >> nome;
    std::cout << "|senha : ";
    std::cin >> senha;
    std::cout << "+===================================================+" << std::endl;
    return entrar.logar(nome, senha);
}