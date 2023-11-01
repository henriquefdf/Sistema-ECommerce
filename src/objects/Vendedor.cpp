#include "../../include/objects/Vendedor.hpp"

/**
 * @brief Construtor padrão da classe Vendedor
*/
Vendedor::Vendedor() {}

/**
 * @brief Construtor de cópia da classe Vendedor
 * @param usuário Usuário a ser copiado
 */
Vendedor::Vendedor(Usuario* usuario) : Usuario(usuario) {}

/**
 * @brief Destrutor da classe Vendedor
*/
Vendedor::~Vendedor() {}

/**
 * @brief Método para deletar um produto do estoque
*/
void Vendedor::deletarItem(int idProdutoDeletar){
    string nomeProdutoDeletar = ServicoProduto::buscarProduto(idProdutoDeletar);
    if (nomeProdutoDeletar != "") {
        ServicoProduto::deletar(idProdutoDeletar);
        ServicoEstoque::deletarProdutoEstoque(idProdutoDeletar);
        cout << endl << GREEN "Produto " + nomeProdutoDeletar + " deletado com sucesso!" RESET << endl << endl;
    } else {
        throw std::runtime_error("Produto não existe em seu estoque!");
    }
}

/**
 * @brief Método para alterar as informações de um produto no estoque
*/
void Vendedor::alterarInformacoesProduto(int idProdutoAlterar) {
    string nomeProdutoAlterar = ServicoProduto::buscarProduto(idProdutoAlterar);
    if (nomeProdutoAlterar != "") {
        cout << endl << "Digite as novas informações do produto. Caso alguma dessas informações você não deseje alterar, repita a informação." << endl;
        
        std::string nomeProd;
        double precoProd;
        std::string descricaoProd;
        double quantidadeProd;
        std::string unidadeMedidaProd;

        std::cout << endl << CIANO "Nome do produto: > " RESET;
        std::cin.ignore();
        getline(std::cin, nomeProd);

        std::cout << CIANO "Preço do produto: > " RESET;
        for (;;) {
            if (cin >> precoProd) {
                break;
            } else {
                cout << "Por favor, digite um número." << endl << CIANO "> " RESET;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        std::cout << CIANO "Descrição do produto: > " RESET;
        std::cin.ignore();
        getline(std::cin, descricaoProd);

        std::cout << CIANO "Quantidade do produto no estoque: > " RESET;
        for (;;) {
            if (cin >> quantidadeProd) {
                break;
            } else {
                cout << "Por favor, digite um número inteiro." << endl << CIANO "> " RESET;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        std::cout << CIANO "Medida da quantidade (kg, g, un, etc): > " RESET;
        std::cin >> unidadeMedidaProd;

        ServicoProduto::atualizar(idProdutoAlterar, nomeProd, precoProd, descricaoProd);
        ServicoEstoque::atualizar(idProdutoAlterar, this->getID(), quantidadeProd, unidadeMedidaProd);

        cout << endl << GREEN "Produto " + nomeProdutoAlterar + " alterado com sucesso!" RESET << endl << endl;
    } else {
        throw std::runtime_error("Produto não existe em seu estoque!");
    }
}

/**
 * @brief Método para visualizar o estoque do vendedor
*/
void Vendedor::visualizarEstoque() {
    vector<Produto*> estoqueVendedor = ServicoEstoque::selecionarProdutos(this->getID());

    if (estoqueVendedor.size() == 0) {
        throw std::length_error("Você não tem produtos em seu estoque! Use a opção de adicionar produtos ao estoque.");
    } else {
        cout << endl;
        for (auto produto : estoqueVendedor) {
            if (produto->getQuantidade() == 0) {
                cout <<  RED "Produto em falta no estoque: " RESET;
            }
            produto->imprimir();
        } 
    }

    for (auto produto : estoqueVendedor) {
        delete produto;
    } 

    cout << endl;
}

/**
 * @brief Método para listar o histórico de vendas do vendedor, a partir a tabela transação
*/
void Vendedor::listarHistoricoVendas() {
    vector<Transacao*> transacoes;
    transacoes = ServicoTransacoes::selecionarTransacoes(_ID, 'v');

    if(transacoes.size() == 0) {
        throw std::runtime_error("Nenhuma venda encontrada!");
    }

    for(auto transacao : transacoes){
        transacao->imprimir();
    }

    for(auto transacao : transacoes){
        delete transacao;
    }

    cout << endl;
}

/**
 * @brief Método para adicionar um produto ao estoque
*/ 
void Vendedor::adicionarProdutoEstoque() {
    std::string nomeProd;
    double precoProd;
    std::string descricaoProd;
    double quantidadeProd;
    std::string unidadeMedidaProd;

    std::cout << endl << "Para adicionar um produto ao estoque, informe: " << std::endl;
    std::cout << endl << CIANO "Nome do produto: > " RESET;
    std::cin.ignore();
    getline(std::cin, nomeProd);

    std::cout << CIANO "Preço do produto: > " RESET;
    for (;;) {
        if (cin >> precoProd) {
            break;
        } else {
            cout << "Por favor, digite um número." << endl << CIANO "> " RESET;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    if (precoProd < 0) {
        throw std::runtime_error("Preço do produto não pode ser negativo ou inválido!");
    }

    std::cout << CIANO "Descrição do produto: > " RESET;
    std::cin.ignore();
    getline(std::cin, descricaoProd);

    std::cout << CIANO "Quantidade do produto no estoque: > " RESET;
    for (;;) {
        if (cin >> quantidadeProd) {
            break;
        } else {
            cout << "Por favor, digite um número." << endl << CIANO "> " RESET;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    if (quantidadeProd < 0) {
        throw std::runtime_error("Quantidade do produto não pode ser negativa!");
    }

    std::cout << CIANO "Medida da quantidade (kg, g, un, etc): > " RESET;
    std::cin >> unidadeMedidaProd;

    int idProd = ServicoProduto::criar(nomeProd, precoProd, descricaoProd);
    ServicoEstoque::inserirProduto(idProd, this->getID(), quantidadeProd, unidadeMedidaProd);

    std::cout << endl << GREEN "Produto " + nomeProd + " adicionado com sucesso!" RESET << endl << endl;
}

/**
 * @brief Método para verificar o saldo do vendedor, obtido a partir das vendas
*/
void Vendedor::verificarSaldo(){
    if(this->_saldo == 0){
        cout << endl << RED "Você ainda não realizou nenhuma venda!" RESET << endl << endl;
    }
    else{
        cout << endl << "Você já vendeu " GREEN << round(_saldo * 100.f) / 100.f  << " reais" RESET << endl << endl;
    }
}