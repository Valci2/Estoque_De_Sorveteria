#include "interface/UIadm.h"
#include "interface/UIestoque.h"
#include "negocio/Adm.h"
#include <iostream>

void UIadm::iniciar() {

    std::cout << "+======================================================+" << std::endl;
    std::cout << "| Ola ADM, Para Confirmar Que E Voce, Digite Seu Login |" << std::endl;

    // loop para as tentativas de login
    short tentativas = 3;
    do {
        if (ui_logar()) {
            std::cout << "Agora que confirmamos que voce eh o adm pode alterar o que quiser" << std::endl;
            UIestoque estoque;
            estoque.iniciar();
            return;
        }

        tentativas--;
        std::cout << "Usuario ou Senha incorreto" << std::endl;

        if (tentativas > 0) {
            std::cout << "Tente Novamente!" << std::endl;
            std::cout << "Tentativas restantes " << tentativas << std::endl;
        }
    } while (tentativas > 0);

    std::cout << "Numero de tentativas exedido" << std::endl;
    std::cout << "voce nao e o adm" << std::endl;
}

bool UIadm::ui_logar() {

    // adm principal
    std::string nome_adm_primario = "adm";
    std::string senha_adm_primario = "adm";
    Adm Primario(1, nome_adm_primario, senha_adm_primario, "adm@gmail.com");

    // pega os dados do usuario
    std::string nome = "";
    std::string senha = "";
    std::cout << "+======================================================+" << std::endl;
    std::cout << " Nome : ";
    std::cin >> nome;
    std::cout << " senha : ";
    std::cin >> senha;
    std::cout << "+======================================================+" << std::endl;

    // retorna true se ele acertar a senha e o usuario, false se não.
    return Primario.logar(nome, senha);
}