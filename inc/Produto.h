#pragma once
#include <string>

class Produto {
private:
    int id;
    std::string nome;
    std::string marca;
    std::string sabor;
    std::string data_de_validade;
    double preco;

public:
    // constutor de produto
    Produto(int id, std::string &nome, std::string &marca, std::string &sabor, std::string &data_de_validade,
        double preco);

    // getter
    int get_id();
    std::string &get_nome();
    std::string &get_marca();
    std::string &get_sabor();
    std::string &get_data_de_validade();
    double get_preco();

    // setter
    void set_id(int id);
    void set_nome(std::string &nome);
    void set_marca(std::string &marca);
    void set_sabor(std::string &sabor);
    void set_data_de_validade(std::string &data_de_validade);
    void set_preco(double preco);
};
