#include "negocio/User.h"

User::User(int id, std::string& nome) : id(id), nome(nome) {}
int User::get_id() { return id; }
std::string User::get_nome() { return nome; }