#include "Interface.h"
#include <iostream>
#include <iomanip> // std::setw, std::left, std::right
#include <cstdlib>

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
            case 5: 
                std::cout << "Salvando dados em [estoque.csv]..." << std::endl;
                m_estoque.salvarParaCSV("estoque.csv");
                std::cout << "Saindo do programa." << std::endl; break;
                
            default: std::cout << "Opção inválida." << std::endl; break;
        }

        if (escolha != 5) {
            std::cout << "\n\nPressione ENTER para continuar...";
            std::cin.get();
        }
        
    } while (escolha != 5);
}

void Interface::exibir_menu_principal() {
    system("cls");
    // Menu das escolhas disponiveis
    std::cout << "+-----------------------------------+\n";
    std::cout << "|       ESTOQUE DA SORVETERIA       |\n";
    std::cout << "+-----------------------------------+\n";
    std::cout << "| [1] Adicionar Produtos            |\n";
    std::cout << "| [2] Listar Produtos               |\n";
    std::cout << "| [3] Atualizar Produtos            |\n";
    std::cout << "| [4] Apagar Produtos               |\n";
    std::cout << "| [5] Salvar e sair                 |\n";
    std::cout << "+-----------------------------------+\n";
}

// ====================== Funções da UI ======================

void Interface::ui_adicionar_produtos() {
    system("cls");
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
    system("cls");
    using std::cout;
    using std::endl;
    using std::setw;
    using std::left;
    using std::right;

    // verifica se a lista tá vazia
    if (m_estoque.get_todos_os_produtos().empty()) {
        cout << "Nao temos produtos em estoque" << endl;
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
            << setw(10) << right << "Preco"
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
        system("cls");
        std::cout << "Nao temos produtos em estoque" << std::endl;
        return;
    }

    ui_listar_produtos();

    int id = ler_valor<int>("Digite o ID do produto que voce quer atualizar: ");
    if (id >= 1 && id <= static_cast<int>(m_estoque.get_todos_os_produtos().size())) {
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
        system("cls");
        std::cout << "Nao temos produtos em estoque" << std::endl;
        return;
    }

    ui_listar_produtos();

    int id = ler_valor<int>("Digite o ID do produto que voce quer remover: ");
    if (id >= 1 && id <= static_cast<int>(m_estoque.get_todos_os_produtos().size())) {
        m_estoque.remover_produto(id - 1);
        std::cout << "Produto removido com sucesso." << std::endl;
    } else {
        std::cout << "Id do produto nao encontrado" << std::endl;
    }
}

void Interface::menu_dos_produtos(const std::vector<std::string> &produtos) {
    std::cout << "+--------------------+\n";
    std::cout << "|      PRODUTOS      |\n";
    std::cout << "+--------------------+\n";
    for (size_t i = 0; i < produtos.size(); i++) {
        std::cout << "| [" << i + 1 << "] " << std::setw(13) << std::left << produtos[i] << " |\n";
    }
    std::cout << "+--------------------+\n";
}
