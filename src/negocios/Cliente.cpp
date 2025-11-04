#include "negocio/Cliente.h" 
#include <iostream>
#include <string> 
#include <fstream>

/* chama o construtor de user */
Cliente::Cliente(int id, std::string &nome) : User(id, nome) {
}

/* Getters e setters do cliente */
std::string Cliente::get_dataDeNascimento() { 
    return this->dataDeNascimento; 
}
void Cliente::set_dataDeNascimento(std::string &dataNasc) { 
    this->dataDeNascimento = dataNasc; 
}
void Cliente::set_senha(const std::string& senha) { 
    this->senha = senha; 
}
std::string Cliente::get_senha() { 
    return this->senha; 
}
void Cliente::set_email(const std::string& email) { 
    this->email = email; 
}
std::string Cliente::get_email() { 
    return this->email; 
}


void Cliente::criar() {
    int tempId;
    std::string tempNome, tempSenha, tempEmail, tempNascimento;
    
    std::cout << "--- Cadastro de Novo Cliente ---" << std::endl;
    std::cout << "Digite o ID: ";
    std::cin >> tempId;
    std::cin.ignore();

    std::cout << "Digite o Nome (login): ";
    std::getline(std::cin, tempNome);
    
    std::cout << "Digite a Senha: ";
    std::getline(std::cin, tempSenha);

    std::cout << "Digite o Email: ";
    std::getline(std::cin, tempEmail);

    std::cout << "Digite a Data de Nascimento (DD/MM/AAAA): ";
    std::getline(std::cin, tempNascimento);

    /* Salva os dados */
    set_id(tempId);           
    set_nome(tempNome);        
    set_senha(tempSenha);       
    set_email(tempEmail);       
    set_dataDeNascimento(tempNascimento);

    /* salva o .csv */
    std::ofstream arquivo("contas.csv", std::ios::app);
    arquivo << get_nome() << ";"
            << get_senha() << ";"
            << get_id() << ";"
            << get_email() << ";"
            << get_dataDeNascimento() << "\n";
    arquivo.close();

    std::cout << "Conta criada com sucesso!" << std::endl;
}
