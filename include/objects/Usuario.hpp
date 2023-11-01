#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <iostream>
#include <sqlite3.h>
#include "../include/services/ServicoUsuario.hpp"
#include "../lib/cores.hpp"

#include <vector>

using std::multimap;
using std::vector;
using std::cout;
using std::cin;
using std::string;
using std::endl;

class Usuario {

    protected:        // atributos de usuário
        string _login;
        string _senha;
        string _nome;
        char _tipo;
        int _ID;
        double _saldo;
    
    public:         // métodos de usuário   
        Usuario(string login, string senha, string nome, char tipo); 
        Usuario();
        Usuario(Usuario* usuario);
        virtual ~Usuario();  
        
        string getLogin();
        string getNome();
        string getSenha();
        char getTipo();
        int getID();
        double getSaldo();

        void setLogin(string login);
        void setSenha(string senha);
        void setNome(string nome);
        void setTipo(char tipo);
        void setID(int id);
        virtual void setSaldo(double saldo);

        static int cadastrarUsuario(string nome, string login, string senha, char tipo);
};

#endif