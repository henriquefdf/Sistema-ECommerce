#include "../../lib/doctest.h"

#include "../../include/objects/Produto.hpp"

TEST_CASE("Criar produto e checar ID") {
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    CHECK(produto->getID() == 1);
}

TEST_CASE("Criar produto e checar nome") {
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    CHECK(produto->getNome() == "teste");
}

TEST_CASE("Criar produto e checar preco") {
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    CHECK(produto->getPreco() == 50.5);
}

TEST_CASE("Criar produto e checar unidade") {
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    CHECK(produto->getUnidadeMedida() == "un");
}

TEST_CASE("Criar produto e checar idVendedor") {
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    CHECK(produto->getIdVendedor() == 3);
}

TEST_CASE("Criar produto e checar quantidade") {
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    CHECK(produto->getQuantidade() == 100);
}

TEST_CASE("Criar produto e checar descricao") {
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    CHECK(produto->getDescricao() == "teste");
}

TEST_CASE("Imprimir produto") {
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    CHECK_NOTHROW(produto->imprimir());
}

TEST_CASE("Criar produto e modificar nome") {
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    produto->setNome("teste2");
    CHECK(produto->getNome() == "teste2");
}

TEST_CASE("Criar produto e modificar preco") {
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    produto->setPreco(100.5);
    CHECK(produto->getPreco() == 100.5);
}

TEST_CASE("Criar produto e modificar unidade") {
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    produto->setUnidadeMedida("kg");
    CHECK(produto->getUnidadeMedida() == "kg");
}

TEST_CASE("Criar produto e modificar quantidade") {
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    produto->setQuantidade(200);
    CHECK(produto->getQuantidade() == 200);
}

TEST_CASE("Criar produto e modificar descricao") {
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    produto->setDescricao("teste2");
    CHECK(produto->getDescricao() == "teste2");
}

TEST_CASE("Criar produto e destruir") {
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    CHECK_NOTHROW(delete produto);
}