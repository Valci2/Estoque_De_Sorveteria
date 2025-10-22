#include "Estoque.h"
#include <iostream>
#include <limits> // Fornece limites numéricos para os tipos primitivos (como int, float, etc.).

const std::vector<std::string> produtos_disponiveis = {
    {"Sorvete"},
    {"Picole"},
    {"Acai"},
    {"Smoothie"},
    {"Milkshake"},
    {"Iogurte"}
};

// limpa a entrada de uma resposta errada
void limpar_entrada() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Estoque::iniciar() {
    int escolha = 0;
    do {
        // menu das escolhas disponiveis
        std::cout << "====== Estoque ======" << std::endl;
        std::cout << "[1] Adicionar Produtos" << std::endl;
        std::cout << "[2] Listar Produtos" << std::endl;
        std::cout << "[3] Atualizar Produtos" << std::endl;
        std::cout << "[4] Apagar Produtos" << std::endl;
        std::cout << "[5] Sair do programa" << std::endl;
        std::cin >> escolha;
        if (std::cin.fail()) {
            limpar_entrada();
        }
        std::string produto;

        // escolhas disponiveis
        switch (escolha) {
            case 1:
                menu_dos_produtos(produtos_disponiveis);
                adicionar_produtos(produtos_disponiveis);
                break;
            case 2:
                listar_produtos();
        }
    } while (escolha != 5);
}

void Estoque::menu_dos_produtos(const std::vector<std::string> &produtos) {
    std::cout << "===== Produtos =====" << std::endl;
    for (int i = 0; i < produtos.size(); i++) {
        std::cout << "[" << i + 1 << "] " << produtos[i] << std::endl;
    }
}

void Estoque::adicionar_produtos(const std::vector<std::string> &produtos) {
    int id = produtos_em_estoque.size() + 1;
    std::string nome;
    std::string marca;
    std::string sabor;
    std::string data_de_validade;
    int validade_apos_aberto = 0;
    double preco = 0;

    int escolha_do_produto = 0;
    do {
        std::cout << "Escolha: ";
        std::cin >> escolha_do_produto;
        if (std::cin.fail()) {
            limpar_entrada();
        }
    } while (escolha_do_produto < 1 || escolha_do_produto > produtos.size());

    // Define o nome do produto (que já foi previamnete definido)
    nome = produtos[escolha_do_produto - 1];

    // marca
    std::cout << "Qual a marca do produto: ";
    std::cin >> marca;

    // sabor
    std::cout << "Qual o sabor: ";
    std::cin >> sabor;

    // data de validade
    std::cout << "Qual a data de validade. Ex(12/09/25): ";
    std::cin >> data_de_validade;

    // validade apos aberto
    std::cout << "validade apos aberto: ";
    std::cin >> validade_apos_aberto;
    limpar_entrada();

    // preco
    std::cout << "preco: ";
    std::cin >> preco;
    limpar_entrada();

    // cria o produto
    Produto produto_criado(id, nome, marca, sabor, data_de_validade, validade_apos_aberto, preco);

    // adiciona ao estoque
    produtos_em_estoque.push_back(produto_criado);
}

void Estoque::listar_produtos() {
    std::cout << "====== Produtos em estoque =====" << std::endl;
    std::cout << "id  |nome"  << std::endl;
    for (int i = 0; i < produtos_em_estoque.size(); i++) {
        std::cout << produtos_em_estoque[i].get_id() << "  |" << produtos_em_estoque[i].get_nome() << std::endl;
    }
}