#include "../../lib/doctest.h"

#include "../../include/objects/Transacao.hpp"


TEST_CASE("Criar transaçao"){
    Transacao* transacao = new Transacao(1, 1, 1, 1, 1, "teste", 1, "teste", "teste", "teste", "teste");
    CHECK(transacao->getID() == 1);
    CHECK(transacao->getIdComprador() == 1);
    CHECK(transacao->getIdVendedor() == 1);
    CHECK(transacao->getIdProduto() == 1);
    CHECK(transacao->getQtdProduto() == 1);
    CHECK(transacao->getData() == "teste");
    CHECK(transacao->getValorTotal() == 1);
    CHECK(transacao->getTipoPagamento() == "teste");
    CHECK(transacao->getNomeComprador() == "teste");
    CHECK(transacao->getNomeVendedor() == "teste");
    CHECK(transacao->getNomeProduto() == "teste");

    delete transacao;
}

