#ifndef COMPRADOR_HPP
#define COMPRADOR_HPP

#include "Usuario.hpp"
#include "Produto.hpp"
#include "Transacao.hpp"
#include "../include/services/ServicoEstoque.hpp"
#include "../include/services/ServicoTransacoes.hpp"
#include "../include/services/ServicoComprador.hpp"
#include <cmath>
#include <limits>

class Comprador : public Usuario {

    private:
    multimap<Produto*, double> carrinhoCompras;

    public:
        Comprador();
        Comprador(Usuario* usuario);
        ~Comprador();

        void mostrarSaldo();
        void adicionarValorSaldo(double valor);
        vector<Produto*> procurarProdutos(string produto);
        vector<Produto*> listarProdutosDisponiveis();
        void selecionarProdutos(vector<Produto*> produtosListados);
        double verificarQuantidadeProdutoCarrinho(int idProduto);
        int finalizarCompra();
        void historicoComprador();
        void adicionarAoCarrinho(Produto* produtoComprado, double quantidade);
        void esvaziarCarrinho();
        void removerItemCarrinho(int ID_remocao);
        void visualizarCarrinho();
        string escolherFormaPagamento();
        multimap<Produto*, double> getCarrinhoCompras();
        void recuperarCarrinho(multimap<Produto*, double> carrinhoCompras);
};

#endif