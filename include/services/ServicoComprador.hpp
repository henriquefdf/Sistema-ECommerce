#ifndef SERVICOCOMPRADOR_HPP
#define SERVICOCOMPRADOR_HPP

#include <sqlite3.h>
#include <iostream>
#include <map>
#include <vector>

class ServicoComprador {
    public:
        static int criar(int id);
        static int deletar(int id);
        static int atualizarSaldo(int id, double saldoAtualizado);
};

#endif