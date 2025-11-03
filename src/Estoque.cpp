#include "Estoque.h"
#include <string>
#include <fstream>  /* Para o .csv */
#include <sstream>
#include <memory>
#include <random>
#include "produtos/Sorvete.h"
#include "produtos/Picole.h"
#include "produtos/Acai.h"
#include "produtos/Milkshake.h"
#include "produtos/Iogurte.h"
#include "produtos/Smoothie.h"
#include "produtos/Paleta.h"


Estoque::Estoque() {
    carregarDoCSV("estoque.csv");
}

void Estoque::carregarDoCSV(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        return;
    }

    std::string linha;
    std::getline(arquivo, linha); 

    while (std::getline(arquivo, linha)) {
        if (linha.empty()) {
            continue;
        }

        std::stringstream ss(linha);
        std::string pedaco;

        std::string pedaco_id, tipo, marca, data_val, pedaco_preco, pedaco_qtd_estoque, codigo, pedaco_qtd_aberta, data_abertura, dados_especificos;
        double preco = 0.0;
        int id = 0;
        int quantidade_estoque = 0;
        int quantidade_aberta = 0;

        std::getline(ss, pedaco_id, ';');
        std::getline(ss, tipo, ';');
        std::getline(ss, marca, ';');
        std::getline(ss, data_val, ';');
        std::getline(ss, pedaco_preco, ';');
        std::getline(ss, pedaco_qtd_estoque, ';');
        std::getline(ss, codigo, ';');
        std::getline(ss, pedaco_qtd_aberta, ';');
        std::getline(ss, data_abertura, ';');
        std::getline(ss, dados_especificos, ';');

        try {
            id = std::stoi(pedaco_id);
            preco = std::stod(pedaco_preco);
            quantidade_estoque = std::stoi(pedaco_qtd_estoque);
            quantidade_aberta = std::stoi(pedaco_qtd_aberta);
        } catch (const std::exception& e) {
            continue;
        }

        std::unique_ptr<Produto> novoProduto = nullptr;

        if (tipo == "Sorvete") {
            novoProduto = std::make_unique<Sorvete>(id, marca, dados_especificos, data_val, preco, quantidade_estoque, codigo, quantidade_aberta, data_abertura);
        } else if (tipo == "Picole") {
            std::stringstream ss_dados(dados_especificos);
            std::string sabor, recheio;
            std::getline(ss_dados, sabor, '|');
            std::getline(ss_dados, recheio, '|');
            novoProduto = std::make_unique<Picole>(id, marca, sabor, recheio, data_val, preco, quantidade_estoque, codigo, quantidade_aberta, data_abertura);
        } else if (tipo == "Acai") {
            novoProduto = std::make_unique<Acai>(id, marca, dados_especificos, data_val, preco, quantidade_estoque, codigo, quantidade_aberta, data_abertura);
        } else if (tipo == "Milkshake") {
            novoProduto = std::make_unique<Milkshake>(id, marca, dados_especificos, data_val, preco, quantidade_estoque, codigo, quantidade_aberta, data_abertura);
        } else if (tipo == "Iogurte") {
            novoProduto = std::make_unique<Iogurte>(id, marca, dados_especificos, data_val, preco, quantidade_estoque, codigo, quantidade_aberta, data_abertura);
        } else if (tipo == "Smoothie") {
            novoProduto = std::make_unique<Smoothie>(id, marca, dados_especificos, data_val, preco, quantidade_estoque, codigo, quantidade_aberta, data_abertura);
        } else if (tipo == "Paleta") {
            novoProduto = std::make_unique<Paleta>(id, marca, dados_especificos, data_val, preco, quantidade_estoque, codigo, quantidade_aberta, data_abertura);
        }

        if (novoProduto != nullptr) {
            produtos_em_estoque.push_back(std::move(novoProduto));
        }
    }

    arquivo.close();
}


bool Estoque::adicionar_produto(std::unique_ptr<Produto> novoProduto) {
    novoProduto->set_id(static_cast<int>(produtos_em_estoque.size()) + 1);
    
    if (novoProduto->get_codigo_do_produto().empty()) {
        novoProduto->set_codigo_do_produto(gerar_codigo_aleatorio());
    }

    bool existe = verificar_produto_existe(novoProduto.get());
    if (existe) {
        return true;
    }
    
    produtos_em_estoque.push_back(std::move(novoProduto));
    return false;
}

bool Estoque::verificar_produto_existe(Produto *produto) {
    for (auto &p : produtos_em_estoque) {
        if (p->getTipo() != produto->getTipo()) {
            continue;
        }

        bool mergeable = false;
        std::string tipo = produto->getTipo();

        if (tipo == "Sorvete" || tipo == "Milkshake" || tipo == "Iogurte" || tipo == "Smoothie" || tipo == "Paleta") {
            Sorvete* p_existente = static_cast<Sorvete*>(p.get());
            Sorvete* p_novo = static_cast<Sorvete*>(produto);

            if (p_existente->get_marca() == p_novo->get_marca() &&
                p_existente->getSabor() == p_novo->getSabor() &&
                p_existente->get_data_de_validade() == p_novo->get_data_de_validade() &&
                p_existente->get_preco() == p_novo->get_preco()) {
                mergeable = true;
            }
        } else if (tipo == "Picole") {
            Picole* p_existente = static_cast<Picole*>(p.get());
            Picole* p_novo = static_cast<Picole*>(produto);
            
            if (p_existente->get_marca() == p_novo->get_marca() &&
                p_existente->getSabor() == p_novo->getSabor() &&
                p_existente->getRecheio() == p_novo->getRecheio() &&
                p_existente->get_data_de_validade() == p_novo->get_data_de_validade() &&
                p_existente->get_preco() == p_novo->get_preco()) {
                mergeable = true;
            }
        } else if (tipo == "Acai") {
            Acai* p_existente = static_cast<Acai*>(p.get());
            Acai* p_novo = static_cast<Acai*>(produto);

            if (p_existente->get_marca() == p_novo->get_marca() &&
                p_existente->getTamanho() == p_novo->getTamanho() &&
                p_existente->get_data_de_validade() == p_novo->get_data_de_validade() &&
                p_existente->get_preco() == p_novo->get_preco()) {
                mergeable = true;
            }
        }
        
        if (mergeable) {
            // logica da troca
            p->set_quantidade_estoque(p->get_quantidade_estoque() + produto->get_quantidade_estoque());
            return true;
        }
    }
    return false;
}

bool Estoque::atualizar_produto(Produto *produto) {
    return false;
}

bool Estoque::remover_produto(int id) {
    if (id < 0 || id >= produtos_em_estoque.size()) {
        return false;
    }

    produtos_em_estoque.erase(produtos_em_estoque.begin() + id);

    // Reatribui IDs
    for (size_t i = id; i < produtos_em_estoque.size(); i++) {
    // Apaga o produto
        produtos_em_estoque[i]->set_id(static_cast<int>(i + 1));
    }
    return true;
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
        if (produto->get_codigo_do_produto() == codigo) {
            return true;
        }
    }
    return false;
}

// Retorna todos os produtos (para a Interface ler e imprimir)
const std::vector<std::unique_ptr<Produto>>& Estoque::get_todos_os_produtos() const {
    return produtos_em_estoque;
}

/* Para salvar em .csv */
void Estoque::salvarParaCSV(const std::string& nomeArquivo) {
    std::ofstream arquivo_csv(nomeArquivo);

    arquivo_csv << "ID;Tipo;Marca;DataDeValidade;Preco;QtdEstoque;CodigoDoProduto;QtdAberta;DataAbertura;DadosEspecificos" << std::endl;
    
    for (auto& p : produtos_em_estoque) {
        arquivo_csv << p->get_id() << ";"
                    << p->getTipo() << ";"
                    << p->get_marca() << ";"
                    << p->get_data_de_validade() << ";"
                    << p->get_preco() << ";"
                    << p->get_quantidade_estoque() << ";"
                    << p->get_codigo_do_produto() << ";"
                    << p->get_quantidade_aberta() << ";"
                    << p->get_data_abertura() << ";"
                    << p->getDadosParaCSV() << std::endl;
    }
    arquivo_csv.close();
}

Produto* Estoque::get_produto_por_id(int id) {
    for (auto &p : produtos_em_estoque) {
        if (p->get_id() == id) {
            return p.get();
        }
    }
    return nullptr;
}

bool Estoque::abrir_produto(int id, int quantidade_para_abrir, std::string data_hoje) {
    Produto* produto = get_produto_por_id(id);
    
    if (produto == nullptr) {
        return false;
    }
    
    if (produto->get_quantidade_estoque() < quantidade_para_abrir) {
        return false;
    }
    
    produto->set_quantidade_estoque(produto->get_quantidade_estoque() - quantidade_para_abrir);
    produto->set_quantidade_aberta(produto->get_quantidade_aberta() + quantidade_para_abrir);
    
    if (produto->get_data_abertura().empty()) {
        produto->set_data_abertura(data_hoje);
    }
    
    return true;
}
