#include "../../lib/doctest.h"
#include "../../include/services/ServicoProduto.hpp"

TEST_CASE("Criar um novo produto") {
    int id = ServicoProduto::criar("teste", 1.0, "teste");
    CHECK(id != -1);
    ServicoProduto::deletar(id);
}

TEST_CASE("Deletar um produto") {
    int id = ServicoProduto::criar("teste", 1.0, "teste");
    CHECK(id != -1);
    int produtosDeletados = ServicoProduto::deletar(id);
    CHECK(produtosDeletados == 1);
}

TEST_CASE("Deletar um produto inexistente") {
    int produtosDeletados = ServicoProduto::deletar(9909);
    CHECK(produtosDeletados == 0);
}

TEST_CASE("Atualizar um produto") {
    int id = ServicoProduto::criar("teste", 1.0, "teste");
    int produtosAtualizados = ServicoProduto::atualizar(id, "teste2", 2.0, "teste2");
    CHECK(produtosAtualizados == 1);
    ServicoProduto::deletar(id);
}

TEST_CASE("Atualizar um produto inexistente") {
    int produtosAtualizados = ServicoProduto::atualizar(9909, "teste2", 2.0, "teste2");
    CHECK(produtosAtualizados == 0);
}

TEST_CASE("Buscar um produto") {
    int id = ServicoProduto::criar("teste", 1.0, "teste");
    std::string nomeProdutoBuscado = ServicoProduto::buscarProduto(id);
    CHECK(nomeProdutoBuscado == "teste");
    ServicoProduto::deletar(id);
}

TEST_CASE("Buscar um produto inexistente") {
    std::string nomeProdutoBuscado = ServicoProduto::buscarProduto(9909);
    CHECK(nomeProdutoBuscado == "");
}