# 2022-1-TN-grupo03
Arquivo de leitura do trabalho prático de PDSII

### Apresentação do Sistema:

   De maneira geral, foi feito um Sistema de E-commerce baseado nas ações de dois tipos de Usuário, Comprador e Vendedor. Dessa forma, é possível fazer tanto ações relacionadas a operações com os produtos (compra, venda, alteração ...) quanto  controle financeiro e logístico (visualizar histórico de compras e vendas, conferir estoque, adicionar saldo ...).

   O sistema gira em torno das classes principais Usuário, Comprador, Vendedor, Autenticação, Produto e Transações. A organização do estoque está salva em um banco de dados utilizando o SQLite 3. Para fazer as ações de Escrita, Leitura, Atualização e Deleção no banco de dados, são utilizadas as classes auxiliares Serviços + (nome da respectiva classe) que são chamadas para realizar essas ações nas classes em que fazem referência. Essa decisão foi motivada principalmente para melhorar a abstração das funções das classes principais, que devem executar as ações de suas responsabiliades, deixando o controle do banco para tais classes serviços.

   Neste repositório encontra-se a pasta ***Modelagem*** contendo os arquivos de análises de requisitos do sistema a ser desenvolvido. Nele estão contidos dois arquivos, um referente aos cartões CRC e outro às User Stories. Na pasta ***include*** encontram-se os arquivos de cabeçalho (hpp) das classes utilizdas. Em ***lib*** estão arquivos da biblioteca do SQLite, do doctest e das cores usadas na saida do terminal. Em ***src*** estão a main, arquivos auxiliares e as implementações das classes (cpp). Por fim, em **tests** estão os arquivos de testes de unidade do sistema.

   As pastas ***include***, ***src*** e ***tests*** são divididas em 2 outros diretórios, ***objects*** e ***services***, que contém, respectivamente, as classes principais (Usuário, Comprador, Vendedor, Autenticação, Produto, Transação), e as classes auxiliares/serviços (conectam diretamente ao banco de dados).
    
   As principais dificulades encontradas dizem respeito a utilização do SQLite, que é uma tecnologia nova para a maior parte do grupo, além do Makefile. Aprofundando a discussão no Makefile, a adição de várias flags de compilação, adição dos testes, compilação do banco de dados e utilização em diferentes sistemas operacionais foram um dos desafios para o grupo. 


### Preparação do ambiente:

É necessário a criação da pasta ***build*** na raiz da pasta em que foi feito o clone para fazer a compilação.

Siga o link abaixo para realizar a instalação do SQLite 3 (utilizado para gerenciar o banco de dados) 
- [https://www.servermania.com/kb/articles/install-sqlite/](https://www.servermania.com/kb/articles/install-sqlite/)

Instalação de dependências linux: 
- sudo apt-get install libpthread-stubs0-dev (Dividir a aplicação em tarefas - threads- que acessam recursos compartilhados)

### Compilação:

Basta usar o comando ***make*** no terminal que será iniciado a compilação e ligação dos arquivos utilizados. Após isso, com o comando ***make run*** é possível iniciar o sistema.
Outros comandos do make:
- ***make project*** = faz a compilação dos objetos utilizados, com exceção do banco de dados
- ***make clean*** = limpa os arquivos de ligação .o que foram criados.

### Testes e Cobertura

Para rodar os testes e conferir a cobertura de código, é necessário instalar a ferramenta ***gcovr***, no linux ou no windows, e segue o passo a passo:

- Linux: sudo apt install gcovr
- Windows: [https://gcovr.com/en/stable/installation.html](https://gcovr.com/en/stable/installation.html)
    - no windows gcovr é instalado com o sistema de gerenciamento de pacotes pip, que pode ser encontrado aqui: [https://pip.pypa.io/en/stable/installation/](https://pip.pypa.io/en/stable/installation/). Pip por sua vez é instalado através do python, que pode ser encontrado aqui: [https://www.python.org/downloads/](https://www.python.org/downloads/)

Após baixar essa ferramenta, siga:

É necessário a criação da pasta ***build_tests*** na pasta raiz, para armazenar os arquivos *.o dos testes.

Para rodar os testes é necessário rodar ***make tests***, que assim os testes serão compilados. Em seguida, rode ***./testes***, e os testes serão executados.

A maneira que encontramos de testar algumas funcionalidades, como a seleção de produtos, foi pedindo para o usuário/testador inserir dados. Especificamente essa inserção acontece 4 vezes: selecionar forma de pagamento, selecionar ID do produto para ser adicionado ao carrinho, e 2 testes de finalização de compra. Podem ser inseridos quaisquer valores nesses testes, mas, para faciliar, recomendamos os valores *1, -1, 1 e 1*, nesta ordem. No caso da seleção de produtos, quanto mais operações forem feitas, maior será a cobertura.

Outra observação em relação aos testes, é que não colocamos a flag de cobertura de testes (*--coverage*) nos arquivos *main.cpp* e *menu.cpp*. Isso se deve porque são arquivos que contém funções que chamam outras, já testadas, então não foram incluídos na avaliação de cobertura.

Para conferir a cobertura de código em cada classe rode o comando ***gcovr -r . --html --html-details -o relatorio.html***

Assim vários relatórios ***.html*** serão criados na raíz do projeto, informando sobre a cobertura do código de cada classe, e a cobertura de código geral.
