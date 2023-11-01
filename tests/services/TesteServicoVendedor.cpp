#include "../../lib/doctest.h"

#include "../../include/services/ServicoVendedor.hpp"
#include "../../include/services/ServicoUsuario.hpp"

TEST_CASE("Criar Vendedor") {
    CHECK(ServicoVendedor::criar(7530) == 7530);
    ServicoVendedor::deletar(7530);
}

TEST_CASE("Criar Vendedor já existente") {
    ServicoVendedor::criar(7532);
    CHECK(ServicoVendedor::criar(7532) == 0);
    ServicoVendedor::deletar(7532);
}

TEST_CASE("Deletar Vendedor") {
    ServicoVendedor::criar(7531);
    CHECK(ServicoVendedor::deletar(7531) == 1);
}

TEST_CASE("Atualizar saldo") {
    int idVendedor = ServicoUsuario::criar("teste", "teste", "teste", 'v', 100);
    CHECK(ServicoVendedor::atualizarSaldo(idVendedor, 200) == 1);
    ServicoUsuario::deletar(idVendedor);
    ServicoVendedor::deletar(idVendedor);
}

TEST_CASE("Atualizar saldo de vendedor inexistente") {
    CHECK(ServicoVendedor::atualizarSaldo(9909, 200) == 2);
}