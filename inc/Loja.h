#pragma once
#include "Produto.h"

class Loja {
    private:
        Produto produtos;

    public:
        Loja() = default;
        void iniciar();
        void adicionar_produtos();
        void listar_produtos();
        void atualizar_produto();
        void remover_produto();
        void sair();
};