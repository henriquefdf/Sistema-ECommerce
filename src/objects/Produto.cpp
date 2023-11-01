#include "../../include/objects/Produto.hpp"

/**
 * @brief Construtor da classe Produto
 * @param ID ID do produto
 * @param idVendedor ID do vendedor do produto
 * @param nome Nome do produto
 * @param quantidade Quantidade do produto em estoque
 * @param preco Preço do produto
 * @param unidadeMedida Unidade de medida do produto (unidade, kg, litro, etc)
 * @param descricao Descrição do produto
*/
Produto::Produto(int ID, int idVendedor, std::string nome, double quantidade, double preco, std::string unidadeMedida, std::string descricao) {
    _ID = ID;
    _idVendedor = idVendedor;
    _nome = nome;
    _unidadeMedida = unidadeMedida;
    _quantidade = quantidade;
    _preco = preco;
    _descricao = descricao;
}

/**
 * @brief Destrutor da classe Produto
 */
Produto::~Produto() {}

/**
 * @brief Método para alterar o nome do produto
 * @param nome Novo nome do produto
*/
void Produto::setNome(std::string nome) {
    _nome = nome;
}

/**
 * @brief Método para alterar a quantidade do produto em estoque
 * @param quantidade Nova quantidade do produto em estoque
*/
void Produto::setQuantidade(double quantidade) {
    _quantidade = quantidade;
}

/**
 * @brief Método para alterar o preço do produto
 * @param preco Novo preço do produto
*/
void Produto::setPreco(double preco) {
    _preco = preco;
}

/**
 * @brief Método para alterar a unidade de medida do produto
 * @param unidadeMedida Nova unidade de medida do produto
*/
void Produto::setUnidadeMedida(std::string unidadeMedida) {
    _unidadeMedida = unidadeMedida;
}

/**
 * @brief Método para alterar a descrição do produto
 * @param descricao Nova descrição do produto
*/
void Produto::setDescricao(std::string descricao) {
    _descricao = descricao;
}

/**
 * @brief Método para obter o ID do produto
 * @return ID do produto
*/
int Produto::getID() {
    return _ID;
}

/**
 * @brief Método para obter o ID do vendedor do produto
 * @return ID do vendedor do produto
*/
int Produto::getIdVendedor() {
    return _idVendedor;
}

/**
 * @brief Método para obter o nome do produto
 * @return Nome do produto
*/
std::string Produto::getNome() {
    return _nome;
}

/**
 * @brief Método para obter a quantidade do produto em estoque
 * @return Quantidade do produto em estoque
*/
double Produto::getQuantidade() {
    return _quantidade;
}

/**
 * @brief Método para obter o preço do produto
 * @return Preço do produto
*/
double Produto::getPreco() {
    return _preco;
}

/**
 * @brief Método para obter a unidade de medida do produto
 * @return Unidade de medida do produto
*/
std::string Produto::getUnidadeMedida() {
    return _unidadeMedida;
}

/**
 * @brief Método para obter a descrição do produto
 * @return Descrição do produto
*/
std::string Produto::getDescricao() {
    return _descricao;
}

/**
 * @brief Método para imprimir as informações do produto
*/
void Produto::imprimir() {
    std::cout << "ID: " << this->getID() << ", "
        << " Nome: " << this->getNome() << ", "
        << " Preço: " << this->getPreco() << ", "
        << " Quantidade em estoque: " << this->getQuantidade() << " "
        << this->getUnidadeMedida() << ", " << " Descrição: "
        << this->getDescricao() << std::endl;
}