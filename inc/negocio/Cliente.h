#pragma once
#include "negocio/User.h"
#include <string>

class Cliente : public User { 
private:
    std::string dataDeNascimento;
    std::string senha;
    std::string email;

public:
    Cliente() = default;

    Cliente(int id, std::string &nome);

    std::string get_dataDeNascimento();
    void set_dataDeNascimento(std::string &dataNasc);

    void set_senha(const std::string &senha);
    std::string get_senha();

    void set_email(const std::string &email);
    std::string get_email();

    void criar() override; 
};
