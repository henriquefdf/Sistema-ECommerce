#include "uteis.cpp"

#include "../../include/services/ServicoEstoque.hpp"

/**
 * @brief Método que insere um produto no banco de dados
 * @param idProduto ID do produto
 * @param idVendedor ID do vendedor do produto
 * @param qtdProduto Quantidade do produto em estoque
 * @param medidaQtd Unidade de medida do produto (unidade, kg, litro, etc)
 * @return 1 se o produto foi inserido, -1 caso contrário
*/
int ServicoEstoque::inserirProduto(int idProduto, int idVendedor, double qtdProduto, string medidaQtd) {
    string sqlToExecute =
        "INSERT INTO ESTOQUE (idProduto, idVendedor, qtdProduto, medidaQtd) VALUES('" 
        + to_string(idProduto)  + "', '" 
        + to_string(idVendedor) + "', '" 
        + to_string(qtdProduto) + "', '" 
        + medidaQtd             + "');";

    try {
        sqlite3 *database = abrirBanco();
        char *messageError;

        int exit = sqlite3_exec(database, sqlToExecute.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Erro na inserção de produto no estoque: " << messageError << endl;
            sqlite3_free(messageError);
        }

        sqlite3_close(database);
        return 1;
    }
    catch (const exception &e) {
        cerr << "Erro na inserção de produto no estoque: " << e.what() << endl;
        return -1;
    }
}

/**
 * @brief Método que atualiza as informações de um produto na tabela de estoque
 * @param idProduto ID do produto
 * @param idVendedor ID do vendedor do produto
 * @param qtdProduto Nova quantidada do produto em estoque
 * @param medidaQtd Nova unidade de medida do produto (unidade, kg, litro, etc)
 * @return 1 se o produto foi atualizado, -1 caso contrário
*/
int ServicoEstoque::atualizar(int idProduto, int idVendedor, double qtdProduto, string medidaQtd) {
    string sqlToExecute = "UPDATE ESTOQUE SET idProduto = '" + to_string(idProduto) + "', "
    +   "idVendedor = '"        + to_string(idVendedor)  + "', "
    +   "qtdProduto = '"        + to_string(qtdProduto)  + "', "
    +   "medidaQtd = '"         + medidaQtd              + "' "
    +   "WHERE idProduto = '"   + to_string(idProduto)   + "' "
    +   "AND idVendedor = '"    + to_string(idVendedor)  + "'";

    try {
        sqlite3 *database = abrirBanco();
        char *messageError;

        int exit = sqlite3_exec(database, sqlToExecute.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Erro na atualização de estoque: " << messageError << endl;
            sqlite3_free(messageError);
        }

        sqlite3_close(database);
        return 1;
    }
    catch (const exception &e) {
        cerr << "Erro na atualização de estoque: " << e.what() << endl;
        return -1;
    }
}

/**
 * @brief Método que seleciona os produtos de um vendedor específico no banco de dados
 * @param idVendedor ID do vendedor
 * @return Lista de produtos do vendedor
*/
vector<Produto*> ServicoEstoque::selecionarProdutos(int idVendedor){
    vector<Produto*> produtos;
    string sqlToExecute = 
        "SELECT ESTOQUE.idProduto, PRODUTO.nomeProduto, ESTOQUE.qtdProduto, ESTOQUE.medidaQtd, PRODUTO.precoProduto, PRODUTO.descricaoProd, ESTOQUE.idVendedor FROM ESTOQUE "
        "INNER JOIN PRODUTO ON ESTOQUE.idProduto = PRODUTO.idProduto "
        "WHERE ESTOQUE.idVendedor = '" + to_string(idVendedor) + "'";

    try {
        sqlite3 *database = abrirBanco();

        sqlite3_stmt* stmt;
        int exit = sqlite3_prepare_v2(database, sqlToExecute.c_str(), -1, &stmt, NULL);

        if (exit != SQLITE_OK){
            cout << exit << endl;
            cerr << "Erro ao buscar produtos do vendedor com id " << idVendedor << endl;
            sqlite3_finalize(stmt);
        }

        while((exit = sqlite3_step(stmt)) == SQLITE_ROW) { 
            int id = stoi( string((char *) sqlite3_column_text(stmt, 0)) );
            string nomeProduto = string((char *) sqlite3_column_text(stmt, 1)) ;
            double qtdProduto = stod( string((char *) sqlite3_column_text(stmt, 2)) );
            string medidaQtd = string((char *) sqlite3_column_text(stmt, 3)) ;
            double precoProduto = stod( string((char *) sqlite3_column_text(stmt, 4)) );
            string descricaoProduto = string((char *) sqlite3_column_text(stmt, 5)) ;
            int idVendedor = stoi( string((char *) sqlite3_column_text(stmt, 6)) );

            Produto* produto = new Produto(id, idVendedor, nomeProduto, qtdProduto, precoProduto, medidaQtd, descricaoProduto);

            produtos.push_back(produto);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(database);
        return produtos;
    } catch (const exception &e){
        cerr << "Erro ao buscar produtos do vendedor: " << e.what() << endl;
        return produtos;
    }
}

/**
 * @brief Método que seleciona produtos com nome específico no banco de dados
 * @param produto Nome do produto
 * @return Lista de produtos com nome específico
*/
vector<Produto*> ServicoEstoque::selecionarProdutosEspecificos(string produto){ 
    vector<Produto*> produtos;
    string sqlToExecute = 
        "SELECT ESTOQUE.idProduto, PRODUTO.nomeProduto, PRODUTO.precoProduto, PRODUTO.descricaoProd, ESTOQUE.qtdProduto, ESTOQUE.medidaQtd, ESTOQUE.idVendedor FROM ESTOQUE "
        "INNER JOIN PRODUTO ON ESTOQUE.idProduto = PRODUTO.idProduto "
        "WHERE PRODUTO.nomeProduto LIKE '%" + produto + "%'";

    try { 
        sqlite3 *database = abrirBanco();

        sqlite3_stmt* stmt;
        int exit = sqlite3_prepare_v2(database, sqlToExecute.c_str(), -1, &stmt, NULL);

        if (exit != SQLITE_OK){
            cerr << "Erro ao buscar produtos em estoque. Tente novamente." << endl;
            sqlite3_finalize(stmt);
            sqlite3_close(database);
            return produtos;
        }

        while((exit = sqlite3_step(stmt)) == SQLITE_ROW) { 
            int id = stoi( string((char *) sqlite3_column_text(stmt, 0)) );
            string nomeProduto = string((char *) sqlite3_column_text(stmt, 1)) ;
            double precoProduto = stod( string((char *) sqlite3_column_text(stmt, 2)) );
            string descricaoProduto = string((char *) sqlite3_column_text(stmt, 3)) ;
            double qtdProduto = stod( string((char *) sqlite3_column_text(stmt, 4)) );
            string medidaQtd = string((char *) sqlite3_column_text(stmt, 5)) ;
            int idVendedor = stoi( string((char *) sqlite3_column_text(stmt, 6)) );

            Produto* produto = new Produto(id, idVendedor, nomeProduto, qtdProduto, precoProduto, medidaQtd, descricaoProduto);

            produtos.push_back(produto);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(database);
        return produtos;
    } catch (const exception &e){
        cerr << "Erro ao buscar produtos em estoque: " << e.what() << endl;
        return produtos;
    }
}

/**
 * @brief Método que seleciona todos os produtos em estoque no banco de dados
 * @return Lista de produtos em estoque
*/ 
vector<Produto*> ServicoEstoque::listarTodosProdutos(){ 
    vector<Produto*> produtos;
    string sqlToExecute = 
        "SELECT ESTOQUE.idProduto, PRODUTO.nomeProduto, PRODUTO.precoProduto, PRODUTO.descricaoProd, ESTOQUE.qtdProduto, ESTOQUE.medidaQtd, ESTOQUE.idVendedor FROM ESTOQUE "
        "INNER JOIN PRODUTO ON ESTOQUE.idProduto = PRODUTO.idProduto";

    try { 
        sqlite3 *database = abrirBanco();

        sqlite3_stmt* stmt;
        int exit = sqlite3_prepare_v2(database, sqlToExecute.c_str(), -1, &stmt, NULL);

        if (exit != SQLITE_OK){
            cout << exit << endl;
            cerr << "Erro ao buscar produtos em estoque" << endl;
            sqlite3_finalize(stmt);
        }

        while((exit = sqlite3_step(stmt)) == SQLITE_ROW) { 
            int id = stoi( string((char *) sqlite3_column_text(stmt, 0)) );
            string nomeProduto = string((char *) sqlite3_column_text(stmt, 1)) ;
            double precoProduto = stod( string((char *) sqlite3_column_text(stmt, 2)) );
            string descricaoProduto = string((char *) sqlite3_column_text(stmt, 3)) ;
            double qtdProduto = stod( string((char *) sqlite3_column_text(stmt, 4)) );
            string medidaQtd = string((char *) sqlite3_column_text(stmt, 5)) ;
            int idVendedor = stoi( string((char *) sqlite3_column_text(stmt, 6)) );

            Produto* produto = new Produto(id, idVendedor, nomeProduto, qtdProduto, precoProduto, medidaQtd, descricaoProduto);

            produtos.push_back(produto);
        }

        sqlite3_finalize(stmt);
        sqlite3_close(database);
        return produtos;
        
    } catch (const exception &e){
        cerr << "Erro ao buscar produtos em estoque: " << e.what() << endl;
        return produtos;
    }
}

/**
 * @brief Método que deleta um produto do banco de dados
 * @param idProduto Id do produto a ser deletado
*/
int ServicoEstoque::deletarProdutoEstoque(int idProduto) {
    string sqlToExecute = "DELETE FROM ESTOQUE WHERE idProduto = '" + to_string(idProduto) + "'";

    try {
        sqlite3 *database = abrirBanco();
        char *messageError;

        int exit = sqlite3_exec(database, sqlToExecute.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Erro na deleção de produto: " << messageError << endl;
            sqlite3_free(messageError);
        }

        int produtosDeletados = sqlite3_changes(database);
        sqlite3_close(database);

        return produtosDeletados;
    } catch (const exception &e) {
        cerr << "Erro na deleção do produto: " << e.what() << endl;
        return 0;
    }
}