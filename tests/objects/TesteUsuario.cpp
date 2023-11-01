#include "../../lib/doctest.h"

#include "../../include/objects/Usuario.hpp"

TEST_CASE("Criar usuário") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    CHECK(usuario->getNome() == "teste");
    CHECK(usuario->getLogin() == "teste");
    CHECK(usuario->getSenha() == "teste");
    CHECK(usuario->getTipo() == 'c');
}

TEST_CASE("Definir login") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    usuario->setLogin("teste2");
    CHECK(usuario->getLogin() == "teste2");
}

TEST_CASE("Definir senha") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    usuario->setSenha("teste2");
    CHECK(usuario->getSenha() == "teste2");
}

TEST_CASE("Definir nome") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    usuario->setNome("teste2");
    CHECK(usuario->getNome() == "teste2");
}

TEST_CASE("Definir tipo") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    usuario->setTipo('v');
    CHECK(usuario->getTipo() == 'v');
}

TEST_CASE("Definir id") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    usuario->setID(1);
    CHECK(usuario->getID() == 1);
}

TEST_CASE("Cadastrar usuário no banco") {
    int id = Usuario::cadastrarUsuario("teste", "teste", "teste", 'c');
    CHECK(id);

    ServicoUsuario::deletar(id);
}