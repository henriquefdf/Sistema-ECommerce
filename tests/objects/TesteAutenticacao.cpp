#include "../../lib/doctest.h"

#include "../../include/objects/Autenticacao.hpp"

#include "../../include/services/ServicoUsuario.hpp"
#include "../../include/services/ServicoComprador.hpp"


TEST_CASE("Autenticacao de usuario") {
    int idUsuario = ServicoUsuario::criar("teste", "testeCriarUsuario", "teste", 'c', 100);
    CHECK(Autenticacao::autenticar("testeCriarUsuario", "teste"));
    ServicoComprador::deletar(idUsuario);
    ServicoUsuario::deletar(idUsuario);
}

TEST_CASE("Autenticacao de usuario com login invalido") {
    CHECK_THROWS_AS(Autenticacao::autenticar("batata", "Torresmin"), std::runtime_error);
}

TEST_CASE("Senha vazia") {
    int idUsuario = ServicoUsuario::criar("teste", "testeCriarUsuario", "teste", 'c', 100);
    CHECK_THROWS_AS(Autenticacao::autenticar("testeCriarUsuario", ""), std::invalid_argument);
    ServicoComprador::deletar(idUsuario);
    ServicoUsuario::deletar(idUsuario);
}

TEST_CASE("Senha incorreta") {
    int idUsuario = ServicoUsuario::criar("teste", "testeCriarUsuario", "teste", 'c', 100);
    CHECK_THROWS_AS(Autenticacao::autenticar("testeCriarUsuario", "IagoGin"), std::runtime_error);
    ServicoComprador::deletar(idUsuario);
    ServicoUsuario::deletar(idUsuario);
}

TEST_CASE("Usuario nao existe") {
    CHECK_THROWS_AS(Autenticacao::autenticar("CeceloApelao", "ChicoAnao"), std::runtime_error);
}

TEST_CASE("Logout") {
    int idUsuario = ServicoUsuario::criar("teste", "testeCriarUsuario", "teste", 'c', 100);
    Autenticacao::autenticar("testeCriarUsuario", "teste");
    Autenticacao::logout();
    CHECK(!Autenticacao::getAutenticado());
    ServicoComprador::deletar(idUsuario);
    ServicoUsuario::deletar(idUsuario);
}

TEST_CASE("Guardar carrinho comprador logado") {
    Produto* produto = new Produto(1, 1, "prod teste", 5, 10, "un", "teste");
    multimap<Produto*, double> carrinho;
    carrinho.insert({produto, 1});
    CHECK_NOTHROW(Autenticacao::guardarCarrinho(carrinho));
}