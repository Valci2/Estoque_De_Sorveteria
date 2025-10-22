#pragma once
#include <vector>
#include <string>

struct produto {
    std::string nome;
    int i;
};

const std::vector<produto> produtos = {
    {"Sorvete", 1},
    {"Picole", 2},
    {"Acai", 3},
    {"Smoothie", 4},
    {"Milkshake", 5},
    {"Iogurte", 6}
};

class Produto {
private:
    int id;
    std::string marca;
    std::string sabor;     
    std::string data_de_validade;
    int validade_apos_aberto;
    double preco;
public:
    Produto();


    void getNome();
};