#ifndef SERVICOUSUARIO_HPP
#define SERVICOUSUARIO_HPP

#include <sqlite3.h>
#include <iostream>
#include <map>
#include <vector>
#include "../objects/Usuario.hpp"
using std::string;

class Usuario;

class ServicoUsuario {
    public:
        static int criar(string nome, string nomeUsuario, string senha, char tipoUsuario, double saldo = 0);
        static int deletar(int id);
        static void atualizar(int id, string nome, string nomeUsuario, string senha, char tipoUsuario, double saldo);
        static int inserirUsuario(string login, char tipoUsuario);
        static bool existeLogin(string login);
        static Usuario* getUsuario(string login);
};

#endif