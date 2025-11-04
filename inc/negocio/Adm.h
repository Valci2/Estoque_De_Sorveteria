#pragma once
#include "User.h"
#include <vector>

class Adm : public User {
private:
    std::string email;
    std::string senha;

public:

Adm() = default;
Adm(int id, std::string& nome, std::string& senha, std::string& email);
~Adm() = default;

void criar(std::string &nome, std::string &email, std::string &senha);
bool logar(std::vector<Adm> adms);

// getter
int get_id() override;
std::string get_nome() override;
std::string get_senha();
std::string get_email();
};