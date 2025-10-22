#include "Produto.h"

// construtor
Produto::Produto(int id, std::string &nome, std::string &marca, std::string &sabor, std::string &data_de_validade,
    double preco) {
    this->id = id;
    this->nome = nome;
    this->marca = marca;
    this->sabor = sabor;
    this->data_de_validade = data_de_validade;
    this->preco = preco;
}

// setter
void Produto::set_id(int id) { this->id = id; }
void Produto::set_nome(std::string &nome) { this->nome = nome; }
void Produto::set_marca(std::string &marca) { this->marca = marca; }
void Produto::set_sabor(std::string &sabor) { this->sabor = sabor; }
void Produto::set_data_de_validade(std::string &data_de_validade) { this->data_de_validade = data_de_validade; }
void Produto::set_preco(double preco) { this->preco = preco; }

// getter
int Produto::get_id() { return id; }
std::string &Produto::get_nome() { return nome; }
std::string &Produto::get_marca() { return marca; }
std::string &Produto::get_sabor() { return sabor; }
std::string &Produto::get_data_de_validade() { return data_de_validade; }
double Produto::get_preco() { return preco; }
