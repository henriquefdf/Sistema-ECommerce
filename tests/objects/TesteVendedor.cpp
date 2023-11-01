#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../lib/doctest.h"

#include "../../include/objects/Usuario.hpp"
#include "../../include/objects/Vendedor.hpp"

TEST_CASE("Criar Vendedor") {
    Usuario* usuario = new Usuario("login", "senha", "nome", 'v');
    Vendedor* vendedor = new Vendedor(usuario);
    CHECK(vendedor->getNome() == "nome");
    CHECK(vendedor->getLogin() == "login");
    CHECK(vendedor->getSenha() == "senha");
    CHECK(vendedor->getTipo() == 'v');
    CHECK((int) vendedor->getSaldo() == 0);
}

TEST_CASE("Deletar item inexistente") {
    Usuario* usuario = new Usuario("login", "senha", "nome", 'v');
    Vendedor* vendedor = new Vendedor(usuario);

    CHECK_THROWS_AS(vendedor->deletarItem(9000), std::runtime_error);
}

TEST_CASE("Alterar item inexistente") {
    Usuario* usuario = new Usuario("login", "senha", "nome", 'v');
    Vendedor* vendedor = new Vendedor(usuario);

    CHECK_THROWS_AS(vendedor->alterarInformacoesProduto(9000), std::runtime_error);
}

TEST_CASE("Visualizar estoque vazio") {
    Usuario* usuario = new Usuario("login", "senha", "nome", 'v');
    Vendedor* vendedor = new Vendedor(usuario);

    CHECK_THROWS_AS(vendedor->visualizarEstoque(), std::length_error);
}

TEST_CASE("Histórico de vendas de vendedor sem vendas") {
    Usuario* usuario = new Usuario("login", "senha", "nome", 'v');
    Vendedor* vendedor = new Vendedor(usuario);

    CHECK_THROWS_AS(vendedor->listarHistoricoVendas(), std::runtime_error);
}

TEST_CASE("Verificar saldo positivo") {
    Usuario* usuario = new Usuario("login", "senha", "nome", 'v');
    Vendedor* vendedor = new Vendedor(usuario);
    vendedor->setSaldo(100);

    CHECK_NOTHROW(vendedor->verificarSaldo());
}

TEST_CASE("Verificar saldo zerado") {
    Vendedor* vendedor = new Vendedor();
    vendedor->setSaldo(0);

    CHECK_NOTHROW(vendedor->verificarSaldo());
}