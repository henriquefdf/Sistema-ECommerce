#include <cmath>
#include <limits>
#include "../src/uteis.cpp"
#include "../include/objects/Usuario.hpp"
#include "../include/objects/Vendedor.hpp"
#include "../include/objects/Comprador.hpp"
#include "../include/objects/Autenticacao.hpp"

void menuPrincipal();

/**
 * @brief Função que imprime String de apresentação do sistema
 */
void header() {
    cout << "____________________" << endl;
    cout << "Sistema de Ecommerce" << endl;
    cout << "____________________" << endl;
}

/**
 * @brief Acesso ao Menu de Usuário Comprador
 */
void menuComprador(){
    Comprador* compradorLogado = nullptr;
    string produto;
    vector<Produto*> produtosListados; 
    vector<Produto*> produtosSelecionados;

    try {
        double saldo = Autenticacao::usuarioLogado->getSaldo();
        if (saldo > 20) {
            cout << endl << GREEN "......................." << endl;
            cout << "Seu saldo é de " << round(saldo * 100.f) / 100.f  << " reais" << endl;
            cout << "......................." RESET << endl << endl;
        } else {
            cout << endl << RED"........................................................................" << endl;
            cout << " Atenção! Seu saldo é de " << round(saldo * 100.f) / 100.f << " reais, recomendamos adicionar valor ao saldo!" << endl;
            cout << "........................................................................" RESET << endl << endl;
        }

        compradorLogado = new Comprador(Autenticacao::usuarioLogado);

        compradorLogado->recuperarCarrinho(Autenticacao::carrinhoCompradorLogado);

        cout << opcoesMenu("opcoesComprador");  

        int opcao;

        for (;;) {
            if (cin >> opcao) {
                break;
            } else {
                cout << "Por favor, digite um número inteiro." << endl << CIANO "> " RESET;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        if (!(opcao >= 1 && opcao <= 10)) {
            throw std::invalid_argument("Opção inválida");
        }

        while(opcao >= 1 && opcao <= 10) {
            switch (opcao) {
                case 1:
                    compradorLogado->mostrarSaldo();
                    break;

                case 2: 
                    int valorSaldo;
                    cout << endl << CIANO "Informe o valor a ser adicionado ao seu saldo: " RESET;
                    for (;;) {
                        if (cin >> valorSaldo) {
                            break;
                        } else {
                            cout << "Por favor, digite um número." << endl << CIANO "> " RESET;
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                    }
                    compradorLogado->adicionarValorSaldo(valorSaldo);
                    break;
                
                case 3: 
                    cout << endl << CIANO "Informe o produto que deseja buscar: " RESET;
                    cin.ignore();
                    getline(cin, produto);
                    produtosListados = compradorLogado->procurarProdutos(produto);
                    compradorLogado->selecionarProdutos(produtosListados);
                    break;

                case 4: 
                    produtosListados = compradorLogado->listarProdutosDisponiveis();
                    compradorLogado->selecionarProdutos(produtosListados);
                    break;

                case 5: 
                    compradorLogado->finalizarCompra();
                    break;

                case 6: 
                    compradorLogado->esvaziarCarrinho();
                    break;

                case 7: 
                    compradorLogado->historicoComprador();
                    break;
                
                case 8:
                    compradorLogado->visualizarCarrinho();
                    break;

                case 9:
                    compradorLogado->visualizarCarrinho();
                    cout << endl << CIANO "Digite o ID do item a ser retirado > " RESET;
                    int idRemocao;
                    for (;;) {
                        if (cin >> idRemocao) {
                            break;
                        } else {
                            cout << "Por favor, digite um número inteiro." << endl << CIANO "> " RESET;
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                    }
                    compradorLogado->removerItemCarrinho(idRemocao);
                    break;
                
                case 10:
                    delete compradorLogado;        
                    Autenticacao::logout();
                    menuPrincipal(); 
                    break; 

                default:
                    break;
            }
            if (opcao == 10) {
               break;
            }
            cout << opcoesMenu("opcoesComprador");
            for (;;) {
                if (cin >> opcao) {
                    break;
                } else {
                    cout << "Por favor, digite um número inteiro." << endl << CIANO "> " RESET;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
        }
    } catch (std::exception &e) {
        Autenticacao::usuarioLogado = (Usuario*) compradorLogado;
        cout << endl << RED << e.what() << RESET << endl;
        Autenticacao::guardarCarrinho(compradorLogado->getCarrinhoCompras());
        menuComprador();
    }
}

/**
 * @brief Acesso ao Menu de Usuário Vendedor
 */
void menuVendedor(){
    Vendedor* vendedorLogado;
    
    try {
        vendedorLogado= new Vendedor(Autenticacao::usuarioLogado);

        double saldo = vendedorLogado->getSaldo();
        if (saldo > 0) {
            cout << endl << GREEN "......................." << endl;
            cout << "Você já vendeu " << round(saldo * 100.f) / 100.f  << " reais" << endl;
            cout << "......................." RESET << endl << endl;
        } else {
            cout << endl << RED "........................................." << endl;
            cout << "Atenção! Você ainda não realizou vendas !" << endl;
            cout << "........................................." RESET << endl << endl;
        }

        std::cout << opcoesMenu("opcoesVendedor");

        int opcao;

        for (;;) {
            if (cin >> opcao) {
                break;
            } else {
                cout << "Por favor, digite um número inteiro." << endl << CIANO "> " RESET;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        if (!(opcao >= 1 && opcao <= 7)) {
            throw std::invalid_argument("Opção inválida");
        }
        
        while(opcao >= 1 && opcao <= 7){
            
            switch (opcao) {
            
                case 1:
                    vendedorLogado->visualizarEstoque();
                    break;

                case 2: 
                    vendedorLogado->listarHistoricoVendas();
                    break;
                
                case 3: 
                    vendedorLogado->verificarSaldo();
                    break;

                case 4: 
                    int idProdutoAlterar;
                    cout << endl << "Escolha um dos itens para alterar e copie seu id:" << endl; 
                    vendedorLogado->visualizarEstoque();
                    cout << endl << CIANO "Qual o id do produto que você deseja alterar? > " RESET;
                    for (;;) {
                        if (cin >> idProdutoAlterar) {
                            break;
                        } else {
                            cout << "Por favor, digite um número inteiro." << endl << CIANO "> " RESET;
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                    }
                    vendedorLogado->alterarInformacoesProduto(idProdutoAlterar);
                    break;

                case 5: 
                    vendedorLogado->adicionarProdutoEstoque();
                    break;

                case 6: 
                    int idProdutoDeletar;
                    cout << endl << "Escolha um dos itens para deletar e copie seu id:" << endl; 
                    vendedorLogado->visualizarEstoque();
                    cout << endl << CIANO "Qual o id do produto que você deseja deletar? > " RESET ;
                    for (;;) {
                        if (cin >> idProdutoDeletar) {
                            break;
                        } else {
                            cout << "Por favor, digite um número inteiro." << endl << CIANO "> " RESET;
                            cin.clear();
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                    }
                    vendedorLogado->deletarItem(idProdutoDeletar);
                    break;
                
                case 7:
                    delete vendedorLogado;        
                    Autenticacao::logout();
                    menuPrincipal(); 

                default:
                    break;
            }
            if (opcao == 7) {
                break;
            }
            cout << opcoesMenu("opcoesVendedor");
            for (;;) {
                if (cin >> opcao) {
                    break;
                } else {
                    cout << "Por favor, digite um número inteiro." << endl << CIANO "> " RESET;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
        }
    } catch (std::exception &e) {
        Autenticacao::usuarioLogado = (Usuario*) vendedorLogado;
        cout << endl << RED << e.what() << RESET << endl;
        menuVendedor();
    }
}

/**
 * @brief Acesso ao Menu de login do Sistema
 */
void loginMenu(){

    string nomeLogin;
    string senha;

    cout << endl << "Para fazer seu login, informe seus dados. Caso queira cancelar e voltar ao menu principal, digite 'm'." << endl;
    
    try {
        cout << CIANO "Nome de usuário: > " RESET;
        cin >> nomeLogin;

        if (nomeLogin == "m" || nomeLogin == "M") {
            menuPrincipal();
        }
        
        cout << CIANO "Senha: > " RESET; 
        cin >> senha;

        Autenticacao::autenticar(nomeLogin, senha);

        std::cout << endl << GREEN "Bem vind@, " << Autenticacao::usuarioLogado->getNome() << ". Você foi autenticado(a) com sucesso" RESET << std::endl;

        if (Autenticacao::usuarioLogado->getTipo() == 'c') {
            menuComprador();
        } else {
            menuVendedor();
        }

    } catch(std::exception &e) {
        cout << endl << RED << e.what() << RESET << endl;
        cout << RED "Tente novamente" RESET << endl;
        loginMenu();
    }

}

/**
 * @brief Acesso ao Menu de Cadastro de novo Usuário
 */
void cadastroUsuario() {
    string nome;
    string login;
    string senha;
    string tipo;

    cout << endl << "Primeiramente, nos diga que tipo de cadastro você deseja fazer." << endl
    << "Digite 'c' para cadastrar um comprador ou 'v' para cadastrar um vendedor." << endl;

    cout << endl << CIANO "Tipo de cadastro: > " RESET;
    cin >> tipo;

    if(tipo.length()>1){
        cout << RED "tipo de cadastro inválido, tente novamente." RESET << endl;
        cadastroUsuario();    
    } else if (tipo[0] == 'c' || tipo[0] == 'C') {
        cout << endl << "Olá comprador(a)!" << endl;
    } else if (tipo[0] == 'v' || tipo[0] == 'V') {
        cout << endl << "Olá vendedor(a)!" << endl;
    } else {
        cout << RED "tipo de cadastro inválido, tente novamente." RESET << endl;
        cadastroUsuario();
    }

    cout << "Para fazer seu cadastro, informe:" << endl;
    cout << CIANO "Seu nome completo: (se quiser voltar ao menu principal, digite '1') > " RESET;

    cin.ignore();
    getline(cin, nome);
    
    if (nome == "1") {
        menuPrincipal();
    }

    cout << CIANO "Login que você deseja usar (email ou nome de usuário): > " RESET;
    cin >> login;

    cout << CIANO "Nova senha: > " RESET ;
    cin >> senha;

    int retornoCadastro = Usuario::cadastrarUsuario(nome, login, senha, tipo[0]);

    if (retornoCadastro != 0 && retornoCadastro != 2) {
        Autenticacao::autenticar(login, senha);
        cout << endl << GREEN "Cadastro realizado com sucesso! Você será redirecionado para o sistema imediatamente" RESET << endl << endl;

        std::cout << endl << GREEN "Bem vind@, " << Autenticacao::usuarioLogado->getNome() << ". Você foi autenticado(a) com sucesso" RESET << std::endl;

        if (Autenticacao::usuarioLogado->getTipo() == 'c') {
            menuComprador();
        } else {
            menuVendedor();
        }
    } else {
        if (retornoCadastro == 2) {
            cout << endl << RED "Ops... parece que ja existe um usuário com esse login. Por favor, insira outro login." RESET << endl << endl;
            cadastroUsuario();
        } else {
            cout << endl << RED "Ops... houve uma falha ao realizar seu cadastro. Por favor, tente novamente." RESET << endl << endl;
            cadastroUsuario();
        }
    }
}

/**
 * @brief Menu principal do programa, leva a todas as funções do sistema
 */
void menuPrincipal(){
    int opcao;

    cout << GREEN "______________________________________" << endl << endl
    << "Seja bem vind@ ao Sistema de E-commerce" << endl
    << "______________________________________" RESET <<endl
    << endl << CIANO "O que deseja Fazer? Digite o número correspondente à alternativa desejada. " RESET << endl;

    try {
        cout << opcoesMenu("menuPrincipalOpcoes");

        for (;;) {
            if (cin >> opcao) {
                break;
            } else {
                cout << "Por favor, digite um número inteiro." << endl << CIANO "> " RESET;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        if (opcao != 1 && opcao != 2 && opcao != 3) {
            cout << endl << RED "Opção inválida, tente novamente." RESET <<endl;
            menuPrincipal();
        }
        
        switch (opcao) {
            case 1:
                loginMenu();
                break;
            case 2:
                cout << endl << "Vamos cadastrar um novo usuário para você em nosso sistema, preencha os dados conforme solicitado." << endl;
                cadastroUsuario();
                break;
            case 3:
                cout << endl << GREEN "Volte Sempre!" RESET << endl;
                exit(0);
                break;

            default:
                break;
        }
    } catch(std::exception &e) {
        std::cout << RED << e.what() << RESET << std::endl;
    }

}
