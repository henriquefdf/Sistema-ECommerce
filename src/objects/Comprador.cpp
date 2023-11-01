#include "../../include/objects/Comprador.hpp"

using std::runtime_error;

/**
 * @brief Construtor padrão classe Comprador
 */
Comprador::Comprador() {}

/**
 * @brief Construtor de cópia que recebe Usuário da classe Comprador
 * @param usuario Usuário logado a ser copiado
*/
Comprador::Comprador(Usuario* usuario) : Usuario(usuario) {}

/**
 * @brief Destrutor da classe Comprador
 */
Comprador::~Comprador() {}

/**
 * @brief Método que mostra o saldo do comprador
 */
void Comprador::mostrarSaldo() {
    if(this->_saldo < 10){
        
        cout << endl << RED ".............................................................." << endl;
        cout << "Seu saldo é de " << round(_saldo * 100.f) / 100.f << " reais. Recomendados adicionar valor ao saldo!" << endl;
        cout << ".............................................................." RESET << endl << endl;
    }
    else{
        cout << endl <<  GREEN"......................................" <<endl;
        cout << "Seu saldo é de " << round(_saldo * 100.f) / 100.f << " reais. Boas compras!" << endl;
        cout << "......................................" RESET << endl << endl;
    }
}

/**
 * @brief Método que adiciona o valor informado ao saldo do comprador
 * @param valor Valor a ser adicionado ao saldo
 * @throws runtime_error se o valor informado for menor que 0
 */
void Comprador::adicionarValorSaldo(double valor) {
    if (valor < 0) {
        throw runtime_error("Adicione um valor maior que 0!");
    }

    string tipoPagamento = escolherFormaPagamento();

    this->_saldo = this->_saldo + valor;
    ServicoComprador::atualizarSaldo(this->_ID, this->_saldo);

    cout << endl << GREEN "Valor adicionado ao saldo com sucesso, na forma de pagamento " << tipoPagamento << "!" RESET << endl;
    cout << endl << GREEN ".............." << endl;
    cout << "Novo saldo: " << this->_saldo << endl;   
    cout << ".............." RESET << endl << endl;
}

/**
 * @brief Método que adiciona produtos e sua quantidade ao carrinho
 */
void Comprador::adicionarAoCarrinho(Produto* produtoComprado, double quantidade) {
    carrinhoCompras.insert({produtoComprado, quantidade});
}

/**
 * @brief Método que esvazia o carrinho
 * @throws runtime_error Se o carrinho estiver vazio
 */
void Comprador::esvaziarCarrinho() {
    if (carrinhoCompras.size() == 0) {
        throw runtime_error("Carrinho já está vazio!");
    }
    carrinhoCompras.clear();
    cout << GREEN "Carrinho esvaziado com sucesso!" RESET << endl << endl;
}

/**
 * @brief Método que procura um produto no estoque da loja
 * @param produto Nome do produto a ser procurado
 * @return vector<Produto*> vector de produtos encontrados 
 */
vector<Produto*> Comprador::procurarProdutos(string produto) {
    vector<Produto*> produtos = ServicoEstoque::selecionarProdutosEspecificos(produto);
    if (produtos.size() == 0) {
        cout << endl << RED "Nenhum produto com este nome está à venda. Tente outro ou liste os produtos disponíveis." RESET << endl;
    } else {
        cout << endl << "Produtos encontrados: " << endl;
        for (auto produto : produtos) {
            produto->imprimir();
        }
    }
    cout << endl;    
    return produtos;
} 

/**
 * @brief Método que lista todos os produtos disponíveis em estoque
 * @return vector<Produto*> vector de produtos disponíveis em estoque 
 */
vector<Produto*> Comprador::listarProdutosDisponiveis(){
   vector<Produto*> produtos = ServicoEstoque::listarTodosProdutos();
   cout << endl;
   for (auto produto : produtos) {
        if (produto->getQuantidade() == 0) {
            cout <<  RED "Produto em falta no estoque: " RESET;
        }
        produto->imprimir();
    }

    cout << endl;    
    return produtos;
}

/**
 * @brief Método que define quantidade e ID do produto a ser adicionado no carrinho
 * @param produtosListados vector com os produtos disponiveis
 */
void Comprador::selecionarProdutos(vector<Produto*> produtosListados) {
    if(produtosListados.size() == 0) {
        throw runtime_error("Não há produtos disponíveis para selecionar!");
    }

    cout << endl << "Caso deseje adicionar produtos ao carrinho, digite o ID. Caso deseje cancelar ou finalizar a seleção, digite -1" << endl;
    int id;
    cout << endl << CIANO "Informe o ID do produto desejado (Digite -1 para cancelar): > " RESET;
    for (;;) {
        if (cin >> id) {
            break;
        } else {
            cout << "Por favor, digite um número." << endl << CIANO "> " RESET;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    
    while (id != -1) {
        bool encontrado = false;
        double quantidadeDesejada; 
        double quantidadeProdutoCarrinho;
        double quantidadeTotal;
        bool quantidadeValida = false;
        for (auto produto : produtosListados) {
            
            if (produto->getID() == id) {
                encontrado = true;

                cout << CIANO "Quantidade desejada: > " RESET;
                for (;;) {
                    if (cin >> quantidadeDesejada) {
                        break;
                    } else {
                        cout << "Por favor, digite um número." << endl << CIANO "> " RESET;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }

                quantidadeProdutoCarrinho = verificarQuantidadeProdutoCarrinho(id); 
                quantidadeTotal = quantidadeProdutoCarrinho + quantidadeDesejada;

                if (quantidadeDesejada > 0 && (quantidadeTotal <= (produto->getQuantidade()))) {
                    quantidadeValida = true;
                    this->adicionarAoCarrinho(produto, quantidadeDesejada);
                }
                break;
            }
        }

        if (!encontrado) {
            cout << endl << RED "ID não encontrado. Tente outro, ou finalize a seleção digitando -1." RESET << endl;
        }

        if (!quantidadeValida) {
            cout << endl << RED "Quantidade inválida. Digite uma quantidade maior que 0 e menor/igual à quantidade de produtos em estoque." RESET << endl;
        }

        cout << endl << CIANO "Informe o ID do produto desejado (Digite -1 para cancelar): > " RESET;
        for (;;) {
            if (cin >> id) {
                break;
            } else {
                cout << "Por favor, digite um número." << endl << CIANO "> " RESET;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }

    if (carrinhoCompras.size() > 0) {
        cout << endl << GREEN "Produtos adicionados ao carrinho. Para finalizar a compra e realizar o pagamento, ou caso desejar adicionar mais produtos no carrinho, acesse o menu nas opções correspondentes." RESET << endl << endl;
    } else {
        cout << endl << RED "Nenhum produto adicionado ao carrinho. Caso desejar adicionar produtos no carrinho, acesse o menu nas opções correspondentes." RESET << endl << endl;
    }
 }

/**
 * @brief Método que retorna quantidade produtos no carrinho
 * @param idProduto id do produto a ter quantidade verificada no carrinho
 * @return quantidade produto passado como parametro
 */
 double Comprador::verificarQuantidadeProdutoCarrinho(int idProduto) {
    double qtdeProdCarrinho = 0;
    for (auto itemCarrinho : carrinhoCompras) {
        if (itemCarrinho.first->getID() == idProduto) {
            qtdeProdCarrinho += itemCarrinho.second;
        }
    }

    return qtdeProdCarrinho;
 }

/**
 * @brief Método que mostra o historico de compras do comprador
 * @throws runtime_error se nenhuma compra foi realizada por este comprador
 */
void Comprador::historicoComprador() {
    vector<Transacao*> transacoes;
    transacoes = ServicoTransacoes::selecionarTransacoes(_ID, 'c');

    if(transacoes.size() == 0) {
        throw runtime_error("Nenhuma compra encontrada");
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
 * @brief Método que remove um item do carrinho
 * @param idRemocao id do produto a ser removido
 * @throws runtime_error exceção caso produto não encontrado carrinho
 */
void Comprador::removerItemCarrinho(int idRemocao) {
    for (auto produto : carrinhoCompras) {
        if (produto.first->getID() == idRemocao) {
            cout << endl << GREEN "Produto " << produto.first->getNome() << " removido com sucesso!" RESET << endl << endl;
            carrinhoCompras.erase(produto.first);
            break;
        } else {
            throw runtime_error("Produto não encontrado no carrinho");
        }
    } 

    cout << "Seu saldo atual é de: " << _saldo; 
    cout << "Preço Total do Carrinho: " << ServicoTransacoes::calcularValorTotalCompra(carrinhoCompras) << endl;
}

/**
 * @brief Método para finalizo compra deduzindo saldo comprador e verificando se existe produto no carrinho
 * @throws runtime_error excecao caso carrinho vazio
 * @return retorna int 0 caso sucesso, 1 caso erro de saldo e 2 caso desejado voltar ao menu
 */
int Comprador::finalizarCompra() {
    if (carrinhoCompras.size() == 0) {
        throw runtime_error("Nenhum produto no carrinho. Adicione produtos ao carrinho para depois finalizar a compra. Obrigado!");
    } 

    visualizarCarrinho();

    double valorTotal = ServicoTransacoes::calcularValorTotalCompra(carrinhoCompras);
    cout << endl << "Valor total da compra: " << valorTotal << endl;

    int opcao;
    cout << endl << CIANO "Você deseja:" RESET << endl;
    cout << "1 - Finalizar a compra" << endl;
    cout << "2 - Voltar ao menu" << endl << CIANO "> " RESET;
    for (;;) {
        if (cin >> opcao) {
            break;
        } else {
            cout << "Por favor, digite um número (1 ou 2)." << endl << CIANO "> " RESET;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    if (opcao == 1) {
        if (_saldo >= valorTotal){
            ServicoTransacoes::efetuarCompra(this->_ID, carrinhoCompras, valorTotal, "Saldo da conta", _saldo);

            this->_saldo = this->_saldo - valorTotal;
            ServicoComprador::atualizarSaldo(this->_ID, this->_saldo);

            this->esvaziarCarrinho();
                
            cout << endl << GREEN "Compra concluída com sucesso. Obrigado por comprar no nosso sistema! Você será redirecionado(a) ao menu inicial." RESET << endl << endl;
            
            return 0;
        } else {
            cout << endl << RED "Você não tem saldo suficiente para realizar esta compra! Você tem duas opções: " RESET << endl 
            << "--> Adicione valor ao seu saldo e depois finalize a compra. Seus produtos ainda estão no carrinho. " << endl 
            << "--> Esvazie itens do seu carrinho para poder comprar com o saldo atual\n" << endl;
            return 1;
        }
        
    } else {
        cout << endl << RED "Compra não concluída. Seus produtos ainda estão no carrinho." RESET << endl << endl;
        return 2;
    }
}

/**
 * @brief Método para que o comprador selecione a forma de pagamento para adicionar valor ao saldo
 * @return Retorna string com metodo de pagamento escolhido
*/
string Comprador::escolherFormaPagamento() {
    string tipoPagamento[5] = {"Pix", "Boleto", "Cartão de crétido", "Cartão de débito", "Cancelar"};
    int escolhaTipoPgto = 0;
    while (escolhaTipoPgto != 1 && escolhaTipoPgto != 2 && escolhaTipoPgto != 3 && escolhaTipoPgto != 4 && escolhaTipoPgto != 5) {
        cout << endl << CIANO "Qual a forma de pagamento: > " RESET << endl;
        for (int i = 0; i < 4; i++) {
            cout << (i + 1) << " - " << tipoPagamento[i] << endl;
        }
        cout << "> ";
        for (;;) {
            if (cin >> escolhaTipoPgto) {
                break;
            } else {
                cout << "Por favor, digite um número entre de 1 a 5." << endl << CIANO "> " RESET;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }  
    }

    if (escolhaTipoPgto == 5) {
        return "";
    } else {
        return tipoPagamento[escolhaTipoPgto - 1];
    }
}

/**
 * @brief Metodo que percorre e imprime carrinho de compras
 * @throws runtime_error excecao caso carrinho vazio
 */
void Comprador::visualizarCarrinho() {
    if (carrinhoCompras.size() == 0) {
        throw runtime_error("O seu carrinho de compras está vazio.");
    }
    cout << endl;
    for (auto itemCarrinho : carrinhoCompras) {
        itemCarrinho.first->imprimir();
        cout << "Quantidade: " << itemCarrinho.second << endl;
        cout << endl; 
    }
    cout << "Preço Total do carrinho: " << ServicoTransacoes::calcularValorTotalCompra(carrinhoCompras) << endl << endl ;
}

/**
 * @brief Metodo que retorna o carrinho de compras para ser salvo quando uma exceção é lançada
 */
multimap<Produto*, double> Comprador::getCarrinhoCompras() {
    return carrinhoCompras;
}

/**
 * @brief Metodo que recupera o carrinho de compras apos uma exceção
*/
void Comprador::recuperarCarrinho(multimap<Produto*, double> carrinho) {
    carrinhoCompras = carrinho;
}