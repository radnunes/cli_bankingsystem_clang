/**
 * Author: Raul Gomes, João Vicente e Leandro Santos
 * Date: 13Jan2024
 * Description: sgb.c
 **/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "ui.h"
#include "sgb.h"

// TODO: Inserir eventuais defines, ou declaração das funções internas consoante necessário
#define FALSE 0
#define TRUE 1

/**
 * Faz a troca dos valores para o sort cliente
 **/
void trocar_cl(Cliente *c1, Cliente *c2)
{
    Cliente aux = *c1;
    *c1 = *c2;
    *c2 = aux;
}

/**
 * Faz a troca dos valores para o sort conta
 **/
void trocar_acc(Conta *c1, Conta *c2)
{
    Conta aux = *c1;
    *c1 = *c2;
    *c2 = aux;
}

/**
 * Faz o sort alfabeticamente dos clientes
 **/
void sort_clientes(Banco *b)
{
    int trocado;
    do
    {
        trocado = FALSE;
        for (int i = 0; i <= b->num_clientes - 2; i++)
        {
            if (strcmp(b->clientes[i]->nome_cliente, b->clientes[i + 1]->nome_cliente) > 0)
            {
                trocar_cl(b->clientes[i], b->clientes[i + 1]);
                trocado = TRUE;
            }
        }
    } while (trocado);
}

/**
 * Faz o sort alfabeticamente das contas
 **/
void sort_contas(Banco *b)
{
    int trocado;
    do
    {
        trocado = FALSE;
        for (int i = 0; i <= b->num_clientes - 2; i++)
        {
            for (int j = 0; j <= b->clientes[i]->num_contas - 2; j++)
            {
                if (strcmp(b->clientes[i]->contas[j]->codigo, b->clientes[i]->contas[j + 1]->codigo) > 0)
                {
                    trocar_acc(b->clientes[i]->contas[j], b->clientes[i]->contas[j + 1]);
                    trocado = TRUE;
                }
            }
        }
    } while (trocado);
}

/**
 * Inicia o banco
 **/
Banco *iniciarBanco(char *nome)
{
    Banco *b;
    b = malloc(sizeof(Banco));
    memset(b->nome, '\0', MAX_NAME);
    strcpy(b->nome, nome);
    //inicializa as variaveis do banco
    b->valot_total = 0.0;
    b->num_clientes = 0;
    b->num_contas = 0;
    b->next_id_cliente = 1;
    //inicializa todos os clientes como NULL
    for (int i = 0; i < MAX_N_CLIENTS; i++)
    {
        b->clientes[i] = NULL;
    }

    return b;
}

/**
 * Solta a memoria do Banco
 **/
void free_banco(Banco *b)
{
    // TODO: Libertar a memória alocada à estrutura anco
    for (int i = 0; i < MAX_N_CLIENTS; i++)
    {
        if (b->clientes[i] != NULL)
        {
            for (int j = 0; j < MAX_N_ACCOUNTS; j++)
            {
                Conta *c = b->clientes[i]->contas[j];

                if (c != NULL)
                {
                    for (int l = 0; l < MAX_N_MOVEMENTS; l++)
                    {
                        Movimento *m = b->clientes[i]->contas[j]->movimentos[l];
                        free(m);
                    }
                    free(c);
                }
            }
            free(b->clientes[i]);
        }
    }

    free(b);
}

/**
 * Dá o primeiro espaço livre para um novo cliente
 **/
int get_first_free_slot_cliente(Banco *b)
{
    for (int i = 0; i < MAX_N_CLIENTS; i++)
    {
        if (b->clientes[i] == NULL)
        {
            // Esta é a free slot a usar
            return i;
        }
    }
    return -1;
}

/**
 * Dá o primeiro espaço livre para uma nova conta
 **/
int get_first_free_slot_conta(Cliente *cl)
{
    for (int i = 0; i < MAX_N_ACCOUNTS; i++)
    {
        if (cl->contas[i] == NULL)
        {
            return i;
        }
    }
    return -1;
}

/**
 * Verifica se o banco está cheio
 **/
int check_if_bank_full(Banco *b)
{
    if (b->num_clientes == MAX_N_CLIENTS)
    {
        // se não há espaço para novos clientes -> dar erro
        INSERT_CLIENT_ERROR_BANK_OVERLOAD;
        return 1;
    }
    return 0;
}

/**
 * Verifica se o banco está vazio
 **/
int check_if_bank_empty(Banco *b)
{
    if (b->num_clientes == 0)
    {
        return 1;
    }
    return 0;
}

/*=====================Cliente=====================*/
/**
 * Insere um cliente
 **/
void inserir_cliente(Banco *b, char *nome, char *nif)
{
    //Dá a primeira posição livre no banco
    int index = get_first_free_slot_cliente(b);
    //Faz a alocação de memória
    Cliente *cl = malloc(sizeof(Cliente));

    //dá os valores inseridos pelo utilizador ao cliente no novo
    memset(cl->nome_cliente, '\0', MAX_NAME);
    memset(cl->nif, '\0', NIF_SIZE);
    strcpy(cl->nome_cliente, nome);
    strcpy(cl->nif, nif);
    cl->num_contas = 0;
    cl->posicao_integrada = 0;
    //faz a inicialização das contas do cliente como NULL
    for (int i = 0; i < MAX_N_ACCOUNTS; i++)
    {
        cl->contas[i] = NULL;
    }
    //verifica-se o nif já existe
    for (int i = 0; i < MAX_N_CLIENTS; i++)
    {
        if (b->clientes[i] == NULL)
        {
            continue;
        }

        if (strcmp(b->clientes[i]->nif, nif) == 0)
        {
            INSERT_CLIENT_ERROR_ALREADY_EXISTS(nif);
            free(cl);

            return;
        }
    }
    //altera o resto dos valores
    b->clientes[index] = cl;
    cl->id_cliente = b->next_id_cliente;
    b->next_id_cliente++;
    b->num_clientes++;
    INSERT_CLIENT_SUCESS(cl->id_cliente, cl->nome_cliente);
}

/**
 * Lista os clientes
 **/
void listar_clientes(Banco *b)
{
    //verifica se existem clientes
    if (b->num_clientes == 0)
    {
        NO_CLIENTS_ERROR;
        return;
    }
    LIST_USERS_HEADER(b->num_clientes);
    //mostra todos os clientes existentes
    for (int i = 0; i < MAX_N_CLIENTS; i++)
    {
        if (b->clientes[i] == NULL)
        {
            continue;
        }
        LIST_USERS_ITEM(b->clientes[i]->id_cliente, b->clientes[i]->nif, b->clientes[i]->nome_cliente, b->clientes[i]->num_contas, b->clientes[i]->posicao_integrada);
    }
}

/**
 * Mostra o cliente com o id que foi pedido ao utilizador
 **/
int mostrar_cliente(Banco *b, Cliente *cl)
{
    for (int i = 0; i < b->num_clientes; i++)
    {
        //verifica se o id do cliente é igual ao fornecido
        if (b->clientes[i]->id_cliente == cl->id_cliente)
        {
            //mostra a informação do cliente
            CLIENT_INFO(b->clientes[i]->id_cliente, b->clientes[i]->nome_cliente, b->clientes[i]->nif, b->clientes[i]->num_contas, b->clientes[i]->posicao_integrada);
            //verifica se existem contas
            if (b->clientes[i]->num_contas > 0)
            {
                for (int j = 0; j < b->clientes[i]->num_contas; j++)
                {
                    //mostra a informação das contas
                    CLIENT_INFO_ACCOUNTS(b->clientes[i]->contas[j]->codigo, b->clientes[i]->contas[j]->saldo);
                    for (int y = b->clientes[i]->contas[j]->n_movimentos - 1; y >= 0; y--)
                    {
                        int check = b->clientes[i]->contas[j]->movimentos[y]->tipo;
                        //faz um switch que verifica qual o tipo de movimento e mostra as informações dos movimentos
                        switch (check)
                        {
                        case 0:
                            CLIENT_INFO_MOVEMENTS(b->clientes[i]->contas[j]->movimentos[y]->id_movimento, LEVANTAMENTO_STR, b->clientes[i]->contas[j]->movimentos[y]->valor_movimento);
                            break;
                        case 1:
                            CLIENT_INFO_MOVEMENTS(b->clientes[i]->contas[j]->movimentos[y]->id_movimento, DEPOSITO_STR, b->clientes[i]->contas[j]->movimentos[y]->valor_movimento);
                            break;
                        case 2:
                            CLIENT_INFO_MOVEMENTS(b->clientes[i]->contas[j]->movimentos[y]->id_movimento, TRANSFERENCIA_STR, b->clientes[i]->contas[j]->movimentos[y]->valor_movimento);
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
            return 1;
        }
    }

    NO_SUCH_CLIENT_ERROR(cl->id_cliente);
    return 0;
}

/**
 * Apaga o cliente com o id fornecido pelo utlizador
 **/
void apagar_cliente(Banco *b, Cliente *cl)
{
    // pedir o id, se nao houver erro NO_SUCH_CLIENTE_ERROR(ID)
    // se existir, apagar o cliente e usar CLIENTE_DELETE_OK(ID)

    // Apagar as contas do cliente

    for (int j = 0; j < MAX_N_ACCOUNTS; j++)
    {
        if (cl->contas[j])
        {
            for (int y = 0; y < MAX_N_MOVEMENTS; y++)
            {
                //solta a memoria dos movimentos e passa a NULL
                free(cl->contas[j]->movimentos[y]);
                cl->contas[j]->movimentos[y] = NULL;
            }
            //solta a memoria das contas e passa a NULL
            free(cl->contas[j]);
            cl->contas[j] = NULL;
        }
    }
    
    b->valot_total -= cl->posicao_integrada;
    b->num_clientes--;
    CLIENT_DELETE_OK(cl->id_cliente);
    //solta a memoria dos clientes e passa a NULL
    free(cl);
    for (int i = 0; i < MAX_N_CLIENTS; i++)
    {
        if (b->clientes[i] == cl)
        {
            b->clientes[i] = NULL;
            break;
        }
    }
    return;
}

/**
 * Procura dentro do cliente o termo que foi fornecido pelo cliente
 **/
void procurar_cliente(Banco *b, char *pesquisa)
{
    int cont = 0;
    //verifica se o termo existe no cliente
    for (int i = 0; i < MAX_N_CLIENTS; i++)
    {
        if (b->clientes[i] == NULL)
        {
            continue;
        }
        if (strstr(b->clientes[i]->nome_cliente, pesquisa) != NULL)
        {
            LIST_USERS_ITEM(b->clientes[i]->id_cliente, b->clientes[i]->nif, b->clientes[i]->nome_cliente, b->clientes[i]->num_contas, b->clientes[i]->posicao_integrada);
            cont++;
        }
    }
    if (cont != 0)
    {
        CLIENTS_LOOKUP_FOOTER(cont, pesquisa);
        return;
    }
    //senão encontrar mostra a mensagem de erro
    NO_CLIENTS_FOUND_ERROR(pesquisa);
    return;
}

/*=====================Conta===================*/
/**
 * Insere uma nova conta
 **/
void inserir_conta(Banco *b, int id_cliente, char *codigo)
{

    for (int i = 0; i < b->num_clientes; i++)
    {
        //verifica se  id existe
        if (b->clientes[i]->id_cliente == id_cliente)
        {
            //procura o primeiro espaço vazio para uma nova conta
            int index = get_first_free_slot_conta(b->clientes[i]);
            //se existir cria uma nova conta
            if (index != -1)
            {
                Conta *c = malloc(sizeof(Conta));
                b->clientes[i]->contas[index] = c;

                memset(c->codigo, '\0', CODE_SIZE);
                strcpy(c->codigo, codigo);

                c->saldo = 0;
                c->n_movimentos = 0;
                c->next_id_movimento = 1;
                for (int i = 0; i < MAX_N_MOVEMENTS; i++)
                {
                    c->movimentos[i] = NULL;
                }

                b->clientes[i]->num_contas++;

                break;
            }
        }
    }
    b->num_contas++;
    ACCOUNT_CREATION_SUCESS(codigo, id_cliente);
    return;
}

/**
 * Lista todas as contas do cliente
 **/
void listar_contas(Banco *b, int id_cliente)
{
    int cliente_encontrado = 0;

    for (int i = 0; i < b->num_clientes; i++)
    {
        //verifica se o id do cliente existe
        if (b->clientes[i]->id_cliente == id_cliente)
        {
            cliente_encontrado = 1;
            //verifica se o cliente tem contas
            if (b->clientes[i]->num_contas == 0)
            {
                CLIENT_DONT_HAVE_ACCOUNTS(id_cliente);
                continue;
            }
            else
            {
                LIST_ACCOUNTS_HEADER(b->clientes[i]->id_cliente, b->clientes[i]->nome_cliente, b->clientes[i]->posicao_integrada);
                for (int j = 0; j < b->clientes[i]->num_contas; j++)
                {
                    //se o cliente tiver contas mostra a(s) conta(s) e os seus movimento(s)
                    CLIENT_INFO_ACCOUNTS(b->clientes[i]->contas[j]->codigo, b->clientes[i]->contas[j]->saldo);
                    for (int y = b->clientes[i]->contas[j]->n_movimentos - 1; y >= 0; y--)
                    {
                        int check = b->clientes[i]->contas[j]->movimentos[y]->tipo;
                        switch (check)
                        {
                        case 0:
                            CLIENT_INFO_MOVEMENTS(b->clientes[i]->contas[j]->movimentos[y]->id_movimento, LEVANTAMENTO_STR, b->clientes[i]->contas[j]->movimentos[y]->valor_movimento);
                            break;
                        case 1:
                            CLIENT_INFO_MOVEMENTS(b->clientes[i]->contas[j]->movimentos[y]->id_movimento, DEPOSITO_STR, b->clientes[i]->contas[j]->movimentos[y]->valor_movimento);
                            break;
                        case 2:
                            CLIENT_INFO_MOVEMENTS(b->clientes[i]->contas[j]->movimentos[y]->id_movimento, TRANSFERENCIA_STR, b->clientes[i]->contas[j]->movimentos[y]->valor_movimento);
                            break;
                        default:
                            break;
                        }
                    }
                }
                continue;
            }
        }
    }
    //senão encontrar cliente nenhum mostra a mensagem de erro
    if (!cliente_encontrado)
    {
        NO_SUCH_CLIENT_ERROR(id_cliente);
    }
}

/**
 * Lista um conta especifica do cliente
 **/
int mostrar_conta(Banco *b, int id, Cliente *cliente, Conta *conta)
{
    for (int i = 0; i < b->num_clientes; i++)
    {
        //verifica se o id existe
        if (b->clientes[i]->id_cliente == cliente->id_cliente)
        {
            LIST_ACCOUNTS_HEADER(b->clientes[i]->id_cliente, b->clientes[i]->nome_cliente, b->clientes[i]->posicao_integrada);
            //verifica se tem contas
            if (cliente->num_contas > 0)
            {
                for (int j = 0; j < cliente->num_contas; j++)
                {
                    //verifica se o codigo da conta existe
                    if (strcmp(cliente->contas[j]->codigo, conta->codigo) == 0)
                    {
                        CLIENT_INFO_ACCOUNTS(cliente->contas[j]->codigo, cliente->contas[j]->saldo);
                        for (int y = cliente->contas[j]->n_movimentos - 1; y >= 0; y--)
                        {
                            // mostra os movimentos da conta
                            int check = cliente->contas[j]->movimentos[y]->tipo;
                            switch (check)
                            {
                            case 0:
                                CLIENT_INFO_MOVEMENTS(cliente->contas[j]->movimentos[y]->id_movimento, LEVANTAMENTO_STR, cliente->contas[j]->movimentos[y]->valor_movimento);
                                break;
                            case 1:
                                CLIENT_INFO_MOVEMENTS(cliente->contas[j]->movimentos[y]->id_movimento, DEPOSITO_STR, cliente->contas[j]->movimentos[y]->valor_movimento);
                                break;
                            case 2:
                                CLIENT_INFO_MOVEMENTS(cliente->contas[j]->movimentos[y]->id_movimento, TRANSFERENCIA_STR, cliente->contas[j]->movimentos[y]->valor_movimento);
                                break;
                            default:
                                break;
                            }
                        }
                    }
                }
            }
            else
            {
                CLIENT_DONT_HAVE_ACCOUNTS(cliente->id_cliente);
            }

            return 1;
        }
    }

    NO_SUCH_CLIENT_ERROR(cliente->id_cliente);
    return 0;
}

/**
 * Cria um apontador através do id do cliente fornecido pelo utilizador
 **/
Cliente *get_cliente_by_id(Banco *b, int id)
{
    for (int i = 0; i < MAX_N_CLIENTS; i++)
    {

        if (b->clientes[i] == NULL)
        {
            continue;
        }
        //verifica se existe o id e retorna um apontador da posição do cliente
        if (b->clientes[i]->id_cliente == id)
        {
            return b->clientes[i];
        }
    }
    return NULL;
}

/*=====================<Movimentos>=====================*/
/**
 * Cria um apontador através do codigo da conta fornecido pelo cliente
 **/
Conta *get_conta_by_id(char *id, Cliente *cl)
{
    for (int i = 0; i < MAX_N_ACCOUNTS; i++)
    {

        if (cl->contas[i] == NULL)
        {
            continue;
        }
        //verifica se existe o id e retorna um apontador da posição da conta
        if (strcmp(cl->contas[i]->codigo, id) == 0)
        {
            return cl->contas[i];
        }
    }
    return NULL;
}

/**
 * Dá o primeiro espaço vazio dos movimentos
 **/
int get_first_free_slot_movimentos(Conta *c)
{
    for (int i = 0; i < MAX_N_MOVEMENTS; i++)
    {
        if (c->movimentos[i] == NULL)
        {
            return i;
        }
    }
    return -1;
}

/**
 * Faz o deposito na conta
 **/
void depositar(Banco *b, Cliente *id_cl, Conta *id_c, double montante)
{
    
    Movimento *m;

    m = malloc(sizeof(Movimento));

    int index = get_first_free_slot_movimentos(id_c);

    id_c->movimentos[index] = m;
    id_c->n_movimentos++;

    m->id_movimento = id_c->next_id_movimento;
    m->valor_movimento = montante;
    m->tipo = DEPOSITO;
    id_c->saldo += montante;
    id_cl->posicao_integrada += montante;
    b->valot_total += montante;
    char code_c[CODE_SIZE];
    strcpy(code_c, id_c->codigo);
    DEPOSIT_OK(montante, code_c);

    return;
}

/**
 * Faz o levantamento na conta
 **/
void levantar(Banco *b, Cliente *id_cl, Conta *id_c, double montante)
{
    Movimento *m;
    m = malloc(sizeof(Movimento));
    int index = get_first_free_slot_movimentos(id_c);

    id_c->movimentos[index] = m;
    id_c->n_movimentos++;
    id_c->next_id_movimento++;
    m->id_movimento = id_c->next_id_movimento;
    m->valor_movimento = montante - (montante * 2);
    m->tipo = LEVANTAMENTO;
    id_c->saldo -= montante;
    id_cl->posicao_integrada -= montante;
    b->valot_total -= montante;
    char code_c[CODE_SIZE];
    strcpy(code_c, id_c->codigo);
    WITHDRAW_OK(montante, code_c);
}

/**
 * Transfere um montante de uma conta para a outra
 **/
void transferir(Cliente *id_cl, Cliente *id_cl2, Conta *id_c, Conta *id_c2, double montante)
{
    Movimento *m;
    m = malloc(sizeof(Movimento));
    int index = get_first_free_slot_movimentos(id_c);
    int index2 = get_first_free_slot_movimentos(id_c2);

    id_c->movimentos[index] = m;
    id_c->n_movimentos++;
    id_c->next_id_movimento++;
    m->id_movimento = id_c->next_id_movimento;
    m->valor_movimento = montante - (montante * 2);
    m->tipo = TRANSFERENCIA;
    id_c->saldo -= montante;
    id_cl->posicao_integrada -= montante;
    char code_c[CODE_SIZE];
    strcpy(code_c, id_c->codigo);

    Movimento *m2;
    m2 = malloc(sizeof(Movimento));
    id_c2->movimentos[index2] = m2;
    id_c2->n_movimentos++;
    id_c2->next_id_movimento++;
    m2->id_movimento = id_c2->next_id_movimento;
    m2->valor_movimento = montante;
    m2->tipo = TRANSFERENCIA;
    id_c2->saldo += montante;
    id_cl2->posicao_integrada += montante;
    char code_c2[CODE_SIZE];
    strcpy(code_c2, id_c2->codigo);
    TRANSFER_OK(montante, code_c, code_c2);
}

/**
 * Elimina uma conta especifica
 **/
void eliminar_conta(Banco *b, Cliente *id_cliente, Conta *id_conta)
{
    for (int i = 0; i < MAX_N_CLIENTS; i++)
    {
        //verifica se o id existe
        if (b->clientes[i]->id_cliente == id_cliente->id_cliente)
        {
            for (int j = 0; j < MAX_N_ACCOUNTS; j++)
            {
                //verifica se o codigo existe
                if (strcmp(b->clientes[i]->contas[j]->codigo, id_conta->codigo) == 0)
                {
                    //apaga a conta
                    free(b->clientes[i]->contas[j]);
                    b->clientes[i]->contas[j] = NULL;
                    ACCOUNT_CLOSE_OK(id_conta->codigo, id_cliente->id_cliente);
                    b->clientes[i]->num_contas--;
                    b->num_contas--;
                    return;
                }
            }
        }
    }
}