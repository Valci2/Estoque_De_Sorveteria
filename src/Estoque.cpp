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
    {"Iogurte"},
    {"Paleta"}
};

// limpa a entrada de uma resposta errada
void limpar_entrada() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Lê um valor genérico com validação de tipo
template<typename T>
T ler_valor(const std::string &mensagem) {
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
std::string ler_linha(const std::string &mensagem) {
    std::string linha;
    std::cout << mensagem;
    std::getline(std::cin, linha);
    while (linha.empty()) {
        std::cout << "Campo vazio! Digite novamente: ";
        std::getline(std::cin, linha);
    }
    return linha;
}

bool Estoque::verificar_produtos(std::string &nome, std::string &marca, std::string &sabor,
                                 std::string &data_de_validade, double preco, int quantidade) {
    for (size_t i = 0; i < (int) produtos_em_estoque.size(); i++) {
        if (nome == produtos_em_estoque[i].get_nome() &&
            marca == produtos_em_estoque[i].get_marca() &&
            sabor == produtos_em_estoque[i].get_sabor() &&
            data_de_validade == produtos_em_estoque[i].get_data_de_validade() &&
            preco == produtos_em_estoque[i].get_preco()) {
            produtos_em_estoque[i].set_quantidade(produtos_em_estoque[i].get_quantidade() + quantidade);
            return true;
        }
    }
    return false;
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
        std::cout << "[5] Salvar e sair" << std::endl;
        std::cout << "Escolha: ";
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
    while (escolha < 1 || escolha > (int) produtos.size()) {
        std::cout << "Escolha inválida! Tente novamente." << std::endl;
        escolha = ler_valor<int>("Escolha o produto pelo número: ");
    }

    // Define as caracteristicas do produto
    int id = static_cast<int>(produtos_em_estoque.size()) + 1;
    std::string nome = produtos[escolha - 1];
    std::string marca = ler_linha("Marca: ");
    std::string sabor = ler_linha("Sabor: ");
    std::string data_de_validade = ler_linha("Data de validade (EX: 02/10/2025): ");
    auto preco = ler_valor<double>("Preco: R$");
    auto quantidade = ler_valor<int>("Quantidade: ");

    // Verifica se o produto existe
    if (!verificar_produtos(nome, marca, sabor, data_de_validade, preco, quantidade)) {
        // adiciona o produto no estoque
        Produto produto_criado(id, nome, marca, sabor, data_de_validade, preco, quantidade); // cria o produto
        produtos_em_estoque.push_back(produto_criado); // adicionar ao estoque
    }
}

// ============================== Lista os produtos ==============================
void Estoque::listar_produtos() {
    using std::cout;
    using std::endl;
    using std::setw;
    using std::left;
    using std::right;

    // verifica se a lista tá vazia
    if (produtos_em_estoque.empty()) {
        cout << "Não temos produtos em estoque" << endl;
        return;
    }

    // mostra os produtos em estoque
    cout << "================================= Produtos em estoque =================================" << endl;

    // centraliza os status do produto
    cout << setw(5) << left << "ID"
            << setw(15) << left << "Nome"
            << setw(15) << left << "Marca"
            << setw(15) << left << "Sabor"
            << setw(15) << left << "Validade"
            << setw(10) << right << "Preço"
            << setw(12) << right << "Qtd" << endl;
    cout << std::string(87, '-') << endl;

    // centraliza os itens do produto
    for (auto &p: produtos_em_estoque) {
        cout << setw(5) << left << p.get_id()
                << setw(15) << left << p.get_nome()
                << setw(15) << left << p.get_marca()
                << setw(15) << left << p.get_sabor()
                << setw(15) << left << p.get_data_de_validade()
                << setw(10) << right << std::fixed << std::setprecision(2) << p.get_preco()
                << setw(12) << right << p.get_quantidade()
                << endl;
    }
}

// ============================== Atualizar o produto do estoque ==============================
void Estoque::atualizar_produto() {

    listar_produtos();
    if (produtos_em_estoque.empty()) return;

    int id = ler_valor<int>("Digite o ID do produto a atualizar: ") - 1;

    if (id >= 1 && id <= produtos_em_estoque.size()) {
        std::cout << "Atualizando produto " << produtos_em_estoque[id].get_nome() << "...\n";
        std::string marca = ler_linha("Nova Marca: ");
        std::string sabor = ler_linha("Novo Sabor: ");
        std::string data_de_validade = ler_linha("Nova validade: ");
        auto preco = ler_valor<double>("Novo Preco: R$");
        auto quantidade = ler_valor<int>("Quantidade: ");

        if (verificar_produtos(produtos_em_estoque[id].get_nome(), marca, sabor, data_de_validade, preco, quantidade)) {
            remove_o_produto(id);
            return;
        }

        produtos_em_estoque[id].set_marca(marca);
        produtos_em_estoque[id].set_sabor(sabor);
        produtos_em_estoque[id].set_data_de_validade(data_de_validade);
        produtos_em_estoque[id].set_preco(preco);
        produtos_em_estoque[id].set_quantidade(quantidade);
        std::cout << "Produto atualizado com sucesso!" << std::endl;
        return;
    }
    std::cout << "Produto com ID " << id << " não encontrado." << std::endl;
}

// ============================== Remover Produto ==============================
void Estoque::remover_produto() {

    // Verifica se a lista não é vazia
    if (produtos_em_estoque.empty()) {
        std::cout << "Nao existe nenhum produto" << std::endl;
        return;
    }

    // Mostrar a lista de produtos
    listar_produtos();

    // Pega o Id do produto
    int id = ler_valor<int>("Digite o ID do produto: ") - 1;
    remove_o_produto(id);
}

void Estoque::remove_o_produto(int id) {

    // verifica se o ID existe dentro do tamanho da lista
    if (id < 0 || id > (int)produtos_em_estoque.size()) {
        std::cout << "Esse ID nao existe!" << std::endl;
        return;
    }

    produtos_em_estoque.erase(produtos_em_estoque.begin() + id);

    for (size_t i = id; i < produtos_em_estoque.size(); i++) {
        produtos_em_estoque[i].set_id(id + 1);
        id++;
    }
}