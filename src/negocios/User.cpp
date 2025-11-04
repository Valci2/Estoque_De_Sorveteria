#include "negocio/User.h"

User::User(int id, std::string& nome) : id(id), nome(nome) {}
void User::criar() {}
bool User::logar() {
    return true;
}


int User::get_id() { return id; }
std::string User::get_nome() { return nome; }

void User::set_id(int id) {
    this->id = id;  /* Permite que cliente altere o id */
}
void User::set_nome(const std::string& nome) {
    this->nome = nome; /* Permite que o cliente altere o nome */
}
