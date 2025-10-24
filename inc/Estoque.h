#pragma once
#include "Produto.h"
#include <vector>

class Estoque {
private:
    std::vector<Produto> produtos_em_estoque; // vector para manter todos os produtos dentro do estoque
public:
    Estoque() = default;

    // função que inicia o as escolhas do usuario
    void iniciar();
    bool verificar_produtos(std::string &nome, std::string &marca, std::string &sabor, std::string &data_de_validade, double preco, int quantidade);

    // adicionar produto no estoque
    void menu_dos_produtos(const std::vector<std::string> &produtos);
    void adicionar_produtos(const std::vector<std::string> &produtos);

    // lista os produtos dentro da vector dos produtos_em_estoque que está dentro da classe
    void listar_produtos();

    // atualiza um produto que já está dentro da vector
    void atualizar_produto();

    // remove o produto da vector
    void remover_produto();
    void remove_o_produto(int id);

    // ================================= IMPLEMENTAÇÂO PARA SALVAR O ARQUIVO =================================
    void salvar_arquivo();
    void carregar_arquivo();
};
