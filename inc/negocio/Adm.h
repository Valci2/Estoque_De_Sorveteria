#pragma once
#include "User.h"
#include <vector>

class Adm : public User {
private:
    std::string senha;
public:

Adm() = default;
Adm(int id, std::string& nome, std::string& senha);
~Adm() = default;

bool logar(std::string &nome, std::string &senha);

// getter
int get_id() override;
std::string get_nome() override;
std::string get_senha();
};