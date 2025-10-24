#include "Interface.h"
#include <iostream>
#include <iomanip> // std::setw, std::left, std::right

// limpa a entrada de uma resposta errada
void Interface::limpar_entrada() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Lê um valor genérico com validação de tipo
template<typename T>
T Interface::ler_valor(const std::string &mensagem) {
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
std::string Interface::ler_linha(const std::string &mensagem) {
    std::string linha;
    std::cout << mensagem;
    std::getline(std::cin, linha);
    while (linha.empty()) {
        std::cout << "Campo vazio! Digite novamente: ";
        std::getline(std::cin, linha);
    }
    return linha;
}


void Interface::iniciar() {
    int escolha = 0;
    do {
        exibir_menu_principal();
        escolha = ler_valor<int>("Escolha: ");
        switch (escolha) {
            case 1: ui_adicionar_produtos(); break;
            case 2: ui_listar_produtos(); break;
            case 3: ui_atualizar_produto(); break;
            case 4: ui_remover_produto(); break;
            case 5: std::cout << "Salvando e saindo..." << std::endl; break;
            default: std::cout << "Opção inválida." << std::endl; break;
        }
        std::cout << "\n"; // Espaço entre as operações
    } while (escolha != 5);
}

void Interface::exibir_menu_principal() {
    // Menu das escolhas disponiveis
    std::cout << "====== Estoque ======" << std::endl;
    std::cout << "[1] Adicionar Produtos" << std::endl;
    std::cout << "[2] Listar Produtos" << std::endl;
    std::cout << "[3] Atualizar Produtos" << std::endl;
    std::cout << "[4] Apagar Produtos" << std::endl;
    std::cout << "[5] Salvar e sair" << std::endl;
}

// ====================== Funções da UI ======================

void Interface::ui_adicionar_produtos() {
    menu_dos_produtos(produtos_disponiveis);

    int escolha = ler_valor<int>("Escolha o produto pelo número: ");
    while (escolha < 1 || escolha > static_cast<int>(produtos_disponiveis.size())) {
        std::cout << "Escolha inválida! Tente novamente." << std::endl;
        escolha = ler_valor<int>("Escolha o produto pelo número: ");
    }

    // 1. Coleta todos os dados da UI
    std::string nome = produtos_disponiveis[escolha - 1];
    std::string marca = ler_linha("Marca: ");
    std::string sabor = ler_linha("Sabor: ");
    std::string data_de_validade = ler_linha("Data de validade (EX: 02/10/2025): ");
    auto preco = ler_valor<double>("Preco: R$");
    auto quantidade = ler_valor<int>("Quantidade: ");

    // 2. Manda a lógica de Estoque processar
    bool resultado = m_estoque.adicionar_produto(nome, marca, sabor, data_de_validade, preco, quantidade);
    if (resultado) {
        std::cout << "O produto ja existe e por isso a quantidade sera atualizada" << std::endl;
    } else {
        std::cout << "Produto " << nome << " adicionado com sucesso!" << std::endl;
    }
}

void Interface::ui_listar_produtos() {
    using std::cout;
    using std::endl;
    using std::setw;
    using std::left;
    using std::right;

    // verifica se a lista tá vazia
    if (m_estoque.get_todos_os_produtos().empty()) {
        cout << "Não temos produtos em estoque" << endl;
        return;
    }

    // mostra os produtos em estoque
    cout << "================================================ Produtos em estoque ================================================" << endl;

    // centraliza os status do produto
    cout << setw(7) << left << "ID"
            << setw(15) << left << "Nome"
            << setw(15) << left << "Marca"
            << setw(15) << left << "Sabor"
            << setw(15) << left << "Validade"
            << setw(10) << right << "Preço"
            << setw(15) << right << "Qtd"
            << setw(25) << right << "Codigo do produto" << endl;
    cout << std::string(117, '-') << endl;

    // centraliza os itens do produto
    for (auto &p: m_estoque.get_todos_os_produtos()) {
        cout << setw(7) << left << p.get_id()
                << setw(15) << left << p.get_nome()
                << setw(15) << left << p.get_marca()
                << setw(15) << left << p.get_sabor()
                << setw(15) << left << p.get_data_de_validade()
                << setw(10) << right << std::fixed << std::setprecision(2) << p.get_preco()
                << setw(15) << right << p.get_quantidade()
                << setw(25) << right << p.get_codigo_do_produto()
                << endl;
    }
}

void Interface::ui_atualizar_produto() {

    // verifica se a lista tá vazia
    if (m_estoque.get_todos_os_produtos().empty()) {
        std::cout << "Não temos produtos em estoque" << std::endl;
        return;
    }

    ui_listar_produtos();

    int id = ler_valor<int>("Digite o ID do produto que voce quer atualizar: ");
    if (id >= 1 && id <= static_cast<int>(m_estoque.get_todos_os_produtos().size() - 1)) {
        std::string nome = m_estoque.get_todos_os_produtos()[id - 1].get_nome();
        std::string marca = ler_linha("Nova Marca: ");
        std::string sabor = ler_linha("Novo Sabor: ");
        std::string data_de_validade = ler_linha("Nova Data de validade (EX: 02/10/2025): ");
        auto preco = ler_valor<double>("Novo Preco: R$");
        auto quantidade = ler_valor<int>("Nova Quantidade: ");
        std::string codigo_do_produto = m_estoque.get_todos_os_produtos()[id - 1].get_codigo_do_produto();

        Produto produto(id, nome, marca, sabor, data_de_validade, preco, quantidade, codigo_do_produto);

        bool existe = m_estoque.atualizar_produto(produto);
        if (existe) {
            std::cout << "Produto ja existe e por isso atualizaremos a quantidade" << std::endl;
        } else {
            std::cout << "Produto atualizado com sucesso" << std::endl;
        }
    } else {
        std::cout << "Id do produto nao encontrado" << std::endl;
    }
}

void Interface::ui_remover_produto() {

    // verifica se a lista tá vazia
    if (m_estoque.get_todos_os_produtos().empty()) {
        std::cout << "Não temos produtos em estoque" << std::endl;
        return;
    }

    ui_listar_produtos();

    int id = ler_valor<int>("Digite o ID do produto que voce quer remover: ");
    if (id >= 1 && id <= static_cast<int>(m_estoque.get_todos_os_produtos().size() - 1)) {
        m_estoque.remover_produto(id - 1);
    }
}

void Interface::menu_dos_produtos(const std::vector<std::string> &produtos) {
    std::cout << "===== Produtos =====" << std::endl;
    for (size_t i = 0; i < produtos.size(); i++) {
        std::cout << "[" << i + 1 << "] " << produtos[i] << std::endl;
    }
    std::cout << "=====================" << std::endl;
}