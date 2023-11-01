#ifndef VENDEDOR_HPP
#define VENDEDOR_HPP

#include <cmath>
#include <limits>
// #include "../lib/cores.hpp"
#include "Usuario.hpp"
#include "Produto.hpp"
#include "../include/services/ServicoTransacoes.hpp"
#include "../include/services/ServicoVendedor.hpp"
#include "../include/services/ServicoEstoque.hpp"
#include "../include/services/ServicoProduto.hpp"

class Vendedor : public Usuario {

    public:
        Vendedor();
        Vendedor(Usuario* usuario);
        ~Vendedor();
        
        //comandos de organização de estoque
        void deletarItem(int idProdutoDeletar);
        void visualizarEstoque();
        void adicionarProdutoEstoque();
        void alterarInformacoesProduto(int idProdutoAlterar);
        void verificarSaldo();
        void listarHistoricoVendas();
};

#endif