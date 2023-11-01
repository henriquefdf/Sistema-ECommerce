#include "uteis.cpp"

#include "../../include/services/ServicoTransacoes.hpp"

using std::to_string;

/**
 * @brief Método para salvar uma transação no banco de dados
 * @param idComprador ID do comprador
 * @param idVendedor ID do vendedor
 * @param idProduto ID do produto
 * @param qtdProduto Quantidade do produto
 * @param data Data da transação (dia/mês/ano)
 * @param valorTotal Valor total da transação
 * @param tipoPagamento Tipo de pagamento (saldo na conta do usuário)
 * @return ID da transação, ou -1 se não foi possível criar a transação
*/
int ServicoTransacoes::criar(int idComprador, int idVendedor, int idProduto, double qtdProduto, string data, double valorTotal, string tipoPagamento) {
    string sqlToExecute =
        "INSERT INTO TRANSACAO (idComprador, idVendedor, idProduto, qtdProduto, data, valorTotal, tipoPagamento) VALUES('" 
        + to_string(idComprador)    + "', '" 
        + to_string(idVendedor)     + "', '" 
        + to_string(idProduto)      + "', '" 
        + to_string(qtdProduto)     + "', '" 
        + data                      + "', '" 
        + to_string(valorTotal)     + "', '" 
        + tipoPagamento             + "');";

    try {
        sqlite3 *database = abrirBanco();
        char *messageError;

        int exit = sqlite3_exec(database, sqlToExecute.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Erro na criação de transação: " << messageError << endl;
            sqlite3_free(messageError);
            return -1;
        }

        int id = sqlite3_last_insert_rowid(database);
        sqlite3_close(database);
        return id;
    }
    catch (const exception &e) {
        cerr << "Erro na criação de transação: " << e.what() << endl;
        return -1;
    }
}

/**
 * @brief Método para selecionar as transações de um usuário do banco de dados
 * @param id ID do usuário
 * @param tipoUsuario Tipo de usuário (comprador ou vendedor)
 * @return Lista de transações do usuário em um vector de transações
*/
vector<Transacao*> ServicoTransacoes::selecionarTransacoes(int id, char tipoUsuario){
    vector<Transacao*> transacoes;
    string sqlToExecute;
    if (tipoUsuario == 'c'){
        sqlToExecute = 
            "SELECT TRANSACAO.idTransacao, TRANSACAO.idComprador, TRANSACAO.idVendedor, TRANSACAO.idProduto, TRANSACAO.qtdProduto, TRANSACAO.data, TRANSACAO.valorTotal, TRANSACAO.tipoPagamento, PRODUTO.nomeProduto, COMPRADOR.nome, VENDEDOR.nome FROM TRANSACAO "
            "INNER JOIN USUARIO AS VENDEDOR ON TRANSACAO.idVendedor = VENDEDOR.idUsuario "
            "INNER JOIN PRODUTO ON TRANSACAO.idProduto = PRODUTO.idProduto "
            "INNER JOIN USUARIO AS COMPRADOR ON TRANSACAO.idComprador = COMPRADOR.idUsuario "
            "WHERE COMPRADOR.idUsuario = '" + to_string(id) +  "'";
    } else {
        sqlToExecute = 
            "SELECT TRANSACAO.idTransacao, TRANSACAO.idComprador, TRANSACAO.idVendedor, TRANSACAO.idProduto, TRANSACAO.qtdProduto, TRANSACAO.data, TRANSACAO.valorTotal, TRANSACAO.tipoPagamento, PRODUTO.nomeProduto, COMPRADOR.nome, VENDEDOR.nome FROM TRANSACAO "
            "INNER JOIN USUARIO AS VENDEDOR ON TRANSACAO.idVendedor = VENDEDOR.idUsuario "
            "INNER JOIN PRODUTO ON TRANSACAO.idProduto = PRODUTO.idProduto "
            "INNER JOIN USUARIO AS COMPRADOR ON TRANSACAO.idComprador = COMPRADOR.idUsuario "
            "WHERE VENDEDOR.idUsuario = '" + to_string(id) +  "'";
    }
        
    try { 
        sqlite3 *database = abrirBanco();

        sqlite3_stmt* stmt;
        int exit = sqlite3_prepare_v2(database, sqlToExecute.c_str(), -1, &stmt, NULL);

        if (exit != SQLITE_OK){
            cout << exit << endl;
            cerr << "Erro ao buscar transacoes. Tente novamente." << endl;
            sqlite3_finalize(stmt);
            sqlite3_close(database);
            return transacoes;
        }

        while((exit = sqlite3_step(stmt)) == SQLITE_ROW){
            int id = stoi( string((char *) sqlite3_column_text(stmt, 0)) );
            int idComprador = stoi( string((char *) sqlite3_column_text(stmt, 1)) );
            int idVendedor = stoi( string((char *) sqlite3_column_text(stmt, 2)) );
            int idProduto = stoi( string((char *) sqlite3_column_text(stmt, 3)) );
            double qtdProduto = stod( string((char *) sqlite3_column_text(stmt, 4)) );
            string data = string((char *) sqlite3_column_text(stmt, 5));
            double valorTotal = stod( string((char *) sqlite3_column_text(stmt, 6)) );
            string tipoPagamento = string((char *) sqlite3_column_text(stmt, 7));
            string nomeProduto = string((char *) sqlite3_column_text(stmt, 8));
            string nomeComprador = string((char *) sqlite3_column_text(stmt, 9));
            string nomeVendedor= string((char *) sqlite3_column_text(stmt, 10));

            Transacao* transacao = new Transacao(id, idComprador, idVendedor, idProduto, qtdProduto, data, valorTotal, tipoPagamento, nomeComprador, nomeVendedor, nomeProduto);

            transacoes.push_back(transacao);
        } 

        sqlite3_finalize(stmt);
        sqlite3_close(database);
        return transacoes;
    } catch(const exception &e) {
        cerr << "Erro ao buscar transacoes." << e.what() << endl;
    }
    
    return transacoes;
}

/**
 * @brief Método para efetuar a compra de um produto e realizar as operações necessárias no banco de dados
 * @details Este método chama os métodos de inserir a transação no banco de dados, atualizar o saldo do vendedor e atualizar o estoque conforme a quantidade de produtos comprados
 * @param idComprador ID do comprador
 * @param carrinho Carrinho de compras do comprador
 * @param valorTotal Valor total da compra
 * @param tipoPagamento Tipo de pagamento da compra
 * @param saldoComprador Saldo do comprador
*/ 
void ServicoTransacoes::efetuarCompra(int idComprador, std::multimap<Produto*, double> carrinho, double valorTotal, string tipoPagamento, double saldoComprador) {
   time_t now = time(0);
   tm *horarioLocal = localtime(&now);
   int mesInicialTimeLib = 1;
   int anoInicialTimeLib = 1900;
   int diaAtual = horarioLocal->tm_mday;
   int mesAtual = mesInicialTimeLib + horarioLocal->tm_mon;
   int anoAtual = anoInicialTimeLib + horarioLocal->tm_year;
   string data = to_string(diaAtual) + "/" + to_string(mesAtual) + "/" + to_string(anoAtual);


    // Inserir na tabela transacoes
   for (auto itemCarrinho : carrinho) {
        //itemCarrinho: first: Produto, second: quantidade
        int idVendedor = itemCarrinho.first->getIdVendedor();
        int idProduto = itemCarrinho.first->getID();
        double preco = itemCarrinho.first->getPreco();
        double quantidadeEstoque = itemCarrinho.first->getQuantidade();
        double quantidadeComprada = itemCarrinho.second;
        double valorProdQuantidade = itemCarrinho.first->getPreco() * quantidadeComprada;
        string medidaQtd = itemCarrinho.first->getUnidadeMedida();

        criar(idComprador, idVendedor, idProduto, quantidadeComprada, data, valorProdQuantidade, tipoPagamento);

        // Incrementar saldo vendedor
        double valorAdicionarVendedor = preco * quantidadeComprada; 
        ServicoVendedor::atualizarSaldo(idVendedor, valorAdicionarVendedor);

        // Deduzir quantidade estoque
        int quantidadeAtualizada = quantidadeEstoque - quantidadeComprada;
        ServicoEstoque::atualizar(idProduto, idVendedor, quantidadeAtualizada, medidaQtd);
   }
}

/**
 * @brief Método para calcular o valor total de uma transação
 * @param carrinho Carrinho de compras a partir do qual o valor total será calculado
*/
double ServicoTransacoes::calcularValorTotalCompra(std::multimap<Produto*, double> carrinho) { 
    double valorTotal = 0.0;

    for (auto itemCarrinho : carrinho) {
        valorTotal += itemCarrinho.first->getPreco() * itemCarrinho.second;
    }

    return valorTotal;
}

/**
 * @brief Método para deletar uma transação após um teste
 * @param idTransacao ID da transação a ser deletada
 * @return 1 caso a transação tenha sido deletada, -1 caso contrário
*/
int ServicoTransacoes::deletar(int idTransacao) {
    string sqlToExecute = "DELETE FROM TRANSACAO WHERE idTransacao = '" + std::to_string(idTransacao) + "'";

    try {
        sqlite3 *database = abrirBanco();
        char *messageError;

        int exit = sqlite3_exec(database, sqlToExecute.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            sqlite3_free(messageError);
            return -1;
        }

        sqlite3_close(database);  
        return 1;
    }
    catch (const exception &e) {
        return -1;
    }
}
