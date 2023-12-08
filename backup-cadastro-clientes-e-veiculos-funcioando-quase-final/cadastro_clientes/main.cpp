#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <locale>
#include <limits>
#include <fstream>
#include <cctype>

#define MAX_CLIENTES 1000
#define MAX_VEICULOS 1000

struct Cliente
{
    int codigo;
    std::string nome;
    std::string endereco;
    std::string telefone;
};

struct Veiculo
{
    int codigo;
    std::string descricao;
    std::string modelo;
    std::string cor;
    std::string placa;
    double valorDiaria;
    int ocupantes;
    std::string status;
};

class CadastroClientes
{
private:
    std::vector<Cliente> clientes;

    // Lógica de validação do ID...
    bool validarID(const std::string& entrada)
    {
        for (char c : entrada)
        {
            if (!std::isdigit(c))
            {
                return false;
            }
        }
        return true;
    }

public:
    void cadastrarCliente(int codigo, const std::string &nome, const std::string &endereco, const std::string &telefone)
    {
        // Lógica para cadastrar um novo cliente...
        for (const auto& cliente : clientes)
        {
            if (cliente.codigo == codigo)
            {
                std::cout << "Erro: Já existe um cliente com este código." << std::endl;
                return;
            }
        }

        if (clientes.size() >= MAX_CLIENTES)
        {
            std::cout << "Erro: Limite máximo de clientes atingido." << std::endl;
            return;
        }

        Cliente novoCliente;
        novoCliente.codigo = codigo;
        novoCliente.nome = nome;
        novoCliente.endereco = endereco;
        novoCliente.telefone = telefone;

        clientes.push_back(novoCliente);
        std::cout << "\nCliente cadastrado com sucesso!" << std::endl;
    }

    void mostrarClientes() const
    {
        if (clientes.empty())
        {
            std::cout << "Nenhum cliente cadastrado." << std::endl;
            return;
        }

        std::cout << "Clientes cadastrados:" << std::endl;
        for (const auto& cliente : clientes)
        {
            std::cout << "Código: " << cliente.codigo << ", Nome: " << cliente.nome
                      << ", Endereço: " << cliente.endereco << ", Telefone: " << cliente.telefone << std::endl;
        }
    }

    void salvarClientes() const
    {
        // Lógica para salvar os clientes em um arquivo...
        std::ofstream arquivo("clientes.txt");
        if (arquivo.is_open())
        {
            for (const auto& cliente : clientes)
            {
                arquivo << cliente.codigo << ":" << cliente.nome << " | " << cliente.endereco << "| Telefone:" << cliente.telefone << "\n";
            }
            arquivo.close();
        }
        else
        {
            std::cout << "Erro ao abrir o arquivo para escrita." << std::endl;
        }
    }

    // Função para remover espaços em branco extras de uma string
        std::string trim(const std::string& str)
        {
            size_t first = str.find_first_not_of(' ');
            size_t last = str.find_last_not_of(' ');
            return str.substr(first, (last - first + 1));
        }


    void carregarClientes()
{
    std::ifstream arquivo("clientes.txt");
    if (arquivo.is_open())
    {
        std::string linha;
        while (std::getline(arquivo, linha))
        {
            std::istringstream iss(linha);
            std::string codigoStr, nome, enderecoTelefone;

            if (std::getline(iss, codigoStr, ':') && std::getline(iss, nome, '|') && std::getline(iss, enderecoTelefone))
            {
                Cliente cliente;
                cliente.codigo = std::stoi(codigoStr);

                // Separando o endereço e o telefone
                size_t posTelefone = enderecoTelefone.find("Telefone:");
                if (posTelefone != std::string::npos)
                {
                    cliente.nome = nome;
                    cliente.endereco = enderecoTelefone.substr(0, posTelefone);
                    cliente.telefone = enderecoTelefone.substr(posTelefone + 9); // Ignorando "Telefone:"

                    clientes.push_back(cliente);
                }
                else
                {
                    throw std::invalid_argument("Erro: Formato inválido para cliente.");
                }
            }
            else
            {
                throw std::invalid_argument("Erro: Formato inválido para cliente.");
            }
        }
        arquivo.close();
    }
    else
    {
        std::cout << "Arquivo de clientes não encontrado. Um novo será criado ao cadastrar um cliente.\n\n";
    }
}





    void criarNovoCliente()
    {
        // Lógica para criar um novo cliente...
        int codigo;
        std::string nome, endereco, telefone;
        char continuar;

        do
        {
            std::string entradaCodigo;
            do
            {
                std::cout << "\nDigite o código do novo cliente: ";
                std::cin >> entradaCodigo;

                if (!validarID(entradaCodigo))
                {
                    std::cout << "Por favor, digitar um ID numérico apenas!" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                else
                {
                    codigo = std::stoi(entradaCodigo);
                    break;
                }
            }
            while (true);

            bool codigoExistente = false;
            for (const auto& cliente : clientes)
            {
                if (cliente.codigo == codigo)
                {
                    codigoExistente = true;
                    std::cout << "Erro: Já existe um cliente com este código." << std::endl;
                    break;
                }
            }
            if (!codigoExistente)
            {
                std::cout << "Digite o nome do novo cliente: ";
                std::cin.ignore();
                std::getline(std::cin, nome);

                std::cout << "Digite o endereco do novo cliente: ";
                std::getline(std::cin, endereco);

                bool apenasNumeros;
                do
                {
                    std::cout << "Digite o telefone do novo cliente: ";
                    std::cin >> telefone;

                    apenasNumeros = true;
                    for (char c : telefone)
                    {
                        if (!std::isdigit(c))
                        {
                            apenasNumeros = false;
                            break;
                        }
                    }

                    if (!apenasNumeros)
                    {
                        std::cout << "Erro: Digite apenas números para o telefone do cliente." << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
                while (!apenasNumeros);

                cadastrarCliente(codigo, nome, endereco, telefone);
            }

            do
            {
                std::cout << "Deseja cadastrar outro cliente? (S/N): ";
                std::cin >> continuar;

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (std::toupper(continuar) != 'S' && std::toupper(continuar) != 'N')
                {
                    std::cout << "Para prosseguir, favor digitar S ou N" << std::endl;
                }
            }
            while (std::toupper(continuar) != 'S' && std::toupper(continuar) != 'N');
        }
        while (std::toupper(continuar) == 'S');

        salvarClientes();
    }
};


// Cadastramento de Veículos


class CadastroVeiculos
{
private:
    std::vector<Veiculo> veiculos;

    bool validarID(const std::string &entrada)
    {
        // Lógica de validação do ID...
        for (char c : entrada)
        {
            if (!std::isdigit(c))
            {
                return false;
            }
        }
        return true;
    }

    bool validarDadosVeiculo(const Veiculo &veiculo) const
    {
        // Lógica para validar os dados de um veículo...
        for (const auto& v : veiculos)
        {
            if (v.codigo == veiculo.codigo)
            {
                std::cout << "Erro: Já existe um veículo com este código." << std::endl;
                return false;
            }
        }

        for (const auto& v : veiculos)
        {
            if (v.placa == veiculo.placa)
            {
                std::cout << "Erro: Já existe um veículo com esta placa." << std::endl;
                return false;
            }
        }

        // Outras verificações de validação para os dados do veículo podem ser adicionadas aqui

        return true;
    }

public:
    void cadastrarVeiculo()
    {
        // Lógica para cadastrar um novo veículo...
        Veiculo novoVeiculo;
        std::string inputCodigo;

        do
        {
            std::cout << "\nDigite o código do novo veículo: ";
            std::cin >> inputCodigo;

            if (!validarID(inputCodigo))
            {
                std::cout << "Por favor, digitar um ID numérico apenas!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        while (!validarID(inputCodigo));     // Valida se é um ID numérico

        novoVeiculo.codigo = std::stoi(inputCodigo);

        for (const auto& v : veiculos)
        {
            if (v.codigo == novoVeiculo.codigo)
            {
                std::cout << "Erro: Já existe um veículo com este código." << std::endl;
                cadastrarVeiculo(); // Pedir um novo código e cadastrar novamente
                return;
            }
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Digite a descrição do veículo: ";
        std::getline(std::cin, novoVeiculo.descricao);

        std::cout << "Digite o modelo do veículo: ";
        std::getline(std::cin, novoVeiculo.modelo);

        std::cout << "Digite a cor do veículo: ";
        std::getline(std::cin, novoVeiculo.cor);

        std::cout << "Digite a placa do veículo: ";
        std::getline(std::cin, novoVeiculo.placa);

        bool valorDiariaValido = false;
        do
        {
            std::cout << "Digite o valor da diária do veículo: ";
            std::string inputValorDiaria;
            std::getline(std::cin, inputValorDiaria);
            try
            {
                novoVeiculo.valorDiaria = std::stod(inputValorDiaria);
                if (novoVeiculo.valorDiaria <= 0)
                {
                    std::cout << "Valor da diária inválido. Deve ser maior que zero." << std::endl;
                }
                else
                {
                    valorDiariaValido = true;
                }
            }
            catch (std::exception const &e)
            {
                std::cout << "Valor da diária inválido. Deve ser um número." << std::endl;
            }
        }
        while (!valorDiariaValido);

        bool ocupantesValido = false;
        do
        {
            std::cout << "Digite a quantidade de ocupantes do veículo: ";
            std::string inputOcupantes;
            std::getline(std::cin, inputOcupantes);
            try
            {
                novoVeiculo.ocupantes = std::stoi(inputOcupantes);
                if (novoVeiculo.ocupantes <= 0)
                {
                    std::cout << "Quantidade de ocupantes inválida. Deve ser maior que zero." << std::endl;
                }
                else
                {
                    ocupantesValido = true;
                }
            }
            catch (std::exception const &e)
            {
                std::cout << "Quantidade de ocupantes inválida. Deve ser um número." << std::endl;
            }
        }
        while (!ocupantesValido);

        std::string status;
        do
        {
            std::cout << "Status do veículo (alugado, disponivel, manutencao): ";
            std::cin >> status;

            if (status != "alugado" && status != "disponivel" && status != "manutencao")
            {
                std::cout << "Opção inválida. Escolha entre 'alugado', 'disponivel' ou 'manutencao'." << std::endl;
            }
        }
        while (status != "alugado" && status != "disponivel" && status != "manutencao");

        novoVeiculo.status = status;

        if (validarDadosVeiculo(novoVeiculo))
        {
            veiculos.push_back(novoVeiculo);
            std::cout << "Veículo cadastrado com sucesso!" << std::endl;
        }
        else
        {
            std::cout << "Erro ao cadastrar o veículo. Verifique os dados fornecidos." << std::endl;
        }

        char continuar;
        do
        {
            std::cout << "Deseja cadastrar outro veículo? (S/N): ";
            std::cin >> continuar;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (std::toupper(continuar) != 'S' && std::toupper(continuar) != 'N')
            {
                std::cout << "Para prosseguir, favor digitar S ou N" << std::endl;
            }
        }
        while (std::toupper(continuar) != 'S' && std::toupper(continuar) != 'N');

        if (std::toupper(continuar) == 'S')
        {
            cadastrarVeiculo();
        }
    }

    void mostrarVeiculos() const
    {
        // Lógica para mostrar os veículos cadastrados...
        std::cout << "\n\nVeículos cadastrados:" << std::endl;
        for (const auto& veiculo : veiculos)
        {
            std::cout << "Código: " << veiculo.codigo << ", Descrição: " << veiculo.descricao
                      << ", Modelo: " << veiculo.modelo << ", Cor: " << veiculo.cor
                      << ", Placa: " << veiculo.placa << ", Valor Diária: " << veiculo.valorDiaria
                      << ", Ocupantes: " << veiculo.ocupantes << ", Status: " << veiculo.status << std::endl;
        }
    }

    void salvarVeiculos() const
    {
        // Lógica para salvar os veículos em um arquivo...
        std::ofstream arquivo("veiculos.txt");
        if (arquivo.is_open())
        {
            for (const auto& veiculo : veiculos)
            {
                arquivo << veiculo.codigo << ":" << veiculo.descricao << ":" << veiculo.modelo << ":"
                        << veiculo.cor << ":" << veiculo.placa << ":" << veiculo.valorDiaria << ":"
                        << veiculo.ocupantes << ":" << veiculo.status << "\n";
            }
            arquivo.close();
        }
        else
        {
            std::cout << "Error: 404 ao abrir o arquivo de veiculos para escrita." << std::endl;
        }
    }

    void carregarVeiculos()
    {
        std::ifstream arquivo("veiculos.txt");
        if (arquivo.is_open())
        {
            std::string linha;
            while (std::getline(arquivo, linha))
            {
                std::istringstream iss(linha);
                std::string token;
                Veiculo veiculo;

                std::vector<std::string> campos;
                while (std::getline(iss, token, ':'))
                {
                    campos.push_back(token);
                }

                if (campos.size() >= 8)
                {
                    veiculo.codigo = std::stoi(campos[0]);
                    veiculo.descricao = campos[1];
                    veiculo.modelo = campos[2];
                    veiculo.cor = campos[3];
                    veiculo.placa = campos[4];
                    veiculo.valorDiaria = std::stod(campos[5]);
                    veiculo.ocupantes = std::stoi(campos[6]);
                    veiculo.status = campos[7];



                    veiculos.push_back(veiculo);
                }
                else
                {
                    throw std::invalid_argument("Erro: Formato inválido para veículo.");
                }
            }
            arquivo.close();
        }
        else
        {
            std::cout << "Arquivo de veículos não encontrado. Um novo será criado ao cadastrar um veículo.\n\n";
        }
    }

};



//Programa principal

int main()
{
    std::setlocale(LC_ALL, "Portuguese_Brazil");

    CadastroClientes cadastroClientes;
    cadastroClientes.carregarClientes(); // Carrega os clientes salvos anteriormente

    // Mostra os clientes carregados
    cadastroClientes.mostrarClientes();

    // Cria um novo cliente
    cadastroClientes.criarNovoCliente();

    // Salva os clientes após adicionar o novo
    cadastroClientes.salvarClientes();

    CadastroVeiculos cadastroVeiculos;

    cadastroVeiculos.carregarVeiculos(); // Carrega os veículos salvos anteriormente


    // Mostra os veículos carregados
    cadastroVeiculos.mostrarVeiculos();



    // Cadastra um novo veículo
    cadastroVeiculos.cadastrarVeiculo();

    // Salva os veículos após adicionar o novo
    cadastroVeiculos.salvarVeiculos();

    return 0;
}
