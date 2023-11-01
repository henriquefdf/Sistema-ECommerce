#include "../../lib/doctest.h"
#include "../../include/services/ServicoUsuario.hpp"
#include "../../include/services/ServicoComprador.hpp"

TEST_CASE("Criar Usuario") {
    int idUsuario = ServicoUsuario::criar("teste", "testeCriarUsuario", "teste", 'c', 100);
    CHECK(ServicoUsuario::existeLogin("testeCriarUsuario"));
    ServicoComprador::deletar(idUsuario);
    ServicoUsuario::deletar(idUsuario);
}

TEST_CASE("Recuperar usuário") {
    Usuario* usuario;
    int idUsuario = ServicoUsuario::criar("teste", "testeRecuperarUser", "teste", 'c', 100);

    usuario = ServicoUsuario::getUsuario("testeRecuperarUser");

    CHECK(usuario->getID() == idUsuario);

    ServicoComprador::deletar(idUsuario);
    ServicoUsuario::deletar(idUsuario);
}

TEST_CASE("Recuperar usuário inexistente") {
    CHECK(ServicoUsuario::getUsuario("recuperarInexistente") == nullptr);
}

TEST_CASE("Verificar se existe login") {
    int idUsuario = ServicoUsuario::criar("teste", "verificarLogin", "teste", 'c', 100);

    CHECK(ServicoUsuario::existeLogin("verificarLogin"));

    ServicoComprador::deletar(idUsuario);
    ServicoUsuario::deletar(idUsuario);
}

TEST_CASE("Verificar se existe login inexistente") {
    CHECK(!ServicoUsuario::existeLogin("verificarLoginInexistente"));
}

TEST_CASE("Deletar usuário") {
    int idUsuario = ServicoUsuario::criar("teste", "testeDeletar", "teste", 'c', 100);
    ServicoComprador::deletar(idUsuario);
    CHECK(ServicoUsuario::deletar(idUsuario) == 1);
}