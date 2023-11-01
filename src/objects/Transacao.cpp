#include "../../include/objects/Transacao.hpp"

/**
 * @brief Construtor da classe Transacao
 * @param id Identificador da transacao
 * @param id_cliente Identificador do cliente que realizou a transacao
 * @param id_vendedor Identificador do vendedor que realizou a transacao
 * @param id_produto Identificador do produto que foi vendido
 * @param quantidade Quantidade do produto vendido
 * @param valor Valor da transacao
 */
Transacao::Transacao
    (int ID, int idComprador, int idVendedor, int idProduto, double qtdProduto, std::string data, double valorTotal, std::string tipoPagamento, std::string nomeComprador, std::string nomeVendedor, std::string nomeProduto) : 
    _ID(ID), _idComprador(idComprador), _idVendedor(idVendedor), _idProduto(idProduto), _qtdProduto(qtdProduto), _data(data), _valorTotal(valorTotal), _tipoPagamento(tipoPagamento), _nomeComprador(nomeComprador), _nomeVendedor(nomeVendedor), _nomeProduto(nomeProduto) {}

Transacao::~Transacao() {}

/**
 * @brief Imprime os dados completos da transacao
 */
void Transacao::imprimir() {
    std::cout << std::endl;
    
    std::cout << "Transacao " << _ID << std::endl;
    std::cout <<  "Nome Comprador: " << _nomeComprador << " - Nome Vendedor: " << _nomeVendedor << " - ID Produto: " << _idProduto << " - Quantidade: " << _qtdProduto << " - Data: " << _data << " - Valor Total: " << _valorTotal << " reais" << " - Tipo Pagamento: " << _tipoPagamento << " - Nome Produto: " << _nomeProduto << std::endl;
}

/**
 * @brief pega o identificador da transacao
 * 
 * @return int Identificador da transacao
 */ 
int Transacao::getID(){
    return this->_ID;
}
/**
 * @brief pega o identificador do cliente que realizou a transacao
 * 
 * @return o identificador do cliente que realizou a transacao
 */
int Transacao::getIdComprador(){
    return this->_idComprador;
}
/**
 * @brief pega o identificador do vendedor que realizou a transacao
 * 
 * @return o identificador do vendedor que realizou a transacao
 */ 
int Transacao::getIdVendedor(){
    return this->_idVendedor;
}
/**
 * @brief pega o identificador do produto que foi vendido
 * 
 * @return o identificador do produto que foi vendido
 */
int Transacao::getIdProduto(){
    return this->_idProduto;
}
/**
 * @brief pega a quantidade do produto vendido
 * 
 * @return double Quantidade do produto vendido
 */
double Transacao::getQtdProduto(){
    return this->_qtdProduto;
}
/**
 * @brief pega a data da transacao
 * 
 * @return  a data da transacao
 */
string Transacao::getData(){
    return this->_data;
}
/**
 * @brief pega o valor total da transacao
 * 
 * @return double Valor total da transacao
 */
double Transacao::getValorTotal(){
    return this->_valorTotal;
}
/**
 * @brief  pega o tipo de pagamento da transacao
 * 
 * @return  o tipo de pagamento da transacao
 */
string Transacao::getTipoPagamento(){
    return this->_tipoPagamento;
}
/**
 * @brief pega o nome do comprador da transacao
 * 
 * @return o nome do comprador da transacao
 */
string Transacao::getNomeComprador(){
    return this->_nomeComprador;
}
/**
 * @brief pega o nome do vendedor da transacao
 * 
 * @return o nome do vendedor da transacao
 */
string Transacao::getNomeVendedor(){
    return this->_nomeVendedor;
}
/**
 * @brief pega o nome do produto da transacao
 * 
 * @return o nome do produto da transacao
 */
string Transacao::getNomeProduto(){
    return this->_nomeProduto;
}

    

