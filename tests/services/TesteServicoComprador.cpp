#include "../../lib/doctest.h"

#include "../../include/services/ServicoComprador.hpp"
#include "../../include/services/ServicoUsuario.hpp"

TEST_CASE("Criar Comprador") {
    CHECK(ServicoComprador::criar(7530) == 7530);
    ServicoComprador::deletar(7530);
}

TEST_CASE("Deletar Comprador") {
    ServicoComprador::criar(7531);
    CHECK(ServicoComprador::deletar(7531) == 1);
}

TEST_CASE("Criar Comprador já existente") {
    ServicoComprador::criar(7532);
    CHECK(ServicoComprador::criar(7532) == 0);
    ServicoComprador::deletar(7532);
}

TEST_CASE("Atualizar saldo") {
    int idComprador = ServicoUsuario::criar("teste", "teste", "teste", 'c', 100);
    CHECK(ServicoComprador::atualizarSaldo(idComprador, 200) == 1);
    ServicoUsuario::deletar(idComprador);
    ServicoComprador::deletar(idComprador);
}