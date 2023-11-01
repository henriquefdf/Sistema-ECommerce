#include "../../include/objects/Usuario.hpp"


/**
 * @brief Construtor da classe Usuario
 * @param login Login do usuário
 * @param senha Senha do usuário
 * @param nome Nome do usuário
 * @param tipo Tipo do usuário (vendedor ou comprador)
*/ 
Usuario::Usuario(std::string login, std::string senha, std::string nome, char tipo){
    this->_login = login;
    this->_senha = senha;
    this->_nome = nome;
    this->_tipo = tipo;
}

/**
 * @brief Construtor padrão da classe Usuário
*/
Usuario::Usuario() {};

/**
 * @brief Construtor de cópia da classe Usuário
 * @param usuario Usuário a ser copiado
*/
Usuario::Usuario(Usuario* usuario){
    this->_login = usuario->_login;
    this->_senha = usuario->_senha;
    this->_nome = usuario->_nome;
    this->_tipo = usuario->_tipo;
    this->_ID = usuario->getID();
    this->_saldo = usuario->getSaldo();
}

/**
 * @brief Destrutor da classe Usuário
*/
Usuario::~Usuario() {}

/**
 * @brief Método para obter o login do usuário
 * @return Login do usuário
*/
std::string Usuario::getLogin(){
    return this->_login;
}

/**
 * @brief Método para obter a senha do usuário
 * @return Senha do usuário
*/
std::string Usuario::getSenha(){
    return this->_senha;
}

/**
 * @brief Método para obter o nome do usuário
 * @return Nome do usuário
*/
std::string Usuario::getNome(){ 
    return this->_nome;
}

/**
 * @brief Método para obter o tipo do usuário
 * @return Tipo do usuário -> 'v' de vendedor ou 'c' de comprador
*/
char Usuario::getTipo(){
    return this->_tipo;
}

/**
 * @brief Método para obter o ID do usuário
 * @return ID do usuário
*/
int Usuario::getID(){
    return this->_ID;
}

/**
 * @brief Método para obter o saldo do usuário
 * @return Saldo do usuário
*/
double Usuario::getSaldo(){
    return this->_saldo;
}

/**
 * @brief Método para definir o login do usuário
 * @param login Login do usuário
*/
void Usuario::setLogin(std::string login){
    this->_login = login;
}

/**
 * @brief Método para definir a senha do usuário
 * @param senha Senha do usuário
*/
void Usuario::setSenha(std::string senha){
    this->_senha = senha;
}

/**
 * @brief Método para definir o nome do usuário
 * @param nome Nome do usuário
*/
void Usuario::setNome(std::string nome){
    this->_nome = nome;
}

/**
 * @brief Método para definir o tipo do usuário
 * @param tipo Tipo do usuário -> 'v' de vendedor ou 'c' de comprador
*/
void Usuario::setTipo(char tipo){
    this->_tipo = tipo;
}

/**
 * @brief Método para definir o ID do usuário
 * @param ID ID do usuário
*/
void Usuario::setID(int id){
    this->_ID = id;
}

/**
 * @brief Método para definir o saldo do usuário
 * @param saldo Saldo do usuário
*/
void Usuario::setSaldo(double saldo){   // deixar somente em vendedor ??
    this->_saldo = saldo;
}

/**
 * @brief Método para cadastrar um novo usuário no banco de dados
 * @param nome Nome do usuário
 * @param login Login do usuário
 * @param senha Senha do usuário
 * @param tipo Tipo do usuário -> 'v' de vendedor ou 'c' de comprador
 * @return Retorna o id do novo usuário caso a operação seja bem sucedida e 0 caso contrário
*/
int Usuario::cadastrarUsuario(std::string nome, std::string login, std::string senha, char tipo) {
    return ServicoUsuario::criar(nome, login, senha, tipo, 0);
}

