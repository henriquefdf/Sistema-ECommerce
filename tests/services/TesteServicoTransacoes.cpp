#include "../../lib/doctest.h"
#include "../../include/services/ServicoTransacoes.hpp"
#include "../../include/services/ServicoUsuario.hpp"
#include "../../include/services/ServicoComprador.hpp"
#include "../../include/services/ServicoVendedor.hpp"
#include "../../include/services/ServicoProduto.hpp"

TEST_CASE("Criar transação") {
    int idTransacao = ServicoTransacoes::criar(1, 1, 1, 10, "teste", 150, "teste");
    CHECK(idTransacao);
    ServicoTransacoes::deletar(idTransacao);
}

TEST_CASE("Selecionar transações de um usuário") {
    int idVendedor = ServicoUsuario::criar("vendedortest", "vendedortest", "teste", 'v', 0);
    int idComprador = ServicoUsuario::criar("compradortest", "compradortest", "teste", 'c', 0);
    int idProduto = ServicoProduto::criar("testeProdEspec", 10, "produto teste");
    int idTransacao = ServicoTransacoes::criar(idComprador, idVendedor, idProduto, 10, "teste", 150, "teste");

    vector<Transacao*> resultado = ServicoTransacoes::selecionarTransacoes(idComprador, 'c');
    CHECK(resultado.size() != 0);

    ServicoVendedor::deletar(idVendedor);
    ServicoComprador::deletar(idComprador);
    ServicoProduto::deletar(idProduto);

    ServicoUsuario::deletar(idVendedor);
    ServicoUsuario::deletar(idComprador);
    ServicoTransacoes::deletar(idTransacao);
}