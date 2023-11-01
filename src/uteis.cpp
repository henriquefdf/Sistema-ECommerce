#include <iostream>
#include <map>
#include "../lib/cores.hpp"

using std::cout;
using std::exception;
using std::cerr;
using std::endl;
using std::string;
using std::cin;

/**
 * @brief Função que contém as strings com o conteúdo dos menus
 * @param chave Chave do menu, indica quem será exibido
 * @return string - Conteúdo do menu
 */
string opcoesMenu(string chave) {
    std::map<string, string> opcoes;
    
    opcoes.insert({"menuPrincipalOpcoes", 

        "1 - Login\n"
        "2 - Cadastro\n"
        "3 - Sair\n"
        CIANO "> " RESET
    });

    opcoes.insert({"opcoesComprador",
        "Escolha uma opcao:\n"
        "1 - Visualizar meu saldo\n"
        "2 - Adicionar valor ao meu saldo\n"
        "3 - Pesquisar por produto para adicionar ao carrinho\n"
        "4 - Listar produtos disponíveis para adicionar ao carrinho\n"
        "5 - Finalizar compra dos produtos no carrinho\n"
        "6 - Esvaziar carrinho\n"
        "7 - Visualizar meu histórico de compras\n"
        "8 - Visualizar carrinho de compras\n"
        "9 - Retirar item do carrinho\n"
        "10 - Logout\n"
        CIANO "> " RESET
    });

    opcoes.insert({"opcoesVendedor",
        "Escolha uma opcao:\n"
        "1 - Visualizar o estoque da minha loja\n"
        "2 - Visualizar meu histórico de vendas\n"
        "3 - Visualizar meu lucro total\n"
        "4 - Alterar informações de um produto em estoque\n"
        "5 - Adicionar produto no meu estoque\n"
        "6 - Deletar produto do meu estoque\n"
        "7 - Logout\n"
        CIANO "> " RESET 
    });

    return opcoes.find(chave)->second;
}
