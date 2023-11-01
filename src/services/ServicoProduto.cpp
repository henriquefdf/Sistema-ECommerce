#include "uteis.cpp"

using std::to_string;

#include "../../include/services/ServicoProduto.hpp"

/**
 * @brief criar um novo produto
 * @param nomeProduto 
 * @param precoProduto 
 * @param descricaoProduto 
 * @return id se der certo, caso contrario -1
 */
int ServicoProduto::criar(string nomeProduto, double precoProduto, string descricaoProduto) {
    string sqlToExecute =
        "INSERT INTO PRODUTO (nomeProduto, precoProduto, descricaoProd) VALUES('" + nomeProduto + "', '" + to_string(precoProduto) + "', '" + descricaoProduto + "');";

    try {
        sqlite3 *database = abrirBanco();
        char *messageError;

        int exit = sqlite3_exec(database, sqlToExecute.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Erro na inserção de produto: " << messageError << endl;
            sqlite3_free(messageError);
            return -1;
        }

        int id = sqlite3_last_insert_rowid(database);
        sqlite3_close(database);
        return id;
    } catch (const exception &e) {
        cerr << "Erro na inserção de produto: " << e.what() << endl;
        return -1;
    }
}

/**
 * @brief deletar um produto
 * @param id - do produto
 * @return o número de produtos deletados, -1 se der erro
 */
int ServicoProduto::deletar(int id) {
    string sqlToExecute = "DELETE FROM PRODUTO WHERE idProduto = '" + to_string(id) + "'";

    try {
        sqlite3 *database = abrirBanco();
        char *messageError;

        int exit = sqlite3_exec(database, sqlToExecute.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Erro na deleção de produto: " << messageError << endl;
            sqlite3_free(messageError);
            return -1;
        }

        int produtosDeletados = sqlite3_changes(database);
        sqlite3_close(database);

        return produtosDeletados;
    } catch (const exception &e) {
        cerr << "Erro na deleção do produto: " << e.what() << endl;
        return -1;
    }
}

/**
 * @brief atualizar um produto
 * @param id - do produto
 * @param nomeProduto - nome do produto
 * @param precoProduto - preco do produto
 * @param descricaoProduto - descricao do produto
 */
int ServicoProduto::atualizar(int id, string nomeProduto, double precoProduto, string descricaoProduto) {
    string sqlToExecute = "UPDATE PRODUTO SET nomeProduto = '" + nomeProduto + "', "
    +   "precoProduto = '"      + to_string(precoProduto) + "', "
    +   "descricaoProd = '"     + descricaoProduto + "' "
    +   "WHERE idProduto = '"   + to_string(id) + "'";

    try {
        sqlite3 *database = abrirBanco();
        char *messageError;

        int exit = sqlite3_exec(database, sqlToExecute.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Erro na atualização de produto: " << messageError << endl;
            sqlite3_free(messageError);
            return -1;
        }

        int produtosAtualizados = sqlite3_changes(database);
        sqlite3_close(database);

        return produtosAtualizados;
    } catch (const exception &e) {
        cerr << "Erro na atualização de produto: " << e.what() << endl;
        return -1;
    }
}

/**
 * @brief buscar um produto
 * @param id - do produto
 * @return produto se der certo, caso contrario NULL
 */
string ServicoProduto::buscarProduto(int id) {
    string nomeProd;
    string sqlToExecute = "SELECT nomeProduto FROM PRODUTO WHERE idProduto = '" + to_string(id) + "'";

    try {
        sqlite3 *database = abrirBanco();
        sqlite3_stmt* stmt;

        int exit = sqlite3_prepare_v2(database, sqlToExecute.c_str(), -1, &stmt, NULL);

        if (exit != SQLITE_OK){
            sqlite3_finalize(stmt);
            return "";
        }
        
        exit = sqlite3_step(stmt);
        if (exit == SQLITE_ROW) {
            nomeProd = string((char *) sqlite3_column_text(stmt, 0));
            sqlite3_finalize(stmt);  
            sqlite3_close(database);
            return nomeProd;
        } else {
            sqlite3_finalize(stmt);  
            sqlite3_close(database);
            return "";
        }
    } catch (const exception &e){
        cerr << "Erro ao buscar usuários: " << e.what() << endl;
        return "";
    }
}
