#include "../../lib/doctest.h"

#include "../../include/objects/Usuario.hpp"
#include "../../include/objects/Comprador.hpp"
#include "../../include/objects/Vendedor.hpp"
#include "../../include/objects/Produto.hpp"

TEST_CASE("Criar Comprador") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    CHECK(comprador->getNome() == "teste");
    CHECK(comprador->getLogin() == "teste");
    CHECK(comprador->getSenha() == "teste");
    CHECK(comprador->getTipo() == 'c');
    CHECK((int) comprador->getSaldo() == 0);
}

TEST_CASE("Mostrar saldo do Comprador com saldo bom") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    comprador->setSaldo(100);
    CHECK_NOTHROW(comprador->mostrarSaldo());
}

TEST_CASE("Mostrar saldo do Comprador com saldo baixo") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    comprador->setSaldo(5);
    CHECK_NOTHROW(comprador->mostrarSaldo());
}

TEST_CASE("Adicionar valor ao saldo do Comprador") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    comprador->setSaldo(100);
    comprador->adicionarValorSaldo(100);
    CHECK(comprador->getSaldo() == 200);
}

TEST_CASE("Adicionar valor negativo ao saldo do Comprador") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    comprador->setSaldo(100);
    CHECK_THROWS_AS(comprador->adicionarValorSaldo(-100), std::runtime_error);
}

TEST_CASE("Adicionar produto ao carrinho") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    comprador->adicionarAoCarrinho(produto, 10);
    CHECK(comprador->getCarrinhoCompras().size() == 1);
}

TEST_CASE("Esvaziar carrinho") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    comprador->adicionarAoCarrinho(produto, 10);
    comprador->esvaziarCarrinho();
    CHECK(comprador->getCarrinhoCompras().size() == 0);
}

TEST_CASE("Esvaziar carrinho ja vazio") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    CHECK_THROWS_AS(comprador->esvaziarCarrinho(), std::runtime_error);
}

TEST_CASE("Procurar produto existente no banco de dados") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    
    int idProd = ServicoProduto::criar("remover produto de teste", 10, "produto de teste - remover");
    ServicoEstoque::inserirProduto(idProd, 1, 10, "un");
    
    vector<Produto*> produtosBuscados = comprador->procurarProdutos("remover");

    ServicoEstoque::deletarProdutoEstoque(idProd);
    ServicoProduto::deletar(idProd);

    CHECK(produtosBuscados[0]->getID() == idProd);
}

TEST_CASE("Procurar produto inexistente no banco de dados") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    
    vector<Produto*> produtosBuscados = comprador->procurarProdutos("123400000000");

    CHECK(produtosBuscados.size() == 0);
}

TEST_CASE("Listar produtos disponíveis") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    
    int idProd = ServicoProduto::criar("remover produto de teste", 10, "produto de teste - remover");
    ServicoEstoque::inserirProduto(idProd, 1, 0, "un");
    
    vector<Produto*> produtosDisponiveis = comprador->listarProdutosDisponiveis();
    
    int encontrado;
    for (auto produto : produtosDisponiveis) {
        if (produto->getID() == idProd) {
            encontrado = 1;
            break;
        }
    }
    ServicoEstoque::deletarProdutoEstoque(idProd);
    ServicoProduto::deletar(idProd);

    CHECK(encontrado == 1);
}

TEST_CASE("Selecionar produtos de uma lista sem produtos") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador *comprador = new Comprador(usuario);
    
    vector<Produto*> produtosListados;
    
    CHECK_THROWS_AS(comprador->selecionarProdutos(produtosListados), std::runtime_error);
}

TEST_CASE("Selecionar produtos de uma lista com produtos") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador *comprador = new Comprador(usuario);
    
    int idProd = ServicoProduto::criar("produto de teste 1", 10, "produto de teste - remover");
    ServicoEstoque::inserirProduto(idProd, 1, 10, "un");
    
    int idProd2 = ServicoProduto::criar("produto de teste 2", 15, "produto de teste - remover");
    ServicoEstoque::inserirProduto(idProd2, 1, 2, "un");

    vector<Produto*> produtosListados;
    produtosListados.push_back(new Produto(idProd, 1, "produto de teste 1", 10, 10, "un", "teste"));
    produtosListados.push_back(new Produto(idProd2, 1, "produto de teste 2", 2, 15, "un", "teste"));
    
    ServicoEstoque::deletarProdutoEstoque(idProd);
    ServicoProduto::deletar(idProd);
    ServicoEstoque::deletarProdutoEstoque(idProd2);
    ServicoProduto::deletar(idProd2);
    

    cout << "Produtos disponíveis: " << endl;
    cout << "Produto teste 1 - ID: " << idProd << " - Quantidade: 10" << endl;
    cout << "Produto teste 2 - ID: " << idProd2 << " - Quantidade: 2" << endl;
    CHECK_NOTHROW(comprador->selecionarProdutos(produtosListados));
}

TEST_CASE("Finalizar compra com carrinho vazio") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    CHECK_THROWS_AS(comprador->finalizarCompra(), std::runtime_error);
}

TEST_CASE("Finalizar compra sem saldo") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    comprador->adicionarAoCarrinho(produto, 10);
    
    CHECK_NOTHROW(comprador->finalizarCompra());
}

TEST_CASE("Finalizar compra com saldo") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    comprador->setSaldo(10000);
    Produto* produto = new Produto(1, 3, "teste", 10, 20, "un", "teste");
    comprador->adicionarAoCarrinho(produto, 10);
    
    CHECK_NOTHROW(comprador->finalizarCompra());
}

TEST_CASE("Verificar a quantidade de um produto no carrinho") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    comprador->adicionarAoCarrinho(produto, 10);
    CHECK(comprador->verificarQuantidadeProdutoCarrinho(1) == 10);
}

TEST_CASE("Histórico de um comprador sem transações") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    comprador->setID(1567);
    CHECK_THROWS_AS(comprador->historicoComprador(), std::runtime_error);
}

TEST_CASE("Remover item do carrinho") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    comprador->adicionarAoCarrinho(produto, 10);
    comprador->removerItemCarrinho(1);
    CHECK(comprador->getCarrinhoCompras().size() == 0);
}

TEST_CASE("Remover item do carrinho inexistente") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    comprador->adicionarAoCarrinho(produto, 10);
    CHECK_THROWS_AS(comprador->removerItemCarrinho(2), std::runtime_error);
}

TEST_CASE("Visualizar carrinho com produto") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    comprador->adicionarAoCarrinho(produto, 10);
    CHECK_NOTHROW(comprador->visualizarCarrinho());
}

TEST_CASE("Visualizar carrinho sem produto") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    CHECK_THROWS_AS(comprador->visualizarCarrinho(), std::runtime_error);
}

TEST_CASE("Obter carrinho de um comprador") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");
    comprador->adicionarAoCarrinho(produto, 10);
    CHECK(comprador->getCarrinhoCompras().size() == 1);
}

TEST_CASE("Recuperar carrinho de um comprador") {
    Usuario* usuario = new Usuario("teste", "teste", "teste", 'c');
    Comprador* comprador = new Comprador(usuario);
    Produto* produto = new Produto(1, 3, "teste", 100, 50.5, "un", "teste");

    multimap<Produto*, double> carrinho;
    carrinho.insert({produto, 10});

    comprador->recuperarCarrinho(carrinho);
    CHECK(comprador->getCarrinhoCompras().size() == 1);
}