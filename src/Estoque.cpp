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
    // Mesmo produto (marca/sabor), mesmo lote (validade e preço)
    for (size_t i = 0; i < (int) produtos_em_estoque.size(); i++) {
        if (nome == produtos_em_estoque[i].get_nome() &&
            marca == produtos_em_estoque[i].get_marca() &&
            sabor == produtos_em_estoque[i].get_sabor() &&
            data_de_validade == produtos_em_estoque[i].get_data_de_validade() &&
            preco == produtos_em_estoque[i].get_preco()) {
            // Mesmo lote → soma quantidade
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
        // Menu das escolhas disponiveis
        std::cout << "====== Estoque ======" << std::endl;
        std::cout << "[1] Adicionar Produtos" << std::endl;
        std::cout << "[2] Listar Produtos" << std::endl;
        std::cout << "[3] Atualizar Produtos" << std::endl;
        std::cout << "[4] Apagar Produtos" << std::endl;
        std::cout << "[5] Salvar e sair" << std::endl;
        std::cout << "Escolha: ";
        escolha = ler_valor<int>("Escolha: ");

        // escolhas disponiveis
        switch (escolha) {
            case 1: menu_dos_produtos(produtos_disponiveis);
                adicionar_produtos(produtos_disponiveis);
                break;
            case 2: listar_produtos();
                break;
            case 3: atualizar_produto();
                break;
            case 4: remover_produto();
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

    // Gera um código e garante que ele seja único
    std::string codigo_do_produto;
    do {
        codigo_do_produto = gerar_codigo_aleatorio();
    } while (codigo_existe(codigo_do_produto)); // Loop até encontrar um código único

    std::cout << "Produto novo. Código gerado: " << codigo_do_produto << std::endl;

    // Verifica se o produto existe
    if (!verificar_produtos(nome, marca, sabor, data_de_validade, preco, quantidade)) {
        // adiciona o produto no estoque
        Produto produto_criado(id, nome, marca, sabor, data_de_validade, preco, quantidade, codigo_do_produto); // cria o produto
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
    for (auto &p: produtos_em_estoque) {
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

// ============================== Atualizar o produto do estoque ==============================
void Estoque::atualizar_produto() {

    // lista todos os produtos para o usuario saber quais itens estão no estoque
    listar_produtos();

    // verifica se o produto está vazio
    if (produtos_em_estoque.empty()) return;

    // Pego o Id que ele quer atualizar
    int id = ler_valor<int>("Digite o ID do produto a atualizar: ") - 1;

    // verifica o ID
    if (id >= 1 && id <= static_cast<int>(produtos_em_estoque.size())) {
        std::cout << "Atualizando produto " << produtos_em_estoque[id].get_nome() << "...\n";
        std::string marca = ler_linha("Nova Marca: ");
        std::string sabor = ler_linha("Novo Sabor: ");
        std::string data_de_validade = ler_linha("Nova validade: ");
        auto preco = ler_valor<double>("Novo Preco: R$");
        auto quantidade = ler_valor<int>("Quantidade: ");

        // se o produto já existe, e existir um produto igual no vector ele deleta o da vector e adiciona na quantidade do produto já existente
        if (verificar_produtos(produtos_em_estoque[id].get_nome(), marca, sabor, data_de_validade, preco, quantidade)) {
            remove_o_produto(id);
            return;
        }

        // caso o produto não exista
        produtos_em_estoque[id].set_marca(marca);
        produtos_em_estoque[id].set_sabor(sabor);
        produtos_em_estoque[id].set_data_de_validade(data_de_validade);
        produtos_em_estoque[id].set_preco(preco);
        produtos_em_estoque[id].set_quantidade(quantidade);
        std::cout << "Produto atualizado com sucesso!" << std::endl;
        return;
    }
    // Caso o Id não seja encontrado
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

    // Verifica se o ID existe dentro do tamanho da lista
    if (id < 0 || id > (int) produtos_em_estoque.size()) {
        std::cout << "Esse ID nao existe!" << std::endl;
        return;
    }

    // Apaga o produto
    produtos_em_estoque.erase(produtos_em_estoque.begin() + id);

    // Reatribui IDs
    for (size_t i = id; i < produtos_em_estoque.size(); i++) {
        produtos_em_estoque[i].set_id(id + 1);
        id++;
    }
}

// Função privada para gerar um código aleatório de 7 caracteres
std::string Estoque::gerar_codigo_aleatorio() {
    // Define os caracteres permitidos no código
    const std::string CHARSET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    // Cria uma distribuição uniforme para escolher índices do CHARSET
    std::uniform_int_distribution<> dis(0, CHARSET.length() - 1);

    std::string codigo;
    codigo.reserve(7);

    for (int i = 0; i < 7; ++i) {
        codigo += CHARSET[dis(gen)]; // 'gen' é o membro da classe que inicializamos
    }
    return codigo;
}

// Função privada para verificar se um código já existe no estoque
bool Estoque::codigo_existe(const std::string& codigo) {
    // Itera por todos os produtos no vetor
    for (auto& produto : produtos_em_estoque) {
        // Aqui você USA o getter que criou na classe Produto
        if (produto.get_codigo_do_produto() == codigo) {
            return true; // Encontrou um código igual
        }
    }
    return false; // Não encontrou o código, é único
}