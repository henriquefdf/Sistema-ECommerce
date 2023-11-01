#include <iostream>
#include <sqlite3.h>

using std::string;
using std::cout;
using std::cerr;

/**
 * @brief cria o banco de dados
 * @param databaseFileName  - nome do banco de dados
 */
static int createDB(const char* databaseFileName)
{
	sqlite3* database;

	try {
		int exit = 0;
        exit = sqlite3_open(databaseFileName, &database);

        if (exit != SQLITE_OK) {
            cout << "Erro ao criar banco de dados." << std::endl;
        } else {
            cout << "Banco de dados criado com sucesso." << std::endl;
        }

    	sqlite3_close(database);
	} catch (const std::exception& e) {
		cerr  << "Erro ao criar banco de dados: " << e.what();
	}

	return 0;
}

/**
 * @brief cria a tabela de usuarios
 * @param databaseFileName - nome do banco de dados
 */
static int createTables(const char* databaseFileName)
{
	sqlite3 *database;
	char* messageError;

	string sql = 
        "CREATE TABLE IF NOT EXISTS USUARIO("
			"idUsuario		INTEGER PRIMARY KEY AUTOINCREMENT, "
			"nome			CHAR(50) NOT NULL, "
			"login			CHAR(20) NOT NULL, "
			"senha			CHAR(50) NOT NULL, "
			"tipoUsuario	CHAR(1) NOT NULL, "
			"saldo			REAL NOT NULL "
        ");" 
		
        "CREATE TABLE IF NOT EXISTS COMPRADOR("
			"idComprador	INTEGER NOT NULL UNIQUE, "
			"FOREIGN KEY(idComprador) REFERENCES USUARIO(idUsuario)"
        ");"

		"CREATE TABLE IF NOT EXISTS VENDEDOR("
			"idVendedor		INTEGER NOT NULL UNIQUE, "
			"FOREIGN KEY(idVendedor) REFERENCES USUARIO(idVendedor)"
        ");"

        "CREATE TABLE IF NOT EXISTS PRODUTO("
			"idProduto		INTEGER PRIMARY KEY AUTOINCREMENT, "
			"nomeProduto	CHAR(50) NOT NULL, "
			"precoProduto	REAL NOT NULL, "
			"descricaoProd	TEXT "
        ");"

        "CREATE TABLE IF NOT EXISTS ESTOQUE("
            "idEstoque      INTEGER PRIMARY KEY AUTOINCREMENT, "
			"idProduto		INTEGER NOT NULL, "
			"idVendedor		INTEGER NOT NULL, "
			"qtdProduto		REAL NOT NULL, "
			"medidaQtd		CHAR(5), "
			"FOREIGN KEY(idVendedor) REFERENCES VENDEDOR(idVendedor), "
			"FOREIGN KEY(idProduto) REFERENCES PRODUTO(idProduto)"
        ");"

        "CREATE TABLE IF NOT EXISTS TRANSACAO("
			"idTransacao	INTEGER PRIMARY KEY AUTOINCREMENT, "
            "idComprador    INTEGER, "
			"idVendedor     INTEGER, "
			"idProduto      INTEGER  NOT NULL, "
			"qtdProduto     REAL NOT NULL, "
			"data           CHAR(50) NOT NULL, "
			"valorTotal     REAL  NOT NULL, "
			"tipoPagamento  CHAR(30)  NOT NULL, "
            "FOREIGN KEY(idComprador) REFERENCES VENDEDOR(idComprador),"
			"FOREIGN KEY(idVendedor) REFERENCES VENDEDOR(idVendedor),"
			"FOREIGN KEY(idProduto) REFERENCES ESTOQUE(idProduto)"
        ");"
        ;
    
	try
	{
		int exit = 0;
		exit = sqlite3_open(databaseFileName, &database);
		exit = sqlite3_exec(database, sql.c_str(), NULL, 0, &messageError);

		if (exit != SQLITE_OK) {
			cerr << "Erro na criacao de tabelas: " << messageError;
			sqlite3_free(messageError);
		}
		else
			cout << "Tabelas criadas com sucesso." << std::endl;

		sqlite3_close(database);
	}
	catch (const std::exception& e) {
		cerr << "Erro na criacao de tabelas: " << e.what();
	}

	return 0;
}

/**
 * @brief altera as colunas da tabela
 * @param databaseFileName nome do banco de dados
 */

static int alterTable(const char* databaseFileName)
{
	sqlite3* database;
	char* messageError;

	string sql = "ALTER TABLE VENDEDOR DROP COLUMN 'NICKNAME'";

    try {
        int exit = sqlite3_open(databaseFileName, &database);
        exit = sqlite3_exec(database, sql.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Erro na alteracao de tabela: " << messageError << std::endl;
            sqlite3_free(messageError);
        }
        else
	    	cout << "Tabela alterada com sucesso." << std::endl;

        sqlite3_close(database);
    } catch (const std::exception& e) {
        cerr << "Erro na alteracao de tabela: " << e.what();
    }

	return 0;
}

int main() {
    const char* dir = "../../database/database.db";

    createDB(dir);
    createTables(dir);
    // alterTable(dir);

    return 0;
}