#ifndef SERVICOVENDEDOR_HPP
#define SERVICOVENDEDOR_HPP

#include <sqlite3.h>
#include <iostream>
#include <map>
#include <vector>

class ServicoVendedor {
    public:
        static int criar(int id);
        static int deletar(int id);
        static int atualizarSaldo(int id, double saldoAdicionar);
};

#endif