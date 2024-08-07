/**
 * Author: Leandro Santos, João Vicente e Raul Gomes
 * Date: 13Jan2024
 * Description: main.c
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// include bibliotecas internas
#include "ui.h"
#include "sgb.h"

/**
 * Process os pedidos no menu Clientes
 * @param banco
 **/
void processaMenuClientes(Banco *b) //Menu Clientes
{
    //Declaração de variaveis
    int id_cliente;
    Cliente *cl;

    int opt;
    while (1)
    {
        //Declaração de variaveis
        char nome_cl[MAX_NAME];
        char nif[NIF_SIZE];
        opt = menuClientes();
        switch (opt)
        {
        case 1:
            if (check_if_bank_full(b)) //Verificação se o banco chegou ao máximo (com os clientes no máximo)
            {
                break;
            }
            memset(nome_cl, '\0', MAX_NAME); //Alocação de memória
            memset(nif, '\0', NIF_SIZE);
            pedirString(nome_cl, ASK_NAME, MAX_NAME); //Pede o nome do utilizador
            pedirString(nif, ASK_NIF, NIF_SIZE); //Pede o nif do utilizador
            inserir_cliente(b, nome_cl, nif); //Função para inserir o cliente
            break;
        case 2:
            //Listar clientes
            sort_clientes(b); //Função para ordenar os clientes por ordem alfabetica
            listar_clientes(b); //Função para listar os clientes
            break;
        case 3:
            // mostrar cliente
            if (check_if_bank_empty(b)) //Verificação se o banco está vazio (sem clientes)
            {
                NO_CLIENTS_ERROR; //Erro caso não existam clientes no banco
                break;
            }
            id_cliente = pedirInteiro(ASK_CLIENT_ID); //Pede o id do cliente
            if (get_cliente_by_id(b, id_cliente) == NULL) //Verificação se o cliente com o id introduzido é NULL
            {
                NO_SUCH_CLIENT_ERROR(id_cliente); //Erro caso o cliente com o id introduzido não exista
                break;
            }
            cl = get_cliente_by_id(b, id_cliente); //Busca pelo cliente com o id introduzido

            mostrar_cliente(b, cl); //Função para mostrar o cliente
            break;
        case 4:
            //Apagar cliente

            if (check_if_bank_empty(b)) //Verificação se o banco está vazio (sem clientes)
            {
                NO_CLIENTS_ERROR; //Erro caso não existam clientes no banco
                break;
            }
            id_cliente = pedirInteiro(ASK_CLIENT_ID); //Pede o id do cliente
            if (get_cliente_by_id(b, id_cliente) == NULL) //Verificação se o cliente com o id introduzido é NULL
            {
                NO_SUCH_CLIENT_ERROR(id_cliente); //Erro caso o cliente com o id introduzido não exista
                break;
            }
            cl = get_cliente_by_id(b, id_cliente); //Busca pelo cliente com o id introduzido
            apagar_cliente(b, cl); //Função para apagar o cliente
            break;
        case 5:
            //Procurar clientes

            //Declaração de variaveis
            char termo[MAX_NAME];
            if (check_if_bank_empty(b)) //Verificação se o banco está vazio (sem clientes)
            {
                NO_CLIENTS_ERROR; //Erro caso não existam clientes no banco
                break;
            }
            memset(termo, '\0', MAX_NAME); //Alocação de memória
            pedirString(termo, ASK_FIND_TERM, MAX_NAME); //Pede o nome do cliente
            procurar_cliente(b, termo); //Função para procurar o cliente
            break;
        case 9:
            return; // Sai da função, logo do menu Clientes
        default:
            INVALID_OPTION; //Output caso o utilizador escolha uma opção diferente das opções existentes
        }
    }
}

/**
 * Process os pedidos no menu Contas
 * @param banco
 **/
void processaMenuContas(Banco *b) //Menu Contas
{
    //Declaração de variaveis
    char id_conta[CODE_SIZE];
    Cliente *cl;
    Conta *conta;
    int id_cliente;
    int cont = 0;
    int opt;
    while (1)
    {
        //Declaração de variaveis
        char codigo_conta[CODE_SIZE];
        opt = menuContas();
        switch (opt)
        {
        case 1:
            // Criar conta
            if (check_if_bank_empty(b)) //Verificação se o banco está vazio (sem clientes)
            {
                NO_CLIENTS_ERROR; //Erro caso não existam clientes no banco
                break;
            }
            int id = pedirInteiro(ASK_CLIENT_ID); //Pede o id do cliente
            int cliente_encontrado = 0;
            for (int i = 0; i < b->num_clientes; i++) //Percorre todos os clientes existentes
            {
                if (b->clientes[i]->id_cliente == id) //Caso o id do cliente seja igual ao id introduzido faz
                {
                    cliente_encontrado = 1;
                    if (b->clientes[i]->num_contas < MAX_N_ACCOUNTS) //caso o número de contas do cliente seja menor do que o número máximo de contas faz
                    {

                        memset(codigo_conta, '\0', CODE_SIZE); //Alocação de memória
                        pedirString(codigo_conta, ASK_ACCOUNT_ID, CODE_SIZE); //Pede o código da conta
                        inserir_conta(b, id, codigo_conta); //Função para inserir a conta

                        continue;
                    }
                    else
                    {

                        NEW_ACCOUNT_ERROR_CLIENT_OVRELOADED(id); //Erro caso o cliente já tenha o máximo de contas possivel por cliente
                        continue;
                    }
                }
            }
            if (!cliente_encontrado) //caso o cliente não existir faz
            {
                NO_SUCH_CLIENT_ERROR(id); //Erro caso o cliente com o id introduzido não exista
            }
            break;
        case 2:
            //Listar contas
            if (check_if_bank_empty(b)) //Verificação se o banco está vazio (sem clientes)
            {
                NO_CLIENTS_ERROR; //Erro caso não existam clientes no banco
                break;
            }
            int id_listar = pedirInteiro(ASK_CLIENT_ID); //Pede o id do cliente
            sort_contas(b); //Função para ordenar as contas por ordem alfabetica
            listar_contas(b, id_listar); //Função para listar as contas existentes

            break;
        case 3:
            // Mostrar contas do Cliente
            if (check_if_bank_empty(b)) //Verificação se o banco está vazio (sem clientes)
            {
                NO_CLIENTS_ERROR; //Erro caso o cliente com o id introduzido não exista
                break;
            }
            id_cliente = pedirInteiro(ASK_CLIENT_ID); //Pede o id do cliente
            if (get_cliente_by_id(b, id_cliente) == NULL) //Verificação se o cliente com o id introduzido é NULL
            {
                NO_SUCH_CLIENT_ERROR(id_cliente); //Erro caso o cliente com o id introduzido não exista
                break;
            }
            cl = get_cliente_by_id(b, id_cliente); //Busca pelo cliente com o id introduzido

            cont = 0; //Contador que verifica quantas contas podem ser criadas
            for (int i = 0; i < MAX_N_ACCOUNTS; i++) //Percorre todos os espaços para contas existentes
            {
                if (cl->contas[i] == NULL) //Caso a conta seja NULL faz
                {
                    cont++; //Incrementa o contador
                }
            }
            if (cont == 3) //caso o contador seja 3 faz
            {
                CLIENT_DONT_HAVE_ACCOUNTS(cl->id_cliente); //Erro o cliente não possui contas
                break;
            }
            memset(id_conta, '\0', CODE_SIZE); //Alocação de memória
            pedirString(id_conta, ASK_ACCOUNT_ID, CODE_SIZE); //Pede o código da conta
            if (get_conta_by_id(id_conta, cl) == NULL) //Verificação se o cliente com o id introduzido é NULL
            {
                NO_SUCH_ACCOUNT_ERROR(id_cliente, id_conta); //Erro caso a conta com o código introduzido não exista
                break;
            }
            conta = get_conta_by_id(id_conta, cl); //Busca a conta do código introduzido
            sort_contas(b); //Função para ordenar as contas por ordem alfabetica
            mostrar_conta(b, id_cliente, cl, conta); //Função para mostrar as contas do cliente
            break;
        case 4:
            // Fechar Conta
            if (check_if_bank_empty(b)) //Verificação se o banco está vazio (sem clientes)
            {
                NO_CLIENTS_ERROR; //Erro caso o cliente com o id introduzido não exista
                break;
            }
            id_cliente = pedirInteiro(ASK_CLIENT_ID); //Pede o id do cliente
            if (get_cliente_by_id(b, id_cliente) == NULL) //Verificação se o cliente com o id introduzido é NULL
            {
                NO_SUCH_CLIENT_ERROR(id_cliente); //Erro caso a conta com o código introduzido não exista
                break;
            }
            cl = get_cliente_by_id(b, id_cliente); //Busca o cliente com o id introduzido
            if (cl->num_contas == 0) //caso o número de contas seja 0 faz
            {
                CLIENT_DONT_HAVE_ACCOUNTS(id_cliente); //Erro caso o cliente não tenha contas
                break;
            }
            memset(id_conta, '\0', CODE_SIZE); //Alocação de memória
            pedirString(id_conta, ASK_ACCOUNT_ID, CODE_SIZE); //Pede o código da conta
            if (get_conta_by_id(id_conta, cl) == NULL) //Verificação se o cliente com o id introduzido é NULL
            {
                NO_SUCH_ACCOUNT_ERROR(id_cliente, id_conta); //Erro caso a conta com o código introduzido não exista
                break;
            }
            conta = get_conta_by_id(id_conta, cl); //Busca a conta do código introduzido
            eliminar_conta(b, cl, conta); //Função para eliminar a conta
            break;
        case 9:
            return; // Sai do menu Contas
        default:
            INVALID_OPTION; //Output caso o utilizador escolha uma opção diferente das opções existentes
        }
    }
}

/**
 * Process os pedidos no meu Clientes
 * @param banco
 **/
void processaMenuMovimentos(Banco *b) //Menu movimentos
{
    //Declaração de variaveis
    char id_conta[CODE_SIZE];
    Cliente *cl;
    Cliente *cl2;
    Conta *conta;
    Conta *conta2;
    int opt;
    int id_cliente;
    double montante;
    int cont = 0;
    while (1)
    {
        opt = menuMovimentos();
        switch (opt)
        {
        case 1:
            //Depositar Dinheiro
            if (check_if_bank_empty(b)) //Verificação se o banco está vazio (sem clientes)
            {
                NO_CLIENTS_ERROR; //Erro caso o cliente com o id introduzido não exista
                break;
            }
            id_cliente = pedirInteiro(ASK_CLIENT_ID); //Pede o id do cliente
            if (get_cliente_by_id(b, id_cliente) == NULL) //Verificação se o cliente com o id introduzido é NULL
            {
                NO_SUCH_CLIENT_ERROR(id_cliente); //Erro caso a conta com o código introduzido não exista
                break;
            }
            cl = get_cliente_by_id(b, id_cliente); //Busca o cliente com o id introduzido

            cont = 0; //Contador que verifica quantas contas podem ser criadas
            for (int i = 0; i < MAX_N_ACCOUNTS; i++) //Percorre todos os espaços para contas existentes
            {
                if (cl->contas[i] == NULL) //Caso a conta seja NULL faz
                {
                    cont++; //Incrementa o contador
                }
            }
            if (cont == 3) //caso o contador seja 3 faz
            {
                CLIENT_DONT_HAVE_ACCOUNTS(cl->id_cliente); //Erro o cliente não possui contas
                break;
            }
            memset(id_conta, '\0', CODE_SIZE); //Alocação de memória
            pedirString(id_conta, ASK_ACCOUNT_ID, CODE_SIZE); //Pede o código da conta
            if (get_conta_by_id(id_conta, cl) == NULL) //Verificação se o cliente com o id introduzido é NULL
            {
                NO_SUCH_ACCOUNT_ERROR(id_cliente, id_conta); //Erro caso a conta com o código introduzido não exista
                break;
            }
            conta = get_conta_by_id(id_conta, cl); //Busca a conta do código introduzido

            montante = pedirDouble(ASK_FOR_VALUE); //Pede a montante que o cliente deseja depositar
            depositar(b, cl, conta, montante); //Função para depositar a montante inserida
            break;
        case 2:
            //Levantar Dinheiro
            if (check_if_bank_empty(b)) //Verificação se o banco está vazio (sem clientes)
            {
                NO_CLIENTS_ERROR; //Erro caso o cliente com o id introduzido não exista
                break;
            }
            id_cliente = pedirInteiro(ASK_CLIENT_ID); //Pede o id do cliente
            if (get_cliente_by_id(b, id_cliente) == NULL) //Verificação se o cliente com o id introduzido é NULL
            {
                NO_SUCH_CLIENT_ERROR(id_cliente); //Erro caso a conta com o código introduzido não exista
                break;
            }
            cl = get_cliente_by_id(b, id_cliente); //Busca o cliente com o id introduzido

            cont = 0; //Contador que verifica quantas contas podem ser criadas
            for (int i = 0; i < MAX_N_ACCOUNTS; i++) //Percorre todos os espaços para contas existentes
            {
                if (cl->contas[i] == NULL) //Caso a conta seja NULL faz
                {
                    cont++; //Incrementa o contador
                }
            }
            if (cont == 3) //caso o contador seja 3 faz
            {
                CLIENT_DONT_HAVE_ACCOUNTS(cl->id_cliente); //Erro o cliente não possui contas
                break;
            }

            memset(id_conta, '\0', CODE_SIZE); //Alocação de memória
            pedirString(id_conta, ASK_ACCOUNT_ID, CODE_SIZE); //Pede o código da conta
            if (get_conta_by_id(id_conta, cl) == NULL) //Busca a conta do código introduzido
            {
                NO_SUCH_ACCOUNT_ERROR(id_cliente, id_conta); //Erro caso a conta com o código introduzido não exista
                break;
            }
            conta = get_conta_by_id(id_conta, cl); //Busca a conta do código introduzido

            double montante = pedirDouble(ASK_FOR_VALUE); //Pede a montante que o cliente deseja depositar
            if (conta->saldo < montante) //Caso o saldo da conta seja menor que a montante que se quer levantar faz
            {
                WITHDRAWAL_ERROR_NO_FUNDS(id_cliente, id_conta); //Erro caso não exista saldo suficiente
                break;
            }

            levantar(b, cl, conta, montante); //Função para levantar dinheiro
            break;
        case 3:
            //Transferir Dinheiro
            if (check_if_bank_empty(b)) //Verificação se o banco está vazio (sem clientes)
            {
                NO_CLIENTS_ERROR; //Erro caso o cliente com o id introduzido não exista
                break;
            }
            id_cliente = pedirInteiro(ASK_CLIENT_ID); //Pede o id do cliente
            if (get_cliente_by_id(b, id_cliente) == NULL) //Verificação se o cliente com o id introduzido é NULL
            {
                NO_SUCH_CLIENT_ERROR(id_cliente); //Erro caso a conta com o código introduzido não exista
                break;
            }
            cl = get_cliente_by_id(b, id_cliente); //Busca o cliente com o id introduzido

            cont = 0; //Contador que verifica quantas contas podem ser criadas
            for (int i = 0; i < MAX_N_ACCOUNTS; i++) //Percorre todos os espaços para contas existentes
            {
                if (cl->contas[i] == NULL) //Caso a conta seja NULL faz
                {
                    cont++; //Incrementa o contador
                }
            }
            if (cont == 3) //caso o contador seja 3 faz
            {
                CLIENT_DONT_HAVE_ACCOUNTS(cl->id_cliente); //Erro o cliente não possui contas
                break;
            }

            memset(id_conta, '\0', CODE_SIZE); //Alocação de memória
            pedirString(id_conta, ASK_ACCOUNT_ID, CODE_SIZE); //Pede o código da conta
            if (get_conta_by_id(id_conta, cl) == NULL) //Verificação se o cliente com o id introduzido é NULL
            {
                NO_SUCH_ACCOUNT_ERROR(id_cliente, id_conta); //Erro caso a conta com o código introduzido não exista
                break;
            }
            conta = get_conta_by_id(id_conta, cl); //Busca a conta do código introduzido

            montante = pedirDouble(ASK_FOR_VALUE); //Pede a montante que o cliente deseja depositar
            if (conta->saldo < montante) //Caso o saldo da conta seja menor que a montante que se quer levantar faz
            {
                WITHDRAWAL_ERROR_NO_FUNDS(id_cliente, id_conta); //Erro caso não exista saldo suficiente
                break;
            }
            // conta a depositar
            id_cliente = pedirInteiro(ASK_CLIENT_ID); //Pede o id do cliente
            if (get_cliente_by_id(b, id_cliente) == NULL) //Verificação se o cliente com o id introduzido é NULL
            {
                NO_SUCH_CLIENT_ERROR(id_cliente); //Erro caso a conta com o código introduzido não exista
                break;
            }
            cl2 = get_cliente_by_id(b, id_cliente); //Busca o cliente com o id introduzido

            cont = 0; //Contador que verifica quantas contas podem ser criadas
            for (int i = 0; i < MAX_N_ACCOUNTS; i++) //Percorre todos os espaços para contas existentes
            {
                if (cl2->contas[i] == NULL) //Caso a conta seja NULL faz
                {
                    cont++; //Incrementa o contador
                }
            }
            if (cont == 3) //caso o contador seja 3 faz
            {
                CLIENT_DONT_HAVE_ACCOUNTS(cl2->id_cliente); //Erro o cliente não possui contas
                break;
            }
            memset(id_conta, '\0', CODE_SIZE); //Alocação de memória
            pedirString(id_conta, ASK_ACCOUNT_ID, CODE_SIZE); //Pede o código da conta
            if (get_conta_by_id(id_conta, cl2) == NULL) //Verificação se o cliente com o id introduzido é NULL
            {
                NO_SUCH_ACCOUNT_ERROR(id_cliente, id_conta); //Erro caso a conta com o código introduzido não exista
                break;
            }
            conta2 = get_conta_by_id(id_conta, cl2); //Busca a conta do código introduzido

            transferir(cl, cl2, conta, conta2, montante); //Função para transferir dinheiro
            break;
        case 9:
            return; // Sai do menu Movimentos
        default:
            INVALID_OPTION; //Output caso o utilizador escolha uma opção diferente das opções existentes
        }
    }
}

int main(int argc, char const *argv[])
{
    //Declaração de variaveis
    Banco *b;
    int opt;
    b = iniciarBanco("ATEC Bank");
    while (1)
    {
        opt = menu();
        switch (opt)
        {
        case 1:
            processaMenuClientes(b); //Menu clientes
            break;
        case 2:
            processaMenuContas(b); //Menu contas
            break;
        case 3:
            processaMenuMovimentos(b); //Menu movimentos
            break;
        case 4:
            //Mostrar info banco;
            SHOW_BANK_INFO(b->nome, b->num_clientes, b->num_contas, b->valot_total);
            break;
        case 9:
            free_banco(b); // Liberta recursos
            exit(EXIT_SUCCESS); // Sai da aplicação
        default:
            INVALID_OPTION; //Output caso o utilizador escolha uma opção diferente das opções existentes
            break;
        }
    }

    return EXIT_SUCCESS; //Encerra o programa com sucesso
}