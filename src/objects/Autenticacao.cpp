#include "../../include/objects/Autenticacao.hpp"

bool Autenticacao::_autenticado = false;
Usuario* Autenticacao::usuarioLogado = nullptr;
multimap<Produto*, double> Autenticacao::carrinhoCompradorLogado = {};

/**
 * @brief Método para autenticar o login do usuário
 * @param loginUsuario Login do usuário
 * @param senha Senha do usuário
 * @return True se o usuário for autenticado com sucesso, False caso contrário
 * @throws invalid_argument Se o login ou a senha estiverem vazios
 * @throws runtime_error Se o login ou a senha estiverem incorretos
*/
bool Autenticacao::autenticar(std::string loginUsuario, std::string senha){
    if (loginUsuario == "" || senha == "") {
        throw std::invalid_argument("Usuario e/ou senha NAO podem ser vazios!!!");
    }

    Usuario* aux = ServicoUsuario::getUsuario(loginUsuario);//testando se o nome do usuário existe no banco de dados

    if(aux == nullptr) {
        throw std::runtime_error("Usuario nao encontrado no nosso sistema");
    }
    
    if (senha == aux->getSenha()){
        usuarioLogado = aux;
        _autenticado = true;
        return true;
    } else {
        throw std::runtime_error("Senha incorreta");
        return false;
    }
    return false;
}

/**
 * @brief Método para verificar se há algum usuário autenticado
 * @return True se houver um usuário autenticado, False caso contrário
*/
bool Autenticacao::getAutenticado(){
    return _autenticado;
}

/**
 * @brief Método para efetuar o logout do usuário
*/ 
void Autenticacao::logout() {
    _autenticado = false;
    usuarioLogado = nullptr;
    carrinhoCompradorLogado.clear();

    std::cout<<"Você efetuou logout com sucesso"<<std::endl;
}

/**
 * @brief Destrutor da classe Autenticacao
*/ 
Autenticacao::~Autenticacao(){
    delete usuarioLogado;
}

/**
 * @brief Método para salvar o carrinho do usuário logado após acontecer uma exceção
*/
void Autenticacao::guardarCarrinho(multimap<Produto*, double> carrinho) {
    carrinhoCompradorLogado = carrinho;
}
