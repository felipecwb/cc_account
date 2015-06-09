
#include "screen.h"

#include <stdio.h>
#include <locale.h>

// API implementation of platform environment
#ifdef WIN32
#  include "../platform/win.h"
#else
#  include "../platform/unix.h"
#endif

void screen_menu()
{
    // support for UTF8 characters
    setlocale(LC_ALL, "");

    screen_menu_print();

    int option;

    fflush(stdin);
    printf("Entre com a opção digitado: ");
    scanf("%d", &option);

    getc(stdin);

    switch(option) {
        case 1:
            screen_add(1);
            break;
        case 2:
            screen_list();
            break;
        case 3:
            screen_delete(1);
            break;
        case 4:
            return; // getting out now guys
            break;
        default:
            printf("***** Opção desejada não é válida! *****\n");
            CC_PAUSE
            break;
    }

    // call me again haha
    screen_menu();
}

/**
 * screen to list all
 */
void screen_list()
{
    CC_CLEAR

    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    printf("|                          Listar Conta Corrente                               |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");

    account_t *list;
    list = account_list();

    int i;
    for (i = 0; i < QTD_ACCOUNTS; i++) {
        if (! (list + i)->code) {
            if (i == 0) {
                printf("\nNão há contas cadastradas\n");
            }
 
            break;
        }

        screen_account_print(list + i);
    }

    CC_PAUSE
}

/**
 * add an checking account
 */
void screen_add(int header)
{
    if (header) {
        CC_CLEAR

        printf("+------------------------------------------------------------------------------+\n");
        printf("|                                                                              |\n");
        printf("|                          Cadastrar Conta Corrente                            |\n");
        printf("|                                                                              |\n");
        printf("+------------------------------------------------------------------------------+\n");
        printf("|                                                                              |\n");
        printf("|            Entre com o numero de conta ou 0 para encerrar                    |\n");
        printf("|                                                                              |\n");
        printf("+------------------------------------------------------------------------------+\n");
    }

    unsigned int code;

    printf("\n==> Informe o numero da nova conta: ");
    scanf("%d", &code);

    if (code == 0) {
        return; // finish
    }

    // add proccess
    account_t cc;
    cc.code = code;

    fflush(stdin);
    printf("Nome: ");
    scanf("%s[^\n]", cc.name);

    fflush(stdin);
    printf("Email: ");
    scanf("%s[^\n]", cc.email);

    fflush(stdin);
    printf("Endereço - Rua: ");
    scanf("%s[^\n]", cc.address.street);

    fflush(stdin);
    printf("Endereço - Número: ");
    scanf("%d", &cc.address.number);

    fflush(stdin);
    printf("Endereço - Bairro: ");
    scanf("%s[^\n]", cc.address.district);

    fflush(stdin);
    printf("Endereço - Cidade: ");
    scanf("%s[^\n]", cc.address.city);

    fflush(stdin);
    printf("Endereço - Estado (UF): ");
    scanf("%s[^\n]", cc.address.state);

    printf("\n");

    int result = account_add(cc);

    if (result) {
        printf("Conta cadastrada!\n");
    } else {
        printf("Conta NÃO cadastrada! Código < 100 OU codigo já existe.\n");
    }

    screen_add(0);
}

/**
 * screen to delete
 */
void screen_delete(int header)
{
    if (header) {
        CC_CLEAR

        printf("+------------------------------------------------------------------------------+\n");
        printf("|                                                                              |\n");
        printf("|                         Excluir Conta Corrente                               |\n");
        printf("|                                                                              |\n");
        printf("+------------------------------------------------------------------------------+\n");
        printf("|                                                                              |\n");
        printf("|            Entre com o numero de conta ou 0 para encerrar                    |\n");
        printf("|                                                                              |\n");
        printf("+------------------------------------------------------------------------------+\n");
    }

    unsigned int code;

    printf("Código da conta a ser excluida: ");
    scanf("%d", &code);

    if (code == 0) {
        return; // bye bye guys
    }

    account_t *cc = account_find_by_code(code);

    if (cc == NULL) {
        printf("\n*** Código não encontrado no cadastro!\n\n");
        return screen_delete(0);
    }

    screen_account_print(cc);

    char del;

    getc(stdin);// fflush does not work here
    printf("Confirmar exclusão desta conta? (s/n): ");
    scanf("%c", &del);

    if (del == 's' || del == 'S') {
        int status = account_delete(cc);

        if (status) {
            printf("\n - Conta excluida com sucesso!\n");
        } else {
            printf("\n - Ocorreu algum problema verifique o numero da conta.\n");
        }

    } else if (del == 'n' || del == 'N') {

        printf("\n - Conta não excluida.\n");
        CC_PAUSE

        return screen_delete(1);
    } else {
        // eastern egg
        printf("\n ** É Sim ou não!!! Tente de novo.**\n");
    }

    CC_PAUSE
    screen_delete(0);
}

/**
 * the menu
 */
void screen_menu_print()
{
    CC_CLEAR

    printf("+------------------------------------------------------------------------------+\n");
    printf("|        ccccccccccccccc    ccccccccccccccc                                    |\n");
    printf("|       ccccccccccccccc    ccccccccccccccc                                     |\n");
    printf("|       cccc               cccc                                                |\n");
    printf("|       cccc               cccc                                                |\n");
    printf("|       cccc               cccc                                                |\n");
    printf("|       ccccccccccccccc    ccccccccccccccc       TTTTT  OOO  TTTTT AAAAA L     |\n");
    printf("|        ccccccccccccccc    ccccccccccccccc        T   O   O   T   A   A L     |\n");
    printf("|                                                  T   O   O   T   A A A L     |\n");
    printf("|                                                  T    OOO    T   A   A LLLL  |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    printf("|                       1 - Cadastrar Conta Corrente                           |\n");
    printf("|                       2 - Listar Conta Corrente                              |\n");
    printf("|                       3 - Excluir Conta Corrente                             |\n");
    printf("|                                                                              |\n");
    printf("|                       4 - Sair                                               |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");
}

/**
 * print the account data
 * @param account_t *cc
 */
static void screen_account_print(account_t *cc)
{
    printf("\n==> Conta Corrente: %d\n", cc->code);
    printf("Nome: %s\n", cc->name);
    printf("Email: %s\n", cc->email);
    printf("Endereço: \n");
    printf("|- Rua: %s\n", cc->address.street);
    printf("|- Número: %d\n", cc->address.number);
    printf("|- Bairro: %s\n", cc->address.district);
    printf("|- Cidade: %s\n", cc->address.city);
    printf("|- Estado: %s\n", cc->address.state);
    printf("\n");
}


