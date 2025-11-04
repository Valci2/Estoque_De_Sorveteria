#include "negocio/Adm.h"

Adm::Adm(int id, std::string& nome, std::string& senha) : User(id, nome), senha(senha) {}


bool Adm::logar(std::string &nome, std::string& senha) {
    if (nome.compare("Adm") == 0 || senha.compare("Adm") == 0) {
        return true;
    }
    return false;
}

int Adm::get_id() { return User::get_id(); }
std::string Adm::get_nome() { return User::get_nome(); }
std::string Adm::get_senha() { return senha; }