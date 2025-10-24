#pragma once
#include "Produto.h"
#include <vector>
#include <string>
#include <random> // <--- ADICIONE ISSO

class Estoque {
private:
    std::vector<Produto> produtos_em_estoque; // vector para manter todos os produtos dentro do estoque

    std::mt19937 gen;

    std::string gerar_codigo_aleatorio();
    bool codigo_existe(const std::string& codigo);

public:
    Estoque() = default;

    bool adicionar_produto(std::string nome, std::string marca, std::string sabor, std::string data_de_validade, double preco, int quantidade);

    bool verificar_produto_existe(Produto &codigo);
    bool atualizar_produto(Produto &produtos);

    std::vector<Produto> get_todos_os_produtos();
    bool remover_produto(int id);
};
