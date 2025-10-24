#pragma once

#include "Estoque.h"
#include <vector>
#include <string>

class Interface {
private:

    Estoque m_estoque; // A instância da lógica de estoque

    // vector com os produtos disponiveis
    const std::vector<std::string> produtos_disponiveis = {
        {"Sorvete"}, {"Picole"}, {"Acai"}, {"Smoothie"},
        {"Milkshake"}, {"Iogurte"}, {"Paleta"}
    };

    // --- Funções de UI (Privadas) ---
    void exibir_menu_principal();
    void ui_adicionar_produtos();
    void ui_listar_produtos();
    void ui_atualizar_produto();
    void ui_remover_produto();

    // Menu de seleção de tipo de produto
    void menu_dos_produtos(const std::vector<std::string> &produtos);

    // --- Funções Auxiliares de Input (Privadas) ---
    void limpar_entrada();

    template<typename T>
    T ler_valor(const std::string &mensagem);

    std::string ler_linha(const std::string &mensagem);
public:
    void iniciar();
};
