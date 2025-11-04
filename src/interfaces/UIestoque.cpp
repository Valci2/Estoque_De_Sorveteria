#include "../../inc/interface/UIestoque.h"
#include <iostream>
#include <iomanip> // std::setw, std::left, std::right

// ================= Funções auxiliares =================
// limpa a entrada de uma resposta errada
void UIestoque::limpar_entrada() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// apagar texto
void UIestoque::limpar_terminal() {
    #ifdef _WIN32
        system("cls");
    #elif __linux__
        system("clear");
    #endif
}

// split para separar a data
std::vector<std::string> split_data(std::string &datastr, char separador = '/') {

    std::vector<std::string> partes;
    std::stringstream ss(datastr);
    std::string parte;

    while (std::getline(ss, parte, separador)) {
        partes.push_back(parte);
    }

    return partes;
}

// faz uma validação na data
bool validar_data(std::string& data) {
    std::vector<std::string> partes = split_data(data);

    // Verificar se tem 3 partes (dia, mês, ano)
    if (partes.size() != 3) {
        std::cout << "Formato inválido! Use DD/MM/AAAA" << std::endl;
        return false;
    }

    // Converter para números
    int dia, mes, ano;
    try {
        dia = stoi(partes[0]);
        mes = stoi(partes[1]);
        ano = stoi(partes[2]);
    }
    catch (const std::exception& e) {
        std::cout << "Erro: A data deve conter apenas números!" << std::endl;
        return false;
    }

    // Validar dia
    if (dia < 1 || dia > 31) {
        std::cout << "Dia invalido! O dia deve estar entre 1 e 31." << std::endl;
        return false;
    }

    // Validar mês
    if (mes < 1 || mes > 12) {
        std::cout << "Mês inválido! O mês deve estar entre 1 e 12." << std::endl;
        return false;
    }

    // valida o ano
    if (ano < 1 || ano > 9999) {
        std::cout << "ano inválido! O ano " << ano << " esta entre 1 e 9999." << std::endl;
        return false;
    }

    // Validar combinação dia/mês
    // Meses com 30 dias
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) {
        std::cout << "Dia invalido! O mês " << mes << " tem apenas 30 dias." << std::endl;
        return false;
    }

    // Fevereiro
    if (mes == 2) {

        if (dia > 29) {
            std::cout << "Dia inválido! Fevereiro tem no máximo 29 dias." << std::endl;
            return false;
        }

        // Validação simples para ano bissexto
        bool bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
        if (dia == 29 && !bissexto) {
            std::cout << "Dia inválido! " << ano << " não é ano bissexto." << std::endl;
            return false;
        }

        if (dia > 28 && !bissexto) {
            std::cout << "Dia inválido! Fevereiro tem apenas 28 dias em anos não bissextos." << std::endl;
            return false;
        }
    }

    return true;
}

// Lê um valor genérico com validação de tipo (para int, double, etc.)
template<typename T>
T UIestoque::ler_valor(const std::string &mensagem) {
    T valor;
    while (true) {
        std::cout << mensagem;
        std::cin >> valor;

        if (std::cin.fail()) {
            std::cout << "Entrada inválida. Digite um valor numérico.\n";
            limpar_entrada();
        } else {
            // Verifica se há caracteres extras na entrada
            if (std::cin.peek() != '\n') {
                std::cout << "Entrada inválida. Digite apenas números.\n";
                limpar_entrada();
            } else {
                limpar_entrada();
                return valor;
            }
        }
    }
}

// Lê uma string completa (com espaços)
std::string UIestoque::ler_linha(const std::string &mensagem) {
    std::string linha;
    std::cout << mensagem;
    std::getline(std::cin, linha);
    while (linha.empty()) {
        std::cout << "Campo vazio! Digite novamente: ";
        std::getline(std::cin, linha);
    }
    return linha;
}

// ================= Funções principais  =================
// função que inicia a interface do estoque
void UIestoque::iniciar() {
    int escolha = 0;

    do {
        exibir_menu_principal();
        escolha = ler_valor<int>("Escolha: ");
        switch (escolha) {
            case 1: ui_adicionar_produtos(); break;
            case 2: ui_listar_produtos(); break;
            case 3: ui_atualizar_produto(); break;
            case 4: ui_remover_produto(); break;
            default: std::cout << "Opção invalida." << std::endl; break;
        }

        if (escolha != 5) {
            std::cout << "\n\nPressione ENTER para continuar...";
            std::cin.get();
        }

    } while (escolha != 5);

    // salva os arquivos em CSV
    std::cout << "Salvando dados em [estoque.csv]..." << std::endl;
    m_estoque.salvarParaCSV("estoque.csv");
    std::cout << "Saindo do programa." << std::endl;

}

// menu das do que dá pra fazer no estoque
void UIestoque::exibir_menu_principal() {
    limpar_terminal();
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

// ====================== Metodos do CRUD ======================
void UIestoque::ui_adicionar_produtos() {
    limpar_terminal();
    menu_dos_produtos(produtos_disponiveis);

    int escolha = ler_valor<int>("Escolha o produto pelo número: ");
    while (escolha < 1 || escolha > static_cast<int>(produtos_disponiveis.size() + 1)) {
        std::cout << "Escolha inválida! Tente novamente." << std::endl;
        escolha = ler_valor<int>("Escolha o produto pelo número: ");
    }

    if (escolha == (int) produtos_disponiveis.size() + 1) {
        return;
    }

    // 1. Coleta todos os dados da UI
    std::string nome = produtos_disponiveis[escolha - 1];
    std::string marca = ler_linha("Marca: ");
    std::string sabor = ler_linha("Sabor: ");
    std::string data_de_validade = "";

    do {
        data_de_validade = ler_linha("Data de validade (EX: 02/10/2025): ");
        if (validar_data(data_de_validade)) {
            break;
        }
    } while (true);

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

// Função auxiliar para centralizar texto em um campo fixo
std::string centralizar_texto(const std::string& texto, int largura) {
    if ((int)texto.size() >= largura)
        return texto.substr(0, largura);
    int espaco_total = largura - texto.size();
    int espaco_esq = espaco_total / 2;
    int espaco_dir = espaco_total - espaco_esq;
    return std::string(espaco_esq, ' ') + texto + std::string(espaco_dir, ' ');
}

void UIestoque::ui_listar_produtos() {
    limpar_terminal();

    using std::cout;
    using std::endl;

    if (m_estoque.get_todos_os_produtos().empty()) {
        cout << "Nao temos produtos em estoque" << endl;
        return;
    }

    const int largura_total = 120; // largura total da tabela

    cout << endl
         << std::string(largura_total, '=') << endl;
    cout << centralizar_texto("PRODUTOS EM ESTOQUE", largura_total) << endl;
    cout << std::string(largura_total, '=') << endl;

    // Larguras das colunas — aumentadas para dar mais espaçamento
    const int w_id = 6;
    const int w_nome = 16;
    const int w_marca = 16;
    const int w_sabor = 16;
    const int w_validade = 16;
    const int w_preco = 12;
    const int w_qtd = 10;
    const int w_codigo = 28; // mais espaço pro código do produto

    // Cálculo automático do total — caso queira ajustar depois
    const int soma_larguras = w_id + w_nome + w_marca + w_sabor + w_validade + w_preco + w_qtd + w_codigo;
    const int ajuste = largura_total - soma_larguras;

    // Cabeçalho
    cout << centralizar_texto("ID", w_id)
         << centralizar_texto("NOME", w_nome)
         << centralizar_texto("MARCA", w_marca)
         << centralizar_texto("SABOR", w_sabor)
         << centralizar_texto("VALIDADE", w_validade)
         << centralizar_texto("PRECO", w_preco)
         << centralizar_texto("QTD", w_qtd)
         << centralizar_texto("CÓDIGO DO PRODUTO", w_codigo + ajuste)
         << endl;

    cout << std::string(largura_total, '-') << endl;

    // Linhas de produtos
    for (auto &p : m_estoque.get_todos_os_produtos()) {
        std::ostringstream preco_formatado;
        preco_formatado << std::fixed << std::setprecision(2) << p.get_preco();

        cout << centralizar_texto(std::to_string(p.get_id()), w_id)
             << centralizar_texto(p.get_nome(), w_nome)
             << centralizar_texto(p.get_marca(), w_marca)
             << centralizar_texto(p.get_sabor(), w_sabor)
             << centralizar_texto(p.get_data_de_validade(), w_validade)
             << centralizar_texto(preco_formatado.str(), w_preco)
             << centralizar_texto(std::to_string(p.get_quantidade()), w_qtd)
             << centralizar_texto(p.get_codigo_do_produto(), w_codigo + ajuste)
             << endl;
    }

    cout << std::string(largura_total, '=') << endl;
}

// Atualiza algum produto do estoque
void UIestoque::ui_atualizar_produto() {

    // verifica se a lista tá vazia
    if (m_estoque.get_todos_os_produtos().empty()) {
        limpar_terminal();
        std::cout << "Nao temos produtos em estoque" << std::endl;
        return;
    }

    ui_listar_produtos();

    int id = ler_valor<int>("Digite o ID do produto que voce quer atualizar: ");

    if (id >= 1 && id <= static_cast<int>(m_estoque.get_todos_os_produtos().size())) {
        std::string nome = m_estoque.get_todos_os_produtos()[id - 1].get_nome();
        std::string marca = ler_linha("Nova Marca: ");
        std::string sabor = ler_linha("Novo Sabor: ");

        std::string data_de_validade = "";
        do {
            data_de_validade = ler_linha("Data de validade (EX: 02/10/2025): ");
            if (validar_data(data_de_validade)) {
                break;
            }
        } while (true);

        auto preco = ler_valor<double>("Novo Preco: R$");
        auto quantidade = ler_valor<int>("Nova Quantidade: ");
        std::string codigo_do_produto = m_estoque.get_todos_os_produtos()[id - 1].get_codigo_do_produto();

        Produto produto(id, nome, marca, sabor, data_de_validade, preco, quantidade, codigo_do_produto);

        bool existe = m_estoque.atualizar_produto(produto);
        if (existe) {
            std::cout << "Produto ja existe e por isso atualizaremos a quantidade do produto existente" << std::endl;
        } else {
            std::cout << "Produto atualizado com sucesso" << std::endl;
        }
    } else {
        std::cout << "Id do produto nao encontrado" << std::endl;
    }
}

// remove o produto do estoque
void UIestoque::ui_remover_produto() {

    // verifica se a lista tá vazia
    if (m_estoque.get_todos_os_produtos().empty()) {
        limpar_terminal();
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

// menu de produtos disponveis para estoque
void UIestoque::menu_dos_produtos(const std::vector<std::string> &produtos) {
    std::cout << "+--------------------+\n";
    std::cout << "|      PRODUTOS      |\n";
    std::cout << "+--------------------+\n";
    for (size_t i = 0; i < produtos.size(); i++) {
        std::cout << "| [" << i + 1 << "] " << std::setw(14) << std::left << produtos[i] << " |\n";
    }
    std::cout << "| [" << (int) produtos.size() + 1 << "] " << std::setw(14) << std::left << "sair" << " |\n";
    std::cout << "+--------------------+\n";
}