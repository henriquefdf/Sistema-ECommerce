#include <iostream>
#include <sqlite3.h>

using std::cout;
using std::exception;
using std::cerr;
using std::endl;
using std::string;
using std::cin;

static sqlite3* abrirBanco() {
    sqlite3 *database;
    try {
        const char *databaseFileName = "database/database.db";
        int exit = sqlite3_open(databaseFileName, &database);
        if (exit != SQLITE_OK) {
            cout << exit << endl;
            cerr << "Erro em abrir o banco." << endl;
        }
        return database;
    } catch (exception &e) {
        cerr << "Erro na criação do banco: " << e.what() << endl;
    }
    return database;
}