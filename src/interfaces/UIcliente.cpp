#include "interface/UIcliente.h"
#include "negocio/Cliente.h" 
#include "negocio/Produto.h" 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>

void UIcliente::limpar_terminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/* Recebe o estoque e o armazena na referência 'meuEstoque' */
UIcliente::UIcliente(Estoque& estoque) : meuEstoque(estoque) {
}

/* Menu principal */
void UIcliente::mostrarMenuPrincipal() {
    int escolha = 0;
    while (escolha != 3) {
        std::cout << "+======================+" << std::endl;
        std::cout << "|    Menu Principal    |" << std::endl;
        std::cout << "+======================+" << std::endl;
        std::cout << " [1] Listar Estoque     " << std::endl;
        std::cout << " [2] Solicitar Reserva  " << std::endl;
        std::cout << " [3] Sair (Deslogar)    " << std::endl;
        std::cout << "Escolha: ";
        std::cin >> escolha;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
            escolha = 0; 
        }

        switch (escolha) {
            case 1:
                executarListarEstoque(); break;
            case 2:
                executarSolicitarReserva(); break;
            case 3:
                std::cout << "Deslogando..." << std::endl;
                this->usuarioLogado = "";
                break;
            default:
                std::cout << "Opcao invalida." << std::endl; break;
        }
    }
}

/* Função para lisatr o estoque */
void UIcliente::executarListarEstoque() {
    std::cout << "+========================================================+" << std::endl;
    std::cout << "|                  Produtos Disponiveis                  |" << std::endl;
    std::cout << "+========================================================+" << std::endl;
    std::vector<Produto> produtos = meuEstoque.get_todos_os_produtos();

    if (produtos.empty()) {
        std::cout << "Nenhum produto em estoque no momento." << std::endl;
        return;
    }
    
    std::cout << std::left 
              << std::setw(7) << "ID"
              << std::setw(15) << "Nome"
              << std::setw(15) << "Sabor"
              << std::setw(15) << "Preco"
              << std::setw(10) << "Qtd."
              << std::endl;
    std::cout << "==========================================================" << std::endl;
    
    /* Mostra somente 2 casas decimais no preço */
    std::cout << std::fixed << std::setprecision(2);
    /* Imprime os produtos */
    for (Produto& p : produtos) {
        std::cout << std::left
                  << std::setw(7) << p.get_id()
                  << std::setw(16) << p.get_nome()
                  << std::setw(13) << p.get_sabor()
                  << "R$" << std::setw(14) << p.get_preco()
                  << std::setw(10) << p.get_quantidade()
                  << std::endl;
    }
    std::cout << "==========================================================" << std::endl;
}

/* Função para solicitar a reserva. OBS: Ela não altera nada no estoque */
void UIcliente::executarSolicitarReserva() {
    /* Mostra a lista para o cliente saber os IDs dos produtos */
    executarListarEstoque();

    int idProduto;
    int qtdDesejada;

    std::cout << "+===========================+" << std::endl;
    std::cout << "|     Solicitar Reserva     |" << std::endl;
    std::cout << "+===========================+" << std::endl;
    std::cout << "Digite o [ID] do produto que deseja reservar (ou 0 para cancelar): ";
    std::cin >> idProduto;

    if (idProduto == 0) {
        std::cout << "Reserva cancelada." << std::endl;
        return;
    }

    /* Busca o produto mas sem modificar o estoque */
    std::vector<Produto> produtos = meuEstoque.get_todos_os_produtos();
    Produto* produtoEncontrado = nullptr;

    for (int i = 0; i < produtos.size(); ++i) {
        if (produtos[i].get_id() == idProduto) {
            produtoEncontrado = &produtos[i]; break;
        }
    }

    /* Caso o produto não exista */
    if (produtoEncontrado == nullptr) {
        std::cout << "ERRO: Produto com ID " << idProduto << " nao encontrado." << std::endl;
        return;
    }

    int maxEstoque = produtoEncontrado->get_quantidade();
    std::cout << "Produto selecionado: " << produtoEncontrado->get_nome() << " (" << produtoEncontrado->get_sabor() << ")" << std::endl;
    std::cout << "Estoque disponivel: " << maxEstoque << std::endl;
    std::cout << "Digite a quantidade que deseja reservar (Max: " << maxEstoque << "): ";
    std::cin >> qtdDesejada;

    /* Só pode requisitar até o máximo do estoque */
    if (qtdDesejada <= 0) {
        std::cout << "Quantidade invalida." << std::endl;
        return;
    }

    if (qtdDesejada > maxEstoque) {
        std::cout << "ERRO: Quantidade solicitada (" << qtdDesejada 
                  << ") excede o limite do estoque (" << maxEstoque << ")." << std::endl;
        return;
    }

    /* Salva o nosso arquivo .csv */
    std::ofstream arquivoReserva("reservas.csv", std::ios::app);
    arquivoReserva << this->usuarioLogado << ";"
                   << produtoEncontrado->get_id() << ";"
                   << produtoEncontrado->get_nome() << ";"
                   << qtdDesejada << "\n";
    arquivoReserva.close();

    std::cout << "=========================================================" << std::endl;
    std::cout << "Reserva solicitada com sucesso!" << std::endl;
    std::cout << "Voce solicitou a reserva de " << qtdDesejada << " " << produtoEncontrado->get_nome() <<"(s)"<<std::endl;
    std::cout << "(Um administrador ira processar seu pedido e entrara em contato por e-mail)" << std::endl;
    std::cout << "=========================================================" << std::endl;
}

/* Função de login */
std::string UIcliente::executarLogin() {
    std::string loginInput, senhaInput;
    std::cout << "+=======================+" << std::endl;
    std::cout << "|         Login         |" << std::endl;
    std::cout << "+=======================+" << std::endl;
    std::cout << "Digite seu Nome (login): ";
    std::cin.ignore(); 
    std::getline(std::cin, loginInput);
    std::cout << "Digite sua Senha: ";
    std::getline(std::cin, senhaInput);

    std::ifstream arquivo("contas.csv");
    std::string linha;
    std::string usuarioLogado = "";

    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            std::stringstream ss(linha);
            std::string loginSalvo, senhaSalva;
            std::getline(ss, loginSalvo, ';');
            std::getline(ss, senhaSalva, ';');
            if (loginSalvo == loginInput && senhaSalva == senhaInput) {
                usuarioLogado = loginInput; break; 
            }
        }
        arquivo.close();
    }
    
    if (!usuarioLogado.empty()) {
        std::cout << "Login bem-sucedido!" << std::endl;
    } else {
        std::cout << "Login ou senha invalidos." << std::endl;
    }
    return usuarioLogado;
}

/* Função para criar contas. OBS: no caso do adm a conta já é criada previamente */
void UIcliente::executarCriarConta() {
    Cliente novoCliente;
    novoCliente.criar(); 
}

/* Menu do cliente logado */
void UIcliente::mostrarMenuLogin() {
    int escolha = 0;
    while (escolha != 3) {
        limpar_terminal();
        std::cout << "+=======================+" << std::endl;
        std::cout << "|   SEJA BEM-VINDO(A)   |" << std::endl;
        std::cout << "+=======================+" << std::endl;
        std::cout << "[1] Criar Conta" << std::endl;
        std::cout << "[2] Logar" << std::endl;
        std::cout << "[3] Sair do Programa" << std::endl;
        std::cout << "Escolha uma opcao: ";
        std::cin >> escolha;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();
            escolha = 0;
        }

        switch (escolha) {
            case 1:
                executarCriarConta(); break;
            case 2:{
                    std::string login = executarLogin();
                    if (!login.empty()) {
                        this->usuarioLogado = login;
                        mostrarMenuPrincipal(); /* Chama o menu principal */
                    }
                } break;
            case 3:
                std::cout << "Obrigado por escolher nossa loja!!" << std::endl;break;
            default:
                std::cout << "Opcao invalida. Tente novamente." << std::endl; break;
        }
    }
}
