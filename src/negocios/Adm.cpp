#include "negocio/Adm.h"

Adm::Adm(int id, std::string& nome, std::string& senha, std::string& email) : User(id, nome), senha(senha), email(email) {}

void criar(std::string& nome, std::string& senha, std::string& email) {
    int novo_id = static_cast<int>(Adm::adms_existentes.size());
    Adm novo_adm(static_cast<int> (novo_id, nome, senha, email);
    Adm::adms_existentes.push_back(novo_adm);
}

bool logar() {
    for (auto& adm : Adm::adms_existentes) {
        if (adm.get_nome() == nome &&
            adm.get_senha() == senha &&
            adm.get_email() == email) {
            return true;
        }
    }
    return false;
}

int Adm::get_id() { return User::get_id(); }
std::string Adm::get_nome() { return User::get_nome(); }
std::string Adm::get_email() { return email; }
std::string Adm::get_senha() { return senha; }