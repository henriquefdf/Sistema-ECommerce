#include <iostream>
#include <sqlite3.h>

using std::string;
using std::cerr;
using std::cout;

static int deleteTransacoes(const char* databaseFileName)
{
	sqlite3* database;
	char* messageError;

	string sql = "DELETE FROM TRANSACAO";

    try {
        int exit = sqlite3_open(databaseFileName, &database);
        exit = sqlite3_exec(database, sql.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Erro ao deletar transacoes: " << messageError << std::endl;
            sqlite3_free(messageError);
        }
        else
	    	cout << "Transações deletadas." << std::endl;

        sqlite3_close(database);
    } catch (const std::exception& e) {
        cerr << "Erro ao deletar transacoes: " << e.what();
    }

	return 0;
}

int main() {
    const char* dir = "../../database/database.db";

    deleteTransacoes(dir);

    return 0;
}