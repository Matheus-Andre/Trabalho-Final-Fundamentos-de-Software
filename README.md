# Trabalho-Final-Fundamentos-de-Software
Nesse trabalho iremos desenvolver, documentar e implementar o trabalho da disciplina Algoritmos de programação e estrutura de dados, do professor Roberto. 

PONTIFÍCIA UNIVERSIDADE CATÓLICA DE MINAS GERAIS
INSTITUTO DE CIÊNCIAS EXATAS E INFORMÁTICA
UNIDADE EDUCACIONAL PRAÇA DA LIBERDADE
Bacharelado em Engenharia de Software




Integrantes: 
•	JORGE MATHEUS DA SILVA LOPES
•	MATHEUS ANDRÉ DE SOUZA BARBOSA
Sistema: LocaMais

LocaMais Sistema de Gestão de Locações de Veículos

Objetivo do Sistema:

Nosso sistema foi desenvolvido para simplificar e otimizar o processo de locação de veículos, oferecendo uma plataforma intuitiva e eficiente para clientes e para a gestão interna da locadora. Com uma gama de funcionalidades, o sistema visa facilitar desde a escolha do veículo até o gerenciamento de locações e clientes.

Vantagens e Recursos:

Facilidade na Localização de Veículos: Oferecemos uma maneira simples e rápida para os clientes encontrarem o veículo desejado, seja por código, descrição ou outros parâmetros.

Eficiência na Gestão de Locações: Com uma interface de administração completa, o sistema permite o cadastro e o gerenciamento ágil de locações, clientes e veículos.

Controle de Prazos e Entregas: A funcionalidade de verificar datas de entrega e prazos auxilia na organização das devoluções, evitando atrasos e garantindo um melhor planejamento.

Cálculo Preciso de Valores: O sistema realiza o cálculo automático do valor da locação, incluindo opções de seguro, facilitando a precificação para clientes e evitando erros de cobrança.

Registro de Histórico: Mantemos um registro detalhado das locações anteriores, facilitando consultas e oferecendo informações úteis para a fidelização de clientes.

Benefícios para Clientes Fieis: Oferecemos um programa de pontos de fidelidade, incentivando clientes frequentes e proporcionando descontos ou vantagens exclusivas.

Segurança e Organização: O sistema garante a integridade dos dados, com procedimentos para verificar a existência de clientes e veículos, mantendo um ambiente organizado.
Objetivo de Uso:

O sistema foi concebido para atender locadoras de todos os tamanhos, desde pequenas empresas até grandes redes. Facilitando tanto para o cliente final quanto para a equipe interna, o objetivo é tornar o processo de locação mais eficiente, transparente e agradável para ambas as partes.

Com uma abordagem centrada no cliente e na facilidade de uso para a equipe, nosso sistema promove a satisfação do cliente e a eficiência operacional, sendo uma solução completa para a gestão de locações de veículos.


Lista de assinaturas das funções e parâmetros:

**int compararDatas(const char data1, const char data2):

Propósito: Compara duas datas no formato dd/mm/aaaa.
Parâmetros:
data1: Ponteiro para a primeira data a ser comparada.
data2: Ponteiro para a segunda data a ser comparada.
*int obterDataEntrega(const char dataDevolucaoPrevista):

Propósito: Obtém a data de entrega e valida com a data de devolução prevista.
Parâmetros:
dataDevolucaoPrevista: Ponteiro para a data de devolução prevista.
*int veiculoDisponivel(FILE arquivoVeiculos, int codigoVeiculo):

Propósito: Verifica se um veículo está disponível.
Parâmetros:
arquivoVeiculos: Ponteiro para o arquivo de veículos.
codigoVeiculo: Código do veículo a ser verificado.
*float calcularValorLocacao(FILE arquivoVeiculos, int codigoVeiculo, int quantidadeDias, int contratarSeguro):

Propósito: Calcula o valor total da locação.
Parâmetros:
arquivoVeiculos: Ponteiro para o arquivo de veículos.
codigoVeiculo: Código do veículo para o cálculo.
quantidadeDias: Quantidade de dias para a locação.
contratarSeguro: Indicador se o seguro será contratado.
**int buscarCliente(FILE *arquivoClientes, const char nomeCliente, int codigoCliente):

Propósito: Busca um cliente pelo nome.
Parâmetros:
arquivoClientes: Ponteiro para o arquivo de clientes.
nomeCliente: Ponteiro para o nome do cliente a ser buscado.
codigoCliente: Ponteiro para o código do cliente encontrado.
*int clienteExiste(FILE arquivo, int codigo):

Propósito: Verifica se um cliente com o mesmo código já existe no arquivo.
Parâmetros:
arquivo: Ponteiro para o arquivo de clientes.
codigo: Código do cliente a ser verificado.
*int veiculoExiste(FILE arquivoVeiculos, int codigoVeiculo):

Propósito: Verifica se um veículo existe.
Parâmetros:
arquivoVeiculos: Ponteiro para o arquivo de veículos.
codigoVeiculo: Código do veículo a ser verificado.
**void cadastrarLocacao(FILE *arquivoLocacoes, FILE *arquivoClientes, FILE arquivoVeiculos, int totalLocacoes):

Propósito: Cadastra uma nova locação.
Parâmetros:
arquivoLocacoes: Ponteiro para o arquivo de locações.
arquivoClientes: Ponteiro para o arquivo de clientes.
arquivoVeiculos: Ponteiro para o arquivo de veículos.
totalLocacoes: Ponteiro para o total de locações.
**void darBaixaLocacao(FILE *arquivoLocacoes, FILE arquivoVeiculos, int totalLocacoes):

Propósito: Dá baixa em uma locação e calcula o valor total a ser pago.
Parâmetros:
arquivoLocacoes: Ponteiro para o arquivo de locações.
arquivoVeiculos: Ponteiro para o arquivo de veículos.
totalLocacoes: Ponteiro para o total de locações.
**void mostrarLocacoesCliente(FILE arquivoLocacoes, FILE arquivoClientes, int codigoOuNomeCliente):

Propósito: Mostra todas as locações de um cliente pelo código ou nome.
Parâmetros:
arquivoLocacoes: Ponteiro para o arquivo de locações.
arquivoClientes: Ponteiro para o arquivo de clientes.
codigoOuNomeCliente: Código ou nome do cliente para busca das locações.
**void calcularPontosFidelidade(FILE arquivoLocacoes, FILE arquivoClientes):

Propósito: Calcula os pontos de fidelidade para os clientes.
Parâmetros:
arquivoLocacoes: Ponteiro para o arquivo de locações.
arquivoClientes: Ponteiro para o arquivo de clientes.
*void aplicarDesconto(FILE arquivoLocacoes):

Propósito: Aplica um cupom com 50% de desconto em uma locação.
Parâmetros:
arquivoLocacoes: Ponteiro para o arquivo de locações.



Caso de Teste 1:  Cadastro de Cliente
Entrada:
Nome: Maria Silva
Endereço: Rua das Flores, 123
Telefone: 987654321
Passos:
Inserir os dados acima para cadastrar um novo cliente.
Saída Esperada:
Confirmação de cadastro bem-sucedido para Maria Silva com as informações registradas.

Caso de Teste 2:  Realização de Locação
Entrada:
Cliente: Maria Silva (código: 1001)
Data de Retirada: 15/12/2023
Data de Devolução: 20/12/2023
Quantidade de Ocupantes Necessária: 4
Passos:
Localizar um veículo disponível para o período e a quantidade de ocupantes desejada.
Escolher um veículo disponível com código 2002 para a locação.
Saída Esperada:
Confirmação da locação bem-sucedida do veículo com código 2002 para Maria Silva no período especificado.

Caso de Teste 3: Encerramento de Locação com Atraso
Entrada:
Código da Locação: 3003
Data de Entrega Real: 25/12/2023
Passos:
Informar a data de entrega real do veículo para a locação com código 3003.
Saída Esperada:
Identificação de atraso na devolução.
Cálculo da multa por atraso.
Atualização do status do veículo para "Disponível".
Encerramento da locação com cobrança do valor total e multa, se aplicável.


Caso de Teste 5:  Pesquisa de Cliente por Código
Entrada:
Código do Cliente: 1001
Passos:
Pesquisar o cliente com código 1001.
Saída Esperada:
Exibição das informações do cliente Maria Silva.

Caso de Teste 6: Pesquisa de Veículo por Descrição
Entrada:
Descrição do Veículo: SUV
Passos:
Pesquisar veículos com a descrição "SUV".
Saída Esperada:
Exibição de todos os veículos cadastrados com a descrição "SUV".


Caso de Teste 8:  Aplicação de Desconto em Locação
Entrada:
Código da Locação: 4004
Passos:
Aplicar o cupom de desconto de 50% na locação com código 4004.
Saída Esperada:
Confirmação da aplicação do desconto com sucesso e exibição do novo valor da locação.


Caso de Teste 12:  Pesquisa de Cliente Inexistente
Entrada:
Código do Cliente: 9999
Passos:
Pesquisar um cliente com código inexistente.
Saída Esperada:
Mensagem indicando que o cliente não foi encontrado.



Caso de Teste 13:  Pesquisa de Veículo Inexistente
Entrada:
Descrição do Veículo: Esportivo
Passos:
Pesquisar veículos com a descrição "Esportivo".
Saída Esperada:
Mensagem indicando que não há veículos cadastrados com essa descrição.



Caso de Teste 14: Premiação de Clientes  (com Bug na Exibição de Nomes)
Entrada:
Realizar a premiação para os clientes com base no histórico de locações.
Passos:
Executar o processo de premiação dos clientes.
Saída Esperada:
Aumento nos pontos de fidelidade dos clientes elegíveis com base nas locações.
Exibição dos nomes dos clientes premiados.

Bug Encontrado:
Problema: Os nomes dos clientes não estão sendo exibidos após a premiação.
Comportamento Atual: Apenas os pontos de fidelidade são exibidos, os nomes dos clientes estão ausentes na listagem.
Observações Adicionais:
Este bug impede a visualização dos nomes dos clientes premiados, dificultando a identificação 
Este cenário de teste identifica um problema específico na exibição dos nomes dos clientes premiados após o processo de premiação.


Caso de Teste 15:  Visualização de Locações por Cliente com Bug na Listagem
Entrada:
Solicitação para visualizar as locações de um cliente específico.
Passos:
Escolher um cliente para visualizar suas locações.
Saída Esperada:
Exibição das locações do cliente selecionado, listando as informações relevantes de cada locação.
Bug Encontrado:
Problema: A listagem não mostra corretamente as locações do cliente selecionado.
Comportamento Atual: Após selecionar um cliente, a listagem não exibe as locações associadas a ele.
Observações Adicionais:
Este bug impede a exibição correta das locações do cliente, dificultando a visualização e o acompanhamento das locações ativas ou anteriores de cada cliente. Essa falha na exibição pode atrapalhar o gerenciamento eficaz das locações por cliente

