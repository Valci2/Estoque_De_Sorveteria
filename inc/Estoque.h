#pragma once
#include "Produto.h"
#include <vector>

class Estoque {
    private:
        std::vector<Produto> produtos_em_estoque; // vector para manter todos os produtos dentro do estoque
    public:
        Estoque() = default;
        void iniciar();

        // adicionar produto no estoque
        void menu_dos_produtos(const std::vector<std::string> &produtos);
        void adicionar_produtos(const std::vector<std::string> &produtos);

        void listar_produtos();

        void atualizar_produto();

        void remover_produto();
        void sair();
};
