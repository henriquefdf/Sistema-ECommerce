#ifndef PRODUTO_HPP
#define PRODUTO_HPP

#include <iostream>
#include <vector>
#include <map>

using std::multimap;
using std::vector;
using std::cout;
using std::cin;
using std::string;
class Produto {
    private:
        int _ID;
        int _idVendedor;
        string _nome;
        double _quantidade;
        double _preco;
        string _unidadeMedida;
        string _descricao;

    public:
        Produto(int ID, int idVendedor, string nome, double quantidade, double preco, string unidadaMedida, string descricao);
        ~Produto();
        void setNome(string nome);
        void setQuantidade(double quantidade);
        void setPreco(double preco);
        void setUnidadeMedida(string unidadeMedida);
        void setDescricao(string descricao);
        void imprimir();
        
        int getID();
        int getIdVendedor();
        string getNome();
        double getQuantidade();
        double getPreco();
        string getUnidadeMedida();
        string getDescricao();
};

#endif