/**
* Author: João Vicente, Raul Gomes, Leandro Santos
* Date: 13Jan2024
* Description: Implementa funções relativas à gestão bancária
* Projeto final de avaliação de módulo
**/

/**
 * Esta biblioteca deve ser complementada com o vosso código
 **/
#ifndef SGB_H
#define SGB_H
/**
 * ######  Mensagens da Biblioteca ######
 **/
//Mensagens de resposta a pedidos
#include <stdio.h>

#define SHOW_BANK_INFO(NOME,NUM_CLIENTES,NUM_CONTAS,SALDO_TOTAL) printf("####  %s  ####\nClientes: %d\nContas: %d\nValor em Cofre: %.2lf €\n",NOME,NUM_CLIENTES,NUM_CONTAS,SALDO_TOTAL)
#define INSERT_CLIENT_SUCESS(ID,NAME) printf("Cliente %d, %s, inserido com sucesso\n",ID,NAME)
#define LIST_USERS_HEADER(TOTAL_CLIENTS) printf("#######  %d Clientes no Banco  #######\n",TOTAL_CLIENTS)
#define LIST_USERS_ITEM(ID,NIF,NAME,NUM_ACCOUNTS,TOTAL_VALUE) printf("%d - %s - %s - Contas: %d - %.2lf€\n", ID,NIF,NAME,NUM_ACCOUNTS,TOTAL_VALUE)
#define CLIENT_INFO(ID,NAME,NIF,NUM_ACCOUNTS,TOTAL_VALUE) printf("###### INFO CLIENTE: %d ######\nNOME: %s\nNIF: %s\nNUM. CONTAS: %d\nPOSIÇÃO INTEGRADA: %.2lf €\n",ID,NAME,NIF,NUM_ACCOUNTS,TOTAL_VALUE)
#define CLIENT_INFO_ACCOUNTS(ID_CONTA,SALDO) printf("  # Conta Num: %s - Saldo: %.2lf €\n",ID_CONTA,SALDO)
#define CLIENT_INFO_MOVEMENTS(ID_MOV,TIPO,VALOR) printf("   -> Movimento %d - %s : %.2lf €\n",ID_MOV,TIPO,VALOR)
#define CLIENT_DELETE_OK(ID) printf("Cliente %d apagado com sucesso\n",ID)
#define CLIENTS_LOOKUP_FOOTER(NUM_CLIENTS_FOUND,TERMO) printf("# Foram encontrados %d clientes com o termo: %s\n",NUM_CLIENTS_FOUND,TERMO)
#define ACCOUNT_CREATION_SUCESS(ID_ACCOUNT,ID_CLIENT) printf("Conta %s criada com sucesso para o cliente %d\n",ID_ACCOUNT,ID_CLIENT)
#define LIST_ACCOUNTS_HEADER(ID_CLIENT,NAME,TOTAL_VALUE) printf("## Cliente %d : %s : %.2lf € ##\n",ID_CLIENT,NAME,TOTAL_VALUE)
#define ACCOUNT_CLOSE_OK(ID_ACCOUNT,ID_CLIENT) printf("Conta %s pertencente ao cliente %d fechada com sucesso",ID_ACCOUNT,ID_CLIENT)
#define DEPOSIT_OK(VALUE,ID_ACCOUNT) printf("Depósito de %.2lf € efetuado com sucesso na conta %s\n",VALUE,ID_ACCOUNT)
#define WITHDRAW_OK(VALUE,ID_ACCOUNT) printf("Levantamento de %.2lf € efetuado com sucesso da conta %s\n",VALUE,ID_ACCOUNT)
#define TRANSFER_OK(VALUE,ID_ORIGIN,ID_DESTINATION) printf("Transferência de %.2lf € efetuada com sucesso. %s -> %s",VALUE,ID_ORIGIN,ID_DESTINATION)
//Mensagens de Erro 
#define INSERT_CLIENT_ERROR_ALREADY_EXISTS(NIF) printf("Erro! Cliente com %s já existe!\n",NIF)
#define INSERT_CLIENT_ERROR_BANK_OVERLOAD printf("Erro! Não há vagas para novos clientes\n")
#define NO_CLIENTS_ERROR printf("Erro! Não existem clientes no banco\n")
#define NO_SUCH_CLIENT_ERROR(ID) printf("Erro! O cliente com o ID %d não existe\n",ID)
#define NO_CLIENTS_FOUND_ERROR(TERMO) printf("Não Foram encontrados clientes através da Pesquisa: %s\n",TERMO)
#define NEW_ACCOUNT_ERROR_CLIENT_OVRELOADED(ID) printf("Erro! O cliente ID %d já não pode possuir mais contas\n",ID)
#define CLIENT_DONT_HAVE_ACCOUNTS(ID) printf("O cliente %d não possui contas\n",ID)
#define NO_SUCH_ACCOUNT_ERROR(ID_CLIENT,ID_ACCOUNT) printf("Erro! O cliente com o ID %d não possuí a conta %s\n",ID_CLIENT,ID_ACCOUNT)
#define WITHDRAWAL_ERROR_NO_FUNDS(ID_CLIENT,ID_ACCOUNT) printf("O cliente %d não possui saldo suficiente na conta %s para a operação solicitada",ID_CLIENT,ID_ACCOUNT)
//Macros com Strings para solicitar dados
#define ASK_NAME "Introduza o nome do Cliente"
#define ASK_NIF "Introduza o NIF do Cliente"
#define ASK_CLIENT_ID "Introduza o ID do cliente"
#define ASK_FIND_TERM "Introduza termo de pesquisa"
#define ASK_ACCOUNT_ID "Introduza o número da conta"
#define ASK_FOR_VALUE "Introduza o valor em €"
//MACROS COM STRINGS do TIPO de Movimentos
#define DEPOSITO_STR "DEPOSITO"
#define LEVANTAMENTO_STR "LEVANTAMENTO"
#define TRANSFERENCIA_STR "TRANSFERÊNCIA"

/**
 * ###### Modelo de Dados######
 **/
#define MAX_NAME 100
#define CODE_SIZE 4
#define MAX_N_MOVEMENTS 10
#define MAX_N_ACCOUNTS 3
#define MAX_N_CLIENTS 20
#define NIF_SIZE 10


/**
 *Estruturas do programa 
 **/
typedef enum tipo
{
    LEVANTAMENTO,
    DEPOSITO,
    TRANSFERENCIA
}TipoT;

typedef struct movimento //estrutura dos movimentos
{
    int id_movimento;
    double valor_movimento;
    TipoT tipo;
}Movimento;

typedef struct conta //estrutura da conta
{
    double saldo;
    int next_id_movimento;
    int n_movimentos;
    char codigo[CODE_SIZE];
    Movimento *movimentos[MAX_N_MOVEMENTS];
}Conta;

typedef struct cliente //estrutura do cliente
{
    char nome_cliente[MAX_NAME];
    int id_cliente;
    double posicao_integrada;
    char nif[NIF_SIZE];
    int num_contas;
    Conta *contas[MAX_N_ACCOUNTS];
}Cliente;

typedef struct banco //estrutura do banco
{
    int next_id_cliente;
    char nome[MAX_NAME];
    int num_clientes;
    double valot_total;
    int num_contas;
    Cliente *clientes[MAX_N_CLIENTS];
}Banco;



/**
 * !###### Funções Visíveis no exterior da biblioteca######
 **/

/**
 * Incicia a estrutura Banco
 * @param nome do Banco
 * @return ponteiro para banco criado
*/
Banco *iniciarBanco(char* nome);


/**
 * Liberta todos os recursos associados ao Banco
 * @param b Banco a ser libertado
*/
void free_banco(Banco *b);


//TODO Outras funções publicas
/**
 * Vai buscar a primeira posição dos clientes vazia
 * @param b faz a ligação com a estrutura clientes
*/
int get_first_free_slot_cliente(Banco *b);

/**
 * Vai buscar a primeira posição das contas vazia
 * @param b faz a ligação com a estrutura contas
*/
int get_first_free_slot_conta(Cliente *cl);

/**
 * Insere novo cliente
 *@param  
*/
void inserir_cliente(Banco *b, char *nome, char *nif);

/**
 * Verifica se o banco está cheio
 * @param b Banco
*/
int check_if_bank_full(Banco *b);

/**
 * Verifica se o banco está vazio
 * @param b Banco
*/
int check_if_bank_empty(Banco *b);

/**
 * Lista todos os clientes do banco
 * @param b Banco
*/
void listar_clientes(Banco *b);

/**
 * Lista todas as contas do cliente com o id pedido ao utilizador
 * @param b Banco
 * @param id_cliente id do cliente para acessar as contas
*/
void listar_contas(Banco *b, int id_cliente);

/**
 * Ordena os cliente por ordem alfabetica
 * @param b Banco
*/
void sort_clientes(Banco *b);

/**
 * Ordena as contas por ordem alfabetica
 * @param b Banco
*/
void sort_contas(Banco *b);

/**
 * Troca os valores das posição fornecidas pelos apontadores
 * @param c1 Apontador da primeira posição do cliente
 * @param c1 Apontador da segunda posição do cliente ou seja a posição seguinte à anterior
*/
void trocar_cl(Cliente *c1, Cliente *c2);

/**
 * Troca os valores das posição fornecidas pelos apontadores
 * @param c1 Apontador da primeira posição da conta
 * @param c1 Apontador da segunda posição da conta ou seja a posição seguinte à anterior
*/
void trocar_acc(Conta *c1, Conta *c2);

/**
 * Mostra o cliente com o id fornecido
 * @param b Banco
 * @param cl Apontador da posição do id fornecido pelo cliente
*/
int mostrar_cliente(Banco *b, Cliente *cl);

/**
 * Mostra a conta com o id e o codigo da conta fornecidos 
 * @param b Banco
 * @param cl Apontador da posição do id do cliente 
 * @param conta Apontador da posição do codigo da conta
*/
int mostrar_conta(Banco *b, int id, Cliente *cl, Conta *conta);

/**
 * Insere um nova conta no cliente
 * @param b Banco
 * @param id_cliente é o id do cliente
 * @param codigo é o codigo da conta
*/
void inserir_conta(Banco *b, int id_cliente, char *codigo);

/**
 * Apaga o cliente do banco
 * @param b Banco
 * @param cl Apontador da posição do id do cliente
*/
void apagar_cliente(Banco *b, Cliente *cl);

/**
 * Procura dentro do cliente o termo fornecido
 * @param b Banco
 * @param pesquisa O termo a ser pesquisado no cliente
*/
void procurar_cliente(Banco *b, char *pesquisa);

/**
 * Deposita um montante numa conta do cliente 
 * @param b Banco
 * @param id_cl Apontador da posição do id do cliente 
 * @param id_c Apontador da posição do codigo da conta
 * @param montante montante a adicionar
*/
void depositar(Banco *b, Cliente *id_cl, Conta *id_c, double montante);


int get_first_free_slot_moviemntos(Conta *c);

Conta *get_conta_by_id(char *id, Cliente *cl );

Cliente *get_cliente_by_id(Banco *b, int id);

/**
 * Deposita um montante numa conta do cliente 
 * @param b Banco
 * @param id_cl Apontador da posição do id do cliente 
 * @param id_c Apontador da posição do codigo da conta
 * @param montante montante a levantar
*/
void levantar(Banco *b, Cliente *id_cl, Conta *id_c, double montante);

/**
 * Deposita um montante numa conta do cliente 
 * @param b Banco
 * @param id_cl Apontador da posição do id do primeiro cliente 
 * @param id_c Apontador da posição do codigo da conta do segundo cliente
 * @param id_cl2 Apontador da posição do id do segundo cliente 
 * @param id_c2 Apontador da posição do codigo da conta do segundo cliente
 * @param montante montante a adicionar
*/
void transferir(Cliente *id_cl, Cliente *id_cl2, Conta *id_c, Conta *id_c2, double montante);

/**
 * Elimina a conta de um cliente
 * @param b Banco
 * @param id_cliente Apontador da posição do id do cliente 
 * @param id_conta Apontador da posição do codigo da conta
*/
void eliminar_conta(Banco *b, Cliente *id_cliente, Conta *id_conta);

#endif