#ifndef TRANSACOES_HPP
#define TRANSACOES_HPP

#include <iostream>

using std::cout;
using std::cin;
using std::string;

class Transacao {
    private:
        int _ID;
        int _idComprador;
        int _idVendedor;
        int _idProduto;
        double _qtdProduto;
        string _data;
        double _valorTotal;
        string _tipoPagamento;
        string _nomeComprador;
        string _nomeVendedor;
        string _nomeProduto;

    public:
        Transacao(int ID, int idComprador, int idVendedor, int idProduto, double qtdProduto, string data, double valorTotal, string tipoPagamento, string nomeComprador, string nomeVendedor,  string nomeProduto);
        Transacao();
        ~Transacao();
        void imprimir();
        int getID();
        int getIdComprador();
        int getIdVendedor();
        int getIdProduto();
        double getQtdProduto();
        string getData();
        double getValorTotal();
        string getTipoPagamento();
        string getNomeComprador();
        string getNomeVendedor();
        string getNomeProduto();
};

#endif