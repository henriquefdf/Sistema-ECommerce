#include "../../include/services/ServicoUsuario.hpp"
#include "../../include/services/ServicoComprador.hpp"
#include "../../include/services/ServicoVendedor.hpp"
#include "uteis.cpp"

/**
 * @brief criar um novo usuario
 * @param id - id do usuario
 * @param nome - nome do usuario
 * @param email - email do usuario
 * @param senha - senha do usuario
 * @param tipo - tipo do usuario
 * @return id do usuario se o usuario foi criado, 0 caso contrário, 2 se já existe um usuario com o mesmo login
 */
int ServicoUsuario::criar(string nome, string nomeUsuario, string senha, char tipoUsuario, double saldo) {
    if(existeLogin(nomeUsuario)){
        return 2;
    }
    string sqlToExecute =
        "INSERT INTO USUARIO(nome, login, senha, tipoUsuario, saldo) VALUES('" 
        + nome              + "', '" 
        + nomeUsuario       + "', '" 
        + senha             + "', '" 
        + tipoUsuario       + "', '" 
        + std::to_string(saldo)  + "');";

    try {
        sqlite3 *database;
        const char *databaseFileName = "database/database.db";
        int exit = sqlite3_open(databaseFileName, &database);
        if (exit != SQLITE_OK) {
            cout << exit << endl;
            cerr << "Erro em abrir o banco." << endl;
        }

        char *messageError;

        exit = sqlite3_exec(database, sqlToExecute.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Erro na inserção de usuário: " << messageError << endl;
            sqlite3_free(messageError);
            return 0;
        } else {
            sqlite3_close(database);
            return inserirUsuario(nomeUsuario, tipoUsuario);
        }
    }
    catch (const exception &e) {
        cerr << "Erro na inserção de usuário: " << e.what() << endl;
        return 0;
    }
}

/**
 * @brief listar usuario especifico
 * @param login - login do usuario
 * @return retorna um usuario
 */
Usuario* ServicoUsuario::getUsuario(string login) {
    Usuario* usuario;

    string sqlToExecute = "SELECT * FROM USUARIO WHERE login = '" + login + "'";

    try {
        sqlite3 *database = abrirBanco();
        sqlite3_stmt* stmt;

        int exit = sqlite3_prepare_v2(database, sqlToExecute.c_str(), -1, &stmt, NULL);

        if (exit != SQLITE_OK){
            sqlite3_finalize(stmt);
        }
        
        exit = sqlite3_step(stmt);
        if (exit == SQLITE_ROW) {
            int idUsuario = stoi( string((char *) sqlite3_column_text(stmt, 0)) );
            string nome = string((char *) sqlite3_column_text(stmt, 1));    
            string senha = string((char *) sqlite3_column_text(stmt, 3));
            char tipoUsuario = string((char *) sqlite3_column_text(stmt, 4))[0];
            double saldo = stod( string((char *) sqlite3_column_text(stmt, 5)) );
            
            usuario = new Usuario(login, senha, nome, tipoUsuario);
            usuario->setID(idUsuario);
            usuario->setSaldo(saldo);

            sqlite3_finalize(stmt);  
            sqlite3_close(database);
            return usuario;
        } else {
            return nullptr;
        }
    } catch (const exception &e){
        cerr << "Erro ao buscar usuários: " << e.what() << endl;
        return nullptr;
    }
}

/**
 * @brief verifica se o usuario possui um login
 * @return true se o usuario possui um login
 */
bool ServicoUsuario::existeLogin(string login) {
    string sqlToExecute = "SELECT idUsuario FROM USUARIO WHERE login = '" + login + "'";

    try {
        sqlite3 *database = abrirBanco();
        sqlite3_stmt* stmt;

        int exit = sqlite3_prepare_v2(database, sqlToExecute.c_str(), -1, &stmt, NULL);

        if (exit != SQLITE_OK){
            sqlite3_finalize(stmt);
        }
        
        exit = sqlite3_step(stmt);
        if (exit == SQLITE_ROW) {
            sqlite3_finalize(stmt);  
            sqlite3_close(database);
            return true;
        } else {
            sqlite3_finalize(stmt);  
            sqlite3_close(database);
            return false;
        }
    } catch (const exception &e){
        cerr << "Erro ao buscar usuários: " << e.what() << endl;
        return true;
    }
}

/**
 * @brief adicionar um login para um usuario
 * @return id do usuario foi adicionado com sucesso, 0 caso contrario
 */
int ServicoUsuario::inserirUsuario(string login, char tipoUsuario) {
    int idUsuario;

    string sqlToExecute = "SELECT idUsuario FROM USUARIO WHERE login = '" + login + "'";

    try {
        sqlite3 *database = abrirBanco();
        sqlite3_stmt* stmt;

        int exit = sqlite3_prepare_v2(database, sqlToExecute.c_str(), -1, &stmt, NULL);

        if (exit != SQLITE_OK){
            cout << exit << endl;
            cerr << "Erro ao inserir usuário com login " << login << endl;
            sqlite3_finalize(stmt);
            return 0;
        }
        
        exit = sqlite3_step(stmt);
        if (exit == SQLITE_ROW) {
            idUsuario = stoi( string((char *) sqlite3_column_text(stmt, 0)) ); 
        }

        sqlite3_finalize(stmt);
        sqlite3_close(database);

        if (tipoUsuario == 'c') {
            return ServicoComprador::criar(idUsuario);
        } else if (tipoUsuario == 'v') {
            return ServicoVendedor::criar(idUsuario);
        }
    } catch (const exception &e){
        cerr << "Erro ao buscar usuários: " << e.what() << endl;
        return 0;
    }
    return 0;
}

/**
 * @brief deletar um usuario
 * @param id - id do usuario
 * @return 1 se o usuario foi deletado com sucesso, 2 caso tenha ocorrido algum erro
 */
int ServicoUsuario::deletar(int id) {
    string sqlToExecute = "DELETE FROM USUARIO WHERE idUsuario = '" + std::to_string(id) + "'";

    try {
        sqlite3 *database = abrirBanco();
        char *messageError;

        int exit = sqlite3_exec(database, sqlToExecute.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Erro na deleção de usuário: " << messageError << endl;
            sqlite3_free(messageError);
            return 2;
        }

        sqlite3_close(database);  
        return 1;
    }
    catch (const exception &e) {
        cerr << "Erro na deleção de usuário: " << e.what() << endl;
        return 2;
    }
}