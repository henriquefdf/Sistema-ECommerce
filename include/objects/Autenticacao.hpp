#ifndef AUTENTICACAO_HPP
#define AUTENTICACAO_HPP

#include <iostream>
#include "Usuario.hpp"
#include "Produto.hpp"
#include "../include/services/ServicoUsuario.hpp" 

class Autenticacao{
    private:
        static bool _autenticado; //token que indica o estado do usuário

    public:
        static Usuario* usuarioLogado; //ponteiro que aponta para o usuário logado no sistema
        static multimap<Produto*, double> carrinhoCompradorLogado; //carrinho de compras do comprador logado
        
        Autenticacao()=default;
        ~Autenticacao();
        static void logout();
        static bool autenticar(string loginUsuario, string senha); //caso o usuário exista, verifica se a senha está correta
        static bool getAutenticado();
        static void guardarCarrinho(multimap<Produto*, double> carrinho);
};

#endif