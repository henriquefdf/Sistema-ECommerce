#ifndef SERVICOPRODUTO_HPP
#define SERVICOPRODUTO_HPP

#include <sqlite3.h>
#include <iostream>
#include <map>
#include <vector>

#include "../objects/Produto.hpp"
class ServicoProduto {
    public:
        static int criar(string nomeProduto, double precoProduto, string descricaoProduto); //retorna o id do produto
        static int deletar(int id);
        static int atualizar(int id, string nomeProduto, double precoProduto, string descricaoProduto);
        static string buscarProduto(int id);
};

#endif