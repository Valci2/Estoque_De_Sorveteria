#pragma once

#include "negocio/Estoque.h"
#include "negocio/Produto.h"
#include <string>

class UIcliente {
private:
    Estoque& meuEstoque;
    std::string usuarioLogado;

    // Funções do menu de login
    void executarCriarConta();
    std::string executarLogin(); 

    // Funções do menu principal
    void executarListarEstoque();
    void executarSolicitarReserva();

    void limpar_terminal();

public:
    UIcliente(Estoque& estoque);

    // Menus
    void mostrarMenuLogin();
    void mostrarMenuPrincipal();
};
