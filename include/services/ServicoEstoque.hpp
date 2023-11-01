#ifndef SERVICOESTOQUE_HPP
#define SERVICOESTOQUE_HPP

#include <sqlite3.h>
#include <iostream>
#include <map>
#include <vector>
#include <iomanip>

#include "../objects/Produto.hpp"

using std::to_string;

class ServicoEstoque {
    public:
        static int inserirProduto(int idProduto, int idVendedor, double qtdProduto, string medidaQtd);
        static int atualizar(int idProduto, int idVendedor, double qtdProduto, string medidaQtd); 
        static vector<Produto*> selecionarProdutos(int idVendedor);
        static vector<Produto*> selecionarProdutosEspecificos(string produto);
        static vector<Produto*> listarTodosProdutos();
        static int deletarProdutoEstoque(int idProduto);
};

#endif