#include "negocio/Adm.h"

Adm::Adm(int id, std::string& nome, std::string& senha, std::string& email) : User(id, nome), senha(senha), email(email) {}

void Adm::criar(std::string& nome, std::string& senha, std::string& email) {
}

bool Adm::logar(std::vector<Adm> adms) {
    return false;
}

int Adm::get_id() { return User::get_id(); }
std::string Adm::get_nome() { return User::get_nome(); }
std::string Adm::get_email() { return email; }
std::string Adm::get_senha() { return senha; }