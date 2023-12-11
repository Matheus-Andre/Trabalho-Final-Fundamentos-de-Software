#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


struct Cliente {
    // Definição da estrutura Cliente
    int codigo;
    char nome[50];
    char endereco[100];
    char telefone[15];
    int pontosFidelidade;
};

struct Veiculo {
    // Definição da estrutura Veiculo
    int codigo;
    char descricao[50];
    char modelo[20];
    char cor[20];
    char placa[15];
    float valorDiaria;
    int ocupantes;
    char status[20]; // "Locado" ou "Disponivel"
};

struct Locacao {
    // Definição da estrutura Locacao
    int codigo;
    char dataRetirada[15];
    char dataDevolucao[15];
    char seguro[5];
    int quantidadeDias;
    int codigoCliente;
    int codigoVeiculo;
    int contratarSeguro;
    float valorTotal;
    char status[20];

};

struct Data {
    int dia;
    int mes;
    int ano;
};






// Função para comparar duas datas no formato dd/mm/aaaa
int compararDatas(const char *data1, const char *data2) {
    int dia1, mes1, ano1, dia2, mes2, ano2;

    sscanf(data1, "%d/%d/%d", &dia1, &mes1, &ano1);
    sscanf(data2, "%d/%d/%d", &dia2, &mes2, &ano2);

    if (ano1 < ano2 || (ano1 == ano2 && (mes1 < mes2 || (mes1 == mes2 && dia1 < dia2)))) {
        return -1; // data1 é anterior a data2
    } else if (ano1 == ano2 && mes1 == mes2 && dia1 == dia2) {
        return 0; // as datas são iguais
    } else {
        return 1; // data1 é posterior a data2
    }
}


int totalClientes = 0;
int totalVeiculos = 0;
void pesquisarCliente(FILE *arquivoClientes);
void pesquisarVeiculo(FILE *arquivoVeiculos);
void mostrarLocacoesCliente(FILE *arquivoLocacoes, FILE *arquivoClientes, int codigoOuNomeCliente);
void calcularPontosFidelidade(FILE *arquivoLocacoes, FILE *arquivoClientes);
void premiarClientes(FILE *arquivoClientes);







// Função para obter a data de entrega e validar com a data de devolução prevista
int obterDataEntrega(const char *dataDevolucaoPrevista) {
    char dataEntrega[15];

    printf("Digite a data de entrega (formato dd/mm/aaaa): ");
    scanf(" %[^\n]s", dataEntrega);

    // Comparar as datas para validar a entrega
    if (compararDatas(dataEntrega, dataDevolucaoPrevista) <= 0) {
        return 1; // Entrega dentro ou no prazo
    } else {
        return 0; // Entrega após o prazo
    }
}









// Função para verificar se um veículo está disponível
int veiculoDisponivel(FILE *arquivoVeiculos, int codigoVeiculo) {
    struct Veiculo veiculo;
    fseek(arquivoVeiculos, 0, SEEK_SET);

    while (fread(&veiculo, sizeof(struct Veiculo), 1, arquivoVeiculos) == 1) {
        if (veiculo.codigo == codigoVeiculo && strcmp(veiculo.status, "Disponivel") == 0) {
            return 1; // Veículo está disponível
        }
    }

    return 0; // Veículo não está disponível
}

// Função para calcular o valor total da locação
float calcularValorLocacao(FILE *arquivoVeiculos, int codigoVeiculo, int quantidadeDias, int contratarSeguro) {
    struct Veiculo veiculo;
    fseek(arquivoVeiculos, 0, SEEK_SET);

    while (fread(&veiculo, sizeof(struct Veiculo), 1, arquivoVeiculos) == 1) {
        if (veiculo.codigo == codigoVeiculo) {
            float valorTotal = veiculo.valorDiaria * quantidadeDias;

            if (contratarSeguro) {
                valorTotal += 50.0; // Valor fixo do seguro
            }

            return valorTotal;
        }
    }

    return -1.0;
}






//Parte 2: Funções para buscar cliente pelo nome e cadastrar um novo cliente


// Função para buscar cliente pelo nome
int buscarCliente(FILE *arquivoClientes, const char *nomeCliente, int *codigoCliente) {
    struct Cliente cliente;
    fseek(arquivoClientes, 0, SEEK_SET);

    while (fread(&cliente, sizeof(struct Cliente), 1, arquivoClientes) == 1) {
        if (strcmp(cliente.nome, nomeCliente) == 0) {

            return 1; // Cliente encontrado
        }
    }

    return 0; // Cliente não encontrado
}

// Função para verificar se um cliente com o mesmo código já existe no arquivo
int clienteExiste(FILE *arquivo, int codigo) {
    struct Cliente cliente;
    fseek(arquivo, 0, SEEK_SET); // Posiciona o cursor no início do arquivo

    while (fread(&cliente, sizeof(struct Cliente), 1, arquivo) == 1) {
        if (cliente.codigo == codigo) {
            return 1; // Cliente com o mesmo código já existe
        }
    }

    return 0; // Cliente com o mesmo código não existe
}



// Função para cadastrar um novo cliente
void cadastrarCliente(FILE *arquivo, int *totalClientes) {
    struct Cliente novoCliente;

    novoCliente.codigo = (*totalClientes) + 1;

    while (clienteExiste(arquivo, novoCliente.codigo)) {
        novoCliente.codigo++;
    }

    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]s", novoCliente.nome);

    printf("Digite o endereco do cliente: ");
    scanf(" %[^\n]s", novoCliente.endereco);

    printf("Digite o telefone do cliente: ");
    scanf(" %[^\n]s", novoCliente.telefone);


    fseek(arquivo, 0, SEEK_END);
    fwrite(&novoCliente, sizeof(struct Cliente), 1, arquivo);

    (*totalClientes)++;
    printf("Cliente cadastrado com sucesso!\n");
}




//Parte 3: Funções para cadastrar um novo veículo e verificar se um veículo existe


// Função para verificar se um veículo existe
int veiculoExiste(FILE *arquivoVeiculos, int codigoVeiculo) {
    struct Veiculo veiculo;
    fseek(arquivoVeiculos, 0, SEEK_SET);

    while (fread(&veiculo, sizeof(struct Veiculo), 1, arquivoVeiculos) == 1) {
        if (veiculo.codigo == codigoVeiculo) {
            return 1; // Veículo encontrado
        }
    }

    return 0; // Veículo não encontrado
}

// Função para cadastrar um novo veículo
void cadastrarVeiculo(FILE *arquivo, int *totalVeiculos) {
    struct Veiculo novoVeiculo;

    novoVeiculo.codigo = (*totalVeiculos) + 1;

    while (veiculoExiste(arquivo, novoVeiculo.codigo)) {
        novoVeiculo.codigo++;
    }

    printf("Digite a descricao do veiculo: ");
    scanf(" %[^\n]s", novoVeiculo.descricao);

    printf("Digite o modelo do veiculo: ");
    scanf(" %[^\n]s", novoVeiculo.modelo);

    printf("Digite a cor do veiculo: ");
    scanf(" %[^\n]s", novoVeiculo.cor);

    printf("Digite a placa do veiculo: ");
    scanf(" %[^\n]s", novoVeiculo.placa);

    printf("Digite o valor da diaria do veiculo: ");
    scanf("%f", &novoVeiculo.valorDiaria);

    printf("Digite a quantidade de ocupantes do veiculo: ");
    scanf("%d", &novoVeiculo.ocupantes);

    sprintf(novoVeiculo.status, "Disponivel");

    fseek(arquivo, 0, SEEK_END);
    fwrite(&novoVeiculo, sizeof(struct Veiculo), 1, arquivo);

    (*totalVeiculos)++;
    printf("Veiculo cadastrado com sucesso!\n");
}






// Função para cadastrar uma nova locação
void cadastrarLocacao(FILE *arquivoLocacoes, FILE *arquivoClientes, FILE *arquivoVeiculos, int *totalLocacoes) {
    struct Locacao novaLocacao;
    struct Cliente cliente;
    struct Veiculo veiculo;

    printf("Digite o nome do cliente que deseja alugar o veiculo: ");
    scanf(" %[^\n]s", cliente.nome);

    // Buscar cliente pelo nome
      int clienteExiste(FILE *arquivo, const char *nome) {
       struct Cliente clienteAtual;

       rewind(arquivo);  // Certifique-se de que o ponteiro do arquivo está no início

       while (fread(&clienteAtual, sizeof(struct Cliente), 1, arquivo) == 1) {
           if (strcmp(clienteAtual.nome, nome) == 0) {
               return 1;  // Cliente encontrado
           }
       }

       return 0;  // Cliente não encontrado
   }



    // Solicitar informações adicionais para a locação
    printf("Digite a data de retirada (formato dd/mm/aaaa): ");
    scanf(" %[^\n]s", novaLocacao.dataRetirada);

    printf("Digite a data de devolucao (formato dd/mm/aaaa): ");
    scanf(" %[^\n]s", novaLocacao.dataDevolucao);

    printf("Digite a quantidade de ocupantes necessaria: ");
    scanf("%d", &novaLocacao.quantidadeDias);

    // Buscar veículo disponível para a necessidade do cliente
    printf("\nVeiculos disponiveis:\n");

    fseek(arquivoVeiculos, 0, SEEK_SET);
    int veiculoEncontrado = 0;

    while (fread(&veiculo, sizeof(struct Veiculo), 1, arquivoVeiculos) == 1) {
        if (veiculo.ocupantes >= novaLocacao.quantidadeDias && strcmp(veiculo.status, "Disponivel") == 0) {
            printf("Codigo: %d | Descricao: %s | Modelo: %s | Cor: %s | Placa: %s | Valor Diaria: %.2f\n",
                   veiculo.codigo, veiculo.descricao, veiculo.modelo, veiculo.cor, veiculo.placa, veiculo.valorDiaria);
            veiculoEncontrado = 1;
        }
    }

    if (!veiculoEncontrado) {
        printf("Nenhum veiculo disponivel para a necessidade do cliente.\n");
        return;
    }

    // Solicitar escolha do veículo pelo código
    printf("\nDigite o codigo do veiculo escolhido: ");
    scanf("%d", &novaLocacao.codigoVeiculo);

    // Verificar se o veículo está disponível
    if (!veiculoDisponivel(arquivoVeiculos, novaLocacao.codigoVeiculo)) {
        printf("Veiculo escolhido nao esta disponivel.\n");
        return;
    }

    // Oferecer opção de contratar seguro
    printf("Deseja contratar um seguro para o veiculo? (1 - Sim, 0 - Nao): ");
    scanf("%d", &novaLocacao.contratarSeguro);

    // Calcular o valor total da locação
    float valorTotal = calcularValorLocacao(arquivoVeiculos, novaLocacao.codigoVeiculo, novaLocacao.quantidadeDias, novaLocacao.contratarSeguro);

    if (valorTotal < 0) {
        printf("Erro ao calcular o valor da locacao. Verifique se o veiculo foi encontrado.\n");
        return;
    }

    // Atualizar o status do veículo para "Locado"
    fseek(arquivoVeiculos, 0, SEEK_SET);
    while (fread(&veiculo, sizeof(struct Veiculo), 1, arquivoVeiculos) == 1) {
        if (veiculo.codigo == novaLocacao.codigoVeiculo) {
            strcpy(veiculo.status, "Locado");
            fseek(arquivoVeiculos, -sizeof(struct Veiculo), SEEK_CUR);
            fwrite(&veiculo, sizeof(struct Veiculo), 1, arquivoVeiculos);
            break;
        }
    }

    // Gravar a nova locação no arquivo
    fseek(arquivoLocacoes, 0, SEEK_END);
    fwrite(&novaLocacao, sizeof(struct Locacao), 1, arquivoLocacoes);

    (*totalLocacoes)++;
    printf("Locacao cadastrada com sucesso! Valor total: R$ %.2f\n", valorTotal);
}

int compararDatas(const char *data1, const char *data2);






// Função para dar baixa em uma locação e calcular o valor total a ser pago
void darBaixaLocacao(FILE *arquivoLocacoes, FILE *arquivoVeiculos, int *totalLocacoes) {
    struct Locacao locacao;
    struct Veiculo veiculo;

    // Solicitar o código da locação a ser encerrada
    int codigoLocacao;
    printf("Digite o codigo da locacao a ser encerrada: ");
    scanf("%d", &codigoLocacao);

    // Buscar a locação pelo código
    fseek(arquivoLocacoes, (codigoLocacao - 1) * sizeof(struct Locacao), SEEK_SET);
    fread(&locacao, sizeof(struct Locacao), 1, arquivoLocacoes);

    // Verificar se a locação existe
    if (locacao.codigo == 0) {
        printf("Locacao nao encontrada.\n");
        return;
    }

    // Solicitar a data de entrega do veículo
    char dataEntrega[15];
    printf("Digite a data de entrega (formato dd/mm/aaaa): ");
    scanf(" %[^\n]s", dataEntrega);

    // Comparar a data de entrega com a data de devolução prevista
    int comparacaoDatas = strcmp(dataEntrega, locacao.dataDevolucao);

    // Calcular a multa por atraso, se houver
    float multa = 0.0;
    if (comparacaoDatas > 0) {
        // Calcular o número de dias de atraso
        int diasAtraso = compararDatas(dataEntrega, locacao.dataDevolucao);

        // Calcular a multa
        multa = (0.05 * locacao.valorTotal) + (30.0 * diasAtraso);
        printf("Multa por atraso: R$ %.2f\n", multa);
    }
    else {

            printf("Entrega realizada no prazo. Sem multa.\n");
    }

// Função para aplicar um cupom com 50% de desconto
void aplicarDesconto(FILE *arquivoLocacoes) {
    int codigoLocacao;
    printf("Digite o codigo da locacao para aplicar o cupom: ");
    scanf("%d", &codigoLocacao);

    struct Locacao locacao;
    fseek(arquivoLocacoes, (codigoLocacao - 1) * sizeof(struct Locacao), SEEK_SET);
    fread(&locacao, sizeof(struct Locacao), 1, arquivoLocacoes);

    if (locacao.codigo == 0) {
        printf("Locacao nao encontrada.\n");
        return;
    }

    // Aplicar desconto de 50%
    locacao.valorTotal *= 0.5;

    // Atualizar o valor no arquivo
    fseek(arquivoLocacoes, (codigoLocacao - 1) * sizeof(struct Locacao), SEEK_SET);
    fwrite(&locacao, sizeof(struct Locacao), 1, arquivoLocacoes);

    printf("Cupom de 50%% de desconto aplicado com sucesso na locacao %d!\n", locacao.codigo);
}


    // Atualizar o status do veículo para "Disponivel"
    fseek(arquivoVeiculos, 0, SEEK_SET);
    while (fread(&veiculo, sizeof(struct Veiculo), 1, arquivoVeiculos) == 1) {
        if (veiculo.codigo == locacao.codigoVeiculo) {
            strcpy(veiculo.status, "Disponivel");
            fseek(arquivoVeiculos, -sizeof(struct Veiculo), SEEK_CUR);
            fwrite(&veiculo, sizeof(struct Veiculo), 1, arquivoVeiculos);
            break;
        }
    }

    // Atualizar o status da locação para "Encerrada"
    fseek(arquivoLocacoes, (codigoLocacao - 1) * sizeof(struct Locacao), SEEK_SET);
    strcpy(locacao.status, "Encerrada");
    fwrite(&locacao, sizeof(struct Locacao), 1, arquivoLocacoes);

    // Mostrar o valor total a ser pago (incluindo a multa, se aplicável)
    float valorTotalPago = locacao.valorTotal + multa;
    printf("Valor total a ser pago: R$ %.2f\n", valorTotalPago);

    printf("Locacao encerrada com sucesso!\n");
}




// Função principal
int main() {
    setlocale(LC_ALL,"Portuguese");
    FILE *arquivoClientes;
    FILE *arquivoVeiculos;
    FILE *arquivoLocacoes;
    struct Cliente cliente;

    arquivoClientes = fopen("clientes.dat", "rb+");
    arquivoVeiculos = fopen("veiculos.dat", "rb+");
    arquivoLocacoes = fopen("locacoes.dat", "ab+");

    if (arquivoClientes == NULL || arquivoVeiculos == NULL || arquivoLocacoes == NULL) {
        printf("Erro ao abrir os arquivos. Certifique-se de cadastrar clientes e veiculos primeiro.\n");
        exit(EXIT_FAILURE);
    }

    // Contar o número total de locações no arquivo
    fseek(arquivoLocacoes, 0, SEEK_END);
    int totalLocacoes = ftell(arquivoLocacoes) / sizeof(struct Locacao);
    fseek(arquivoLocacoes, 0, SEEK_SET); // Posiciona o cursor no início do arquivo

    // Menu para interagir com o programa
    int opcao;
    do {
        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Cadastrar Veiculo\n");
        printf("3 - Cadastrar Locacao\n");
        printf("4 - Dar baixa em Locacao\n");
        printf("5 - Pesquisar\n");
        printf("6 - Locacao de Cliente\n");
        printf("7 - Pontos de Fidelidade\n");
        printf("8 - Premiar clientes\n");
        printf("9 - Desconto de 50%% para locacao\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarCliente(arquivoClientes, &totalClientes);
                break;
            case 2:
                cadastrarVeiculo(arquivoVeiculos, &totalVeiculos);
                break;
            case 3:
                cadastrarLocacao(arquivoLocacoes, arquivoClientes, arquivoVeiculos, &totalLocacoes);
                break;
          case 4:
                darBaixaLocacao(arquivoLocacoes, arquivoVeiculos, &totalLocacoes);
                break;
          case 5:
                printf("\n===== PESQUISAR =====\n");
                printf("1 - Pesquisar Cliente\n");
                printf("2 - Pesquisar Veiculo\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1:
                        pesquisarCliente(arquivoClientes);
                        break;
                    case 2:
                        pesquisarVeiculo(arquivoVeiculos);
                        break;
                    default:
                        printf("Opcao invalida. Tente novamente.\n");
                }
                break;// Function prototypes
void pesquisarCliente(FILE *arquivoClientes);
void pesquisarVeiculo(FILE *arquivoVeiculos);

          case 6:
                printf("\n===== MOSTRAR LOCAÇÕES DE CLIENTE =====\n");
                printf("1 - Mostrar locacoes por Codigo de Cliente\n");
                printf("2 - Mostrar locacoes por Nome de Cliente\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1:
                        printf("Digite o codigo do cliente: ");
                        int codigoCliente;
                        scanf("%d", &codigoCliente);
                        mostrarLocacoesCliente(arquivoLocacoes, arquivoClientes, codigoCliente);
                        break;
                    case 2:
                        printf("Digite o nome do cliente: ");
                        char nomeCliente[50];
                        scanf(" %[^\n]s", nomeCliente);
                        mostrarLocacoesCliente(arquivoLocacoes, arquivoClientes, nomeCliente);
                        break;
                    default:
                        printf("Opcao invalida. Tente novamente.\n");
                }
                break;

          case 7:
              calcularPontosFidelidade(arquivoLocacoes, arquivoClientes);
              printf("Pontos de fidelidade calculados com sucesso!\n");
              break;
          case 8:
              premiarClientes(arquivoClientes);
              break;
          case 9:
             aplicarDesconto(arquivoLocacoes);
              break;
          case 0:
                printf("Saindo do programa. Ate mais!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    // Fechar os arquivos
    fclose(arquivoClientes);
    fclose(arquivoVeiculos);
    fclose(arquivoLocacoes);

    return 0;
}









//QUESTAO 5
// Função para buscar cliente pelo código
int buscarClientePorCodigo(FILE *arquivoClientes, int codigo, struct Cliente *clienteEncontrado) {
    struct Cliente cliente;
    fseek(arquivoClientes, 0, SEEK_SET);

    while (fread(&cliente, sizeof(struct Cliente), 1, arquivoClientes) == 1) {
        if (cliente.codigo == codigo) {
            *clienteEncontrado = cliente;
            return 1; // Cliente encontrado
        }
    }

    return 0; // Cliente não encontrado
}

// Função para buscar veículo pelo código
int buscarVeiculoPorCodigo(FILE *arquivoVeiculos, int codigo, struct Veiculo *veiculoEncontrado) {
    struct Veiculo veiculo;
    fseek(arquivoVeiculos, 0, SEEK_SET);

    while (fread(&veiculo, sizeof(struct Veiculo), 1, arquivoVeiculos) == 1) {
        if (veiculo.codigo == codigo) {
            *veiculoEncontrado = veiculo;
            return 1; // Veículo encontrado
        }
    }

    return 0; // Veículo não encontrado
}

// Função para buscar cliente pelo nome
int buscarClientePorNome(FILE *arquivoClientes, const char *nomeCliente, struct Cliente *clienteEncontrado) {
    struct Cliente cliente;
    fseek(arquivoClientes, 0, SEEK_SET);

    while (fread(&cliente, sizeof(struct Cliente), 1, arquivoClientes) == 1) {
        if (strcmp(cliente.nome, nomeCliente) == 0) {
            *clienteEncontrado = cliente;
            return 1; // Cliente encontrado
        }
    }

    return 0; // Cliente não encontrado
}

// Função para buscar veículo pela descrição
int buscarVeiculoPorDescricao(FILE *arquivoVeiculos, const char *descricaoVeiculo, struct Veiculo *veiculoEncontrado) {
    struct Veiculo veiculo;
    fseek(arquivoVeiculos, 0, SEEK_SET);

    while (fread(&veiculo, sizeof(struct Veiculo), 1, arquivoVeiculos) == 1) {
        if (strcmp(veiculo.descricao, descricaoVeiculo) == 0) {
            *veiculoEncontrado = veiculo;
            return 1; // Veículo encontrado
        }
    }

    return 0; // Veículo não encontrado
}

// Função para imprimir as informações do cliente
void imprimirInfoCliente(const struct Cliente *cliente) {
    printf("Código: %d\n", cliente->codigo);
    printf("Nome: %s\n", cliente->nome);
    printf("Endereco: %s\n", cliente->endereco);
    printf("Telefone: %s\n", cliente->telefone);
}

// Função para imprimir as informações do veículo
void imprimirInfoVeiculo(const struct Veiculo *veiculo) {
    printf("Codigo: %d\n", veiculo->codigo);
    printf("Descricao: %s\n", veiculo->descricao);
    printf("Modelo: %s\n", veiculo->modelo);
    printf("Cor: %s\n", veiculo->cor);
    printf("Placa: %s\n", veiculo->placa);
    printf("Valor Diaria: %.2f\n", veiculo->valorDiaria);
    printf("Ocupantes: %d\n", veiculo->ocupantes);
    printf("Status: %s\n", veiculo->status);
}

// Função para pesquisar cliente por código ou nome
void pesquisarCliente(FILE *arquivoClientes) {
    int opcao;
    printf("\n===== PESQUISAR CLIENTE =====\n");
    printf("1 - Pesquisar por Codigo\n");
    printf("2 - Pesquisar por Nome\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    struct Cliente clienteEncontrado;

    switch (opcao) {
        case 1: {
            int codigoCliente;
            printf("Digite o codigo do cliente: ");
            scanf("%d", &codigoCliente);

            if (buscarClientePorCodigo(arquivoClientes, codigoCliente, &clienteEncontrado)) {
                imprimirInfoCliente(&clienteEncontrado);
            } else {
                printf("Cliente nao encontrado.\n");
            }
            break;
        }
        case 2: {
            char nomeCliente[50];
            printf("Digite o nome do cliente: ");
            scanf(" %[^\n]s", nomeCliente);

            if (buscarClientePorNome(arquivoClientes, nomeCliente, &clienteEncontrado)) {
                imprimirInfoCliente(&clienteEncontrado);
            } else {
                printf("Cliente nao encontrado.\n");
            }
            break;
        }
        default:
            printf("Opcao invalida.\n");
    }
}

// Função para pesquisar veículo por código ou descrição
void pesquisarVeiculo(FILE *arquivoVeiculos) {
    int opcao;
    printf("\n===== PESQUISAR VEÍCULO =====\n");
    printf("1 - Pesquisar por Codigo\n");
    printf("2 - Pesquisar por Descricao\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    struct Veiculo veiculoEncontrado;

    switch (opcao) {
        case 1: {
            int codigoVeiculo;
            printf("Digite o codigo do veiculo: ");
            scanf("%d", &codigoVeiculo);

            if (buscarVeiculoPorCodigo(arquivoVeiculos, codigoVeiculo, &veiculoEncontrado)) {
                imprimirInfoVeiculo(&veiculoEncontrado);
            } else {
                printf("Veiculo nao encontrado.\n");
            }
            break;
        }
        case 2: {
            char descricaoVeiculo[50];
            printf("Digite a descricao do veIculo: ");
            scanf(" %[^\n]s", descricaoVeiculo);

            if (buscarVeiculoPorDescricao(arquivoVeiculos, descricaoVeiculo, &veiculoEncontrado)) {
                imprimirInfoVeiculo(&veiculoEncontrado);
            } else {
                printf("VeIculo não encontrado.\n");
            }
            break;
        }
        default:
            printf("Opção inválida.\n");
    }
}




//QUESTAO 6
// Função para mostrar todas as locações de um cliente pelo código ou nome
void mostrarLocacoesCliente(FILE *arquivoLocacoes, FILE *arquivoClientes, int codigoOuNomeCliente) {
    struct Cliente cliente;
    struct Locacao locacao;

    // Verificar se o parâmetro é um código ou um nome
    int isCodigo = (codigoOuNomeCliente >= 1000); // Assumindo que códigos de cliente são maiores que 1000

    fseek(arquivoClientes, 0, SEEK_SET);

    // Encontrar o cliente pelo código ou nome
    while (fread(&cliente, sizeof(struct Cliente), 1, arquivoClientes) == 1) {
        if ((isCodigo && cliente.codigo == codigoOuNomeCliente) || (!isCodigo && strcmp(cliente.nome, codigoOuNomeCliente) == 0)) {
            // Cliente encontrado, agora mostrar suas locações
            fseek(arquivoLocacoes, 0, SEEK_SET);
            printf("Locacoes do cliente %s (Codigo: %d):\n", cliente.nome, cliente.codigo);

            while (fread(&locacao, sizeof(struct Locacao), 1, arquivoLocacoes) == 1) {
                if (locacao.codigoCliente == cliente.codigo) {
                    // Mostrar informações da locação
                    // Aqui você pode personalizar a exibição conforme necessário
                    printf("Codigo da Locacao: %d\n", locacao.codigo);
                    // ... outras informações da locação ...
                }
            }

            printf("Fim das locacoes do cliente %s.\n", cliente.nome);
            return; // Saindo da função após mostrar as locações do cliente encontrado
        }
    }

    // Se chegou aqui, o cliente não foi encontrado
    printf("Cliente nao encontrado.\n");
}





//QUESTAO 7
void calcularPontosFidelidade(FILE *arquivoLocacoes, FILE *arquivoClientes) {
    struct Locacao locacao;
    struct Cliente cliente;

    fseek(arquivoLocacoes, 0, SEEK_SET);
    while (fread(&locacao, sizeof(struct Locacao), 1, arquivoLocacoes) == 1) {
        fseek(arquivoClientes, (locacao.codigoCliente - 1) * sizeof(struct Cliente), SEEK_SET);
        fread(&cliente, sizeof(struct Cliente), 1, arquivoClientes);

        // Calcular pontos de fidelidade
        int pontos = locacao.quantidadeDias * 10;

        // Atualizar pontos de fidelidade do cliente
        cliente.pontosFidelidade += pontos;

        // Atualizar arquivo de clientes
        fseek(arquivoClientes, (locacao.codigoCliente - 1) * sizeof(struct Cliente), SEEK_SET);
        fwrite(&cliente, sizeof(struct Cliente), 1, arquivoClientes);
    }
}

// Função para pesquisar clientes que atingiram 500 pontos e premiá-los
void premiarClientes(FILE *arquivoClientes) {
    struct Cliente cliente;

    fseek(arquivoClientes, 0, SEEK_SET);
    while (fread(&cliente, sizeof(struct Cliente), 1, arquivoClientes) == 1) {
        if (cliente.pontosFidelidade >= 500) {
            printf("Cliente %s atingiu %d pontos de fidelidade e será premiado!\n", cliente.nome, cliente.pontosFidelidade);
            // Implemente a lógica para premiar o cliente (por exemplo, enviar um kit da LocaMais)
        }
    }
}

//QUESTAO 8


// Função para aplicar um cupom com 50% de desconto

void aplicarDesconto(FILE *arquivoLocacoes) {
    int codigoLocacao;
    printf("Digite o codigo da locacao para aplicar o cupom: ");
    scanf("%d", &codigoLocacao);

    struct Locacao locacao;
    fseek(arquivoLocacoes, (codigoLocacao - 1) * sizeof(struct Locacao), SEEK_SET);
    fread(&locacao, sizeof(struct Locacao), 1, arquivoLocacoes);

    if (locacao.codigo == 0) {
        printf("Locacao nao encontrada.\n");
        return;
    }

    // Exibir valor original
    printf("Valor original da locacao %d: R$ %.2f\n", locacao.codigo, locacao.valorTotal);

    // Aplicar desconto de 50%
    float valorComDesconto = locacao.valorTotal * 0.5;
    locacao.valorTotal -= valorComDesconto;

    // Atualizar o valor no arquivo
    fseek(arquivoLocacoes, (codigoLocacao - 1) * sizeof(struct Locacao), SEEK_SET);
    fwrite(&locacao, sizeof(struct Locacao), 1, arquivoLocacoes);

    // Exibir valor com desconto
    printf("Cupom de 50%% de desconto aplicado com sucesso na locacao %d!\n", locacao.codigo);
    printf("Novo valor com desconto: R$ %.2f\n", valorComDesconto);
}





