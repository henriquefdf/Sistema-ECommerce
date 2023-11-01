#include "../../lib/doctest.h"
#include "../../include/services/ServicoEstoque.hpp"
#include "../../include/services/ServicoProduto.hpp"

TEST_CASE("Inserir produto no estoque") {
    int idProd = ServicoProduto::criar("testeProdEspec", 10, "produto teste");
    int resultado = ServicoEstoque::inserirProduto(idProd, 7500, 2, "un");
    CHECK(resultado == 1);

    ServicoProduto::deletar(idProd);
    ServicoEstoque::deletarProdutoEstoque(idProd);
}

TEST_CASE("Atualizar produto no estoque") {
    int idProd = ServicoProduto::criar("testeProdEspec", 10, "produto teste");
    ServicoEstoque::inserirProduto(idProd, 7500, 1, "un");
    int resultado = ServicoEstoque::atualizar(1, 1, 5, "un");
    CHECK(resultado == 1);

    ServicoProduto::deletar(idProd);
    ServicoEstoque::deletarProdutoEstoque(idProd);
}

TEST_CASE("Selecionar produtos de um vendedor especifico") {
    int idProd = ServicoProduto::criar("testeProdEspec", 10, "produto teste");
    ServicoEstoque::inserirProduto(idProd, 7500, 2, "un");
    vector<Produto*> resultado = ServicoEstoque::selecionarProdutos(7500);
    CHECK(resultado.size() == 1);

    ServicoProduto::deletar(idProd);
    ServicoEstoque::deletarProdutoEstoque(idProd);
}

TEST_CASE("Selecionar produto especifico") {
    int idProd = ServicoProduto::criar("testeProdEspec", 10, "produto teste");
    ServicoEstoque::inserirProduto(idProd, 7500, 2, "un");
    vector<Produto*> resultado = ServicoEstoque::selecionarProdutosEspecificos("testeProdEspec");
    CHECK(resultado.size() != 0);

    ServicoProduto::deletar(idProd);
    ServicoEstoque::deletarProdutoEstoque(idProd);
}

TEST_CASE("Listar produtos") {
    int idProd = ServicoProduto::criar("testeProdEspec", 10, "produto teste");
    ServicoEstoque::inserirProduto(idProd, 7500, 2, "un");

    vector<Produto*> resultado = ServicoEstoque::listarTodosProdutos();
    CHECK(resultado.size() != 0);

    ServicoProduto::deletar(idProd);
    ServicoEstoque::deletarProdutoEstoque(idProd);
}

TEST_CASE("Deletar produto do estoque") {
    int idProd = ServicoProduto::criar("testeProdEspec", 10, "produto teste");
    ServicoEstoque::inserirProduto(idProd, 7500, 2, "un");
    int resultado = ServicoEstoque::deletarProdutoEstoque(idProd);
    CHECK(resultado == 1);

    ServicoProduto::deletar(idProd);
}

TEST_CASE("Deletar produto não existente") {
    int resultado = ServicoEstoque::deletarProdutoEstoque(9909);
    CHECK(resultado == 0);
}