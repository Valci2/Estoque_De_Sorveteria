#include "Estoque.h"
#include <iostream>
#include <limits> // Fornece limites numéricos para os tipos primitivos (como int, float, etc.).
#include <iomanip> // std::setw, std::left, std::right

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

// Lê um valor genérico com validação de tipo
template <typename T>
T ler_valor(const std::string& mensagem) {
    T valor;
    while (true) {
        std::cout << mensagem;
        std::cin >> valor;
        if (!std::cin.fail()) {
            limpar_entrada();
            return valor;
        }
        std::cout << "Entrada inválida. Tente novamente.\n";
        limpar_entrada();
    }
}

// Lê uma string completa (com espaços)
std::string ler_linha(const std::string& mensagem) {
    std::string linha;
    std::cout << mensagem;
    std::getline(std::cin, linha);
    while (linha.empty()) {
        std::cout << "Campo vazio! Digite novamente: ";
        std::getline(std::cin, linha);
    }
    return linha;
}

// ======================== FUNÇÂO PRINCIPAL ========================
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

        // escolhas disponiveis
        switch (escolha) {
            case 1:
                menu_dos_produtos(produtos_disponiveis);
                adicionar_produtos(produtos_disponiveis);
                break;
            case 2:
                listar_produtos();
                break;
            case 3:
                atualizar_produto();
                break;
            case 4:
                remover_produto();
                break;
        }
    } while (escolha != 5);
}

// Mostra os possiveis produtos para se colocar no estoque, acho que deveria deixar o dono escolher
void Estoque::menu_dos_produtos(const std::vector<std::string> &produtos) {
    std::cout << "===== Produtos =====" << std::endl;
    for (size_t i = 0; i < produtos.size(); i++) {
        std::cout << "[" << i + 1 << "] " << produtos[i] << std::endl;
    }
    std::cout << "=====================" << std::endl;
}

// adicona um novo produto
void Estoque::adicionar_produtos(const std::vector<std::string> &produtos) {

    // lê a escolha que o adm quer fazer
    int escolha = ler_valor<int>("Escolha o produto pelo número: ");
    while (escolha < 1 || escolha > (int)produtos.size()) {
        std::cout << "Escolha inválida! Tente novamente." << std::endl;
        escolha = ler_valor<int>("Escolha o produto pelo número: ");
    }

    // Define as caracteristicas do produto
    int id = static_cast<int> (produtos_em_estoque.size()) + 1;
    std::string nome = produtos[escolha - 1];
    std::string marca = ler_linha("Marca: ");
    std::string sabor = ler_linha("Sabor: ");
    std::string data_de_validade = ler_linha("Data de validade (EX: 02/10/2025): ");
    auto preco = ler_valor<double>("Preco: R$");
    auto quantidade = ler_valor<int>("Quantidade: ");

    // adiciona o produto no estoque
    Produto produto_criado(id, nome, marca, sabor, data_de_validade, preco, quantidade); // cria o produto
    produtos_em_estoque.push_back(produto_criado); // adicionar ao estoque
}


void Estoque::listar_produtos() {
    using std::cout;
    using std::endl;
    using std::setw;
    using std::left;
    using std::right;

    if (produtos_em_estoque.empty()) {
        cout << "Não temos produtos em estoque" << endl;
        return;
    }

    cout << "================================= Produtos em estoque =================================" << endl;
    cout << setw(5)  << left << "ID"
         << setw(15) << left << "Nome"
         << setw(15) << left << "Marca"
         << setw(15) << left << "Sabor"
         << setw(15) << left << "Validade"
         << setw(10) << right << "Preço"
         << setw(12) << right << "Qtd" << endl;
    cout << std::string(87, '-') << endl;

    for (auto &p: produtos_em_estoque) {
        cout << setw(5)  << left  << p.get_id()
             << setw(15) << left  << p.get_nome()
             << setw(15) << left  << p.get_marca()
             << setw(15) << left  << p.get_sabor()
             << setw(15) << left  << p.get_data_de_validade()
             << setw(10) << right << std::fixed << std::setprecision(2) << p.get_preco()
             << setw(12) << right << p.get_quantidade()
             << endl;
    }
}

// atualizar o produto do estoque
void Estoque::atualizar_produto() {

    listar_produtos();
    if (produtos_em_estoque.empty()) return;

    int id = ler_valor<int>("Digite o ID do produto a atualizar: ");
    for (auto& p : produtos_em_estoque) {
        if (p.get_id() == id) {
            std::cout << "Atualizando produto " << p.get_nome() << "...\n";
            std::string marca = ler_linha("Nova Marca: ");
            std::string sabor = ler_linha("Novo Sabor: ");
            std::string data_de_validade = ler_linha("Nova validade: ");
            auto preco = ler_valor<double>("Novo Preco: R$");
            auto quantidade = ler_valor<int>("Quantidade: ");
            p.set_marca(marca);
            p.set_sabor(sabor);
            p.set_data_de_validade(data_de_validade);
            p.set_preco(preco);
            p.set_quantidade(quantidade);
            std::cout << "Produto atualizado com sucesso!" << std::endl;
            return;
        }
    }
    std::cout << "Produto com ID " << id << " não encontrado." << std::endl;
}

void Estoque::remover_produto() {

}
