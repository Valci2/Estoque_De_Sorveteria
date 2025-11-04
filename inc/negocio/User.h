#pragma once
#include <string>

class User {
private:
    int id;
    std::string nome;

public:
    //
    User() = default;
    User(int id, std::string &nome);
    ~User() = default;

    //
    virtual void criar();
    virtual bool logar();
    virtual int get_id();
    virtual std::string get_nome();

    /* setters */
    virtual void set_id(int id);
    virtual void set_nome(const std::string &nome);
};
