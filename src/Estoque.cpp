#include "Estoque.h"
#include <string>

bool Estoque::adicionar_produto(std::string nome, std::string marca, std::string sabor, std::string data_de_validade, double preco, int quantidade) {

    int id = static_cast<int>(produtos_em_estoque.size()) + 1;
    std::string codigo_do_produto = gerar_codigo_aleatorio();
    Produto produto(id, nome, marca, sabor, data_de_validade, preco, quantidade, codigo_do_produto);
    bool existe = verificar_produto_existe(produto);
    if (existe) {
        return true;
    }
    produtos_em_estoque.push_back(produto);
    return false;
}

bool Estoque::verificar_produto_existe(Produto &produto) {
    for (auto &p : produtos_em_estoque) {
        if (p.get_nome() == produto.get_nome() && p.get_marca() == produto.get_marca() && p.get_sabor() == produto.get_sabor() && p.get_data_de_validade() == produto.get_data_de_validade() && p.get_preco() == produto.get_preco()) {
            // logica da troca
            p.set_quantidade(p.get_quantidade() + produto.get_quantidade());
            return true;
        }
    }
    return false;
}

bool Estoque::atualizar_produto(Produto &produto) {
    bool existe = verificar_produto_existe(produto);
    if (existe) {
        remover_produto(produto.get_id() - 1);
        return true;
    }
    produtos_em_estoque[produto.get_id() - 1] = produto;
    return false;
}

bool Estoque::remover_produto(int id) {

    produtos_em_estoque.erase(produtos_em_estoque.begin() + id);

    // Reatribui IDs (sua lógica original)
    for (size_t i = id; i < produtos_em_estoque.size(); i++) {
    // Apaga o produto
        produtos_em_estoque[i].set_id(static_cast<int>(i + 1));
    }
}

std::string Estoque::gerar_codigo_aleatorio() {
    const std::string CHARSET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::uniform_int_distribution<> dis(0, CHARSET.length() - 1);
    std::string codigo;
    codigo.reserve(7);
    for (int i = 0; i < 7; ++i) {
        codigo += CHARSET[dis(gen)];
    }
    return codigo;
}

bool Estoque::codigo_existe(const std::string& codigo) {
    for (auto& produto : produtos_em_estoque) {
        if (produto.get_codigo_do_produto() == codigo) {
            return true;
        }
    }
    return false;
}

// Retorna todos os produtos (para a Interface ler e imprimir)
std::vector<Produto> Estoque::get_todos_os_produtos() {
    return produtos_em_estoque;
}