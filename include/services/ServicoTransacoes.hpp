#ifndef SERVICOTRANSACOES_HPP
#define SERVICOTRANSACOES_HPP

#include <sqlite3.h>
#include <iostream>
#include <map>
#include <vector>
#include <ctime>

#include "../objects/Transacao.hpp"
#include "../objects/Produto.hpp"
#include "../services/ServicoVendedor.hpp"
#include "../services/ServicoComprador.hpp"
#include "../services/ServicoEstoque.hpp"

class ServicoTransacoes {
    public:
        static int criar(int idComprador, int idVendedor, int idProduto, double qtdProduto, string data, double valorTotal, string tipoPagamento);
        static vector<Transacao*> selecionarTransacoes(int idVendedorm, char tipoUsuario);
        static void efetuarCompra(int idComprador, std::multimap<Produto*, double> produtos, double valorTotal, string tipoPagamento, double saldoComprador);
        static double calcularValorTotalCompra(std::multimap<Produto*, double> produtos); 
        static int deletar(int idTransacao);
};

#endif