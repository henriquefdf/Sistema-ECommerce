#include "uteis.cpp"
#include "../../include/services/ServicoVendedor.hpp"

/**
 * @brief criar um novo vendedor
 * @param id - id do vendedor
 * @return id do vendedor criado, 0 se não foi possível criar
 */
int ServicoVendedor::criar(int id) {;
    string sqlToExecute =
        "INSERT INTO VENDEDOR (idVendedor) VALUES('" + std::to_string(id) + "');";

    try {
       sqlite3 *database = abrirBanco();
        char *messageError;
        
        int exit = sqlite3_exec(database, sqlToExecute.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Erro na inserção de vendedor: " << messageError << endl;
            sqlite3_free(messageError);
            return 0;
        }

        sqlite3_close(database);
        return id;
    }
    catch (const exception &e) {
        cerr << "Erro na inserção de vendedor: " << e.what() << endl;
    }

    return 0;
}


/**
 * @brief deletar um vendedor
 * @param id - id do vendedor
 * @return 1 se deletou, 2 se a operação não foi concluída com sucesso
 */
int ServicoVendedor::deletar(int id) {
    string sqlToExecute = "DELETE FROM VENDEDOR WHERE idVendedor = '" + std::to_string(id) + "'";

    try {
        sqlite3 *database = abrirBanco();
        char *messageError;

        int exit = sqlite3_exec(database, sqlToExecute.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Erro na deleção de vendedor: " << messageError << endl;
            sqlite3_free(messageError);
            return 2;
        }

        return 1;
    }
    catch (const exception &e) {
        cerr << "Erro na deleção de vendedor: " << e.what() << endl;
        return 2;
    }
}

/**
 * @brief atualizar saldo do vendedor
 * @param id - id do vendedor
 * @param saldoAdicionar - saldo a ser adicionado
 * @return 1 se atualizou, 2 se a operação não foi concluída com sucesso
 */
int ServicoVendedor::atualizarSaldo(int id, double saldoAdicionar) {
    double saldoAtual;
    double novoSaldo;

    try {
        string sqlToExecute = "SELECT saldo FROM USUARIO "
       "WHERE idUsuario = '"   + std::to_string(id)   + "'";

        sqlite3 *database = abrirBanco();
        sqlite3_stmt* stmt;

        int exit = sqlite3_prepare_v2(database, sqlToExecute.c_str(), -1, &stmt, NULL);

        if (exit != SQLITE_OK){
            cerr << "Erro ao buscar saldo do usuario com id " << id << endl;
            sqlite3_finalize(stmt);
            return 2;
        }
        
        exit = sqlite3_step(stmt);
        if (exit == SQLITE_ROW) {
            saldoAtual = stod( string((char *) sqlite3_column_text(stmt, 0)) ); 
        } else {
            return 2;
        }

        sqlite3_finalize(stmt);

        novoSaldo = saldoAtual + saldoAdicionar;

        sqlToExecute = "UPDATE USUARIO SET saldo = '" + std::to_string(novoSaldo) + "' "
        +   "WHERE idUsuario = '"   + std::to_string(id)   + "'";

        char *messageError;

        exit = sqlite3_exec(database, sqlToExecute.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Erro na adição de valor ao saldo: " << messageError << endl;
            sqlite3_free(messageError);
            sqlite3_close(database);
            return 2;
        }

        sqlite3_close(database);
        return 1;
    }
    catch (const exception &e) {
        cerr << "Erro na adição de valor ao saldo: " << e.what() << endl;
        return 2;
    }
}