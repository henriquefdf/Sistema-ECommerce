#include "uteis.cpp"
#include "../../include/services/ServicoComprador.hpp"

using std::to_string;

/**
 * @brief cria um comprador
 * @param id  - id do comprador
 * @return id do comprador criado, ou 0 se não foi possível criar o comprador
 */
int ServicoComprador::criar(int id) {
    string sqlToExecute =
        "INSERT INTO COMPRADOR (idComprador) VALUES('" + to_string(id) + "');";

    try {
        sqlite3 *database = abrirBanco();
        char *messageError;

        int exit = sqlite3_exec(database, sqlToExecute.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Erro na inserção de comprador: " << messageError << endl;
            sqlite3_free(messageError);
            return 0;
        }

        sqlite3_close(database);
        return id;
    }
    catch (const exception &e) {
        cerr << "Erro na inserção de comprador: " << e.what() << '\n';
    }
    return 0;
}

/**
 * @brief deleta um comprador
 * @param id  - id do comprador
 * @return 1 se deletou, 2 se a operação não foi concluída com sucesso
 */
int ServicoComprador::deletar(int id) {
    string sqlToExecute = "DELETE FROM COMPRADOR WHERE idComprador = '" + to_string(id) + "'";

    try {
        sqlite3 *database = abrirBanco();
        char *messageError;

        int exit = sqlite3_exec(database, sqlToExecute.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Erro na deleção de comprador: " << messageError << endl;
            sqlite3_free(messageError);
            return 2;
        }

        return 1;
    }
    catch (const exception &e) {
        cerr << "Erro na deleção de comprador: " << e.what() << '\n';
        return 2;
    }
}

/**
 * @brief atualiza o saldo do comprador
 * @param id - id do comprador
 * @param saldoAtualizado - saldo que acabou de adicionar e atualiza no banco de dados
 * @return 1 se atualizou, 2 se a operação não foi concluída com sucesso
 */
int ServicoComprador::atualizarSaldo(int id, double saldoAtualizado) {
    string sqlToExecute = "UPDATE USUARIO SET saldo = '" + to_string(saldoAtualizado) + "' "
    +   "WHERE idUsuario = '"   + to_string(id)   + "'";

    try {
        sqlite3 *database = abrirBanco();
        char *messageError;

        int exit = sqlite3_exec(database, sqlToExecute.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Erro na adição de valor ao saldo: " << messageError << endl;
            sqlite3_free(messageError);
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