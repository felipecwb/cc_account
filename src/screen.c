
#include "screen.h"

#ifdef _CC_SCREEN

#include <stdio.h>

// API implementation of platform environment
#ifdef WIN32
#  include "../platform/win.h"
#else
#  include "../platform/unix.h"
#endif

/**
 * the menu
 */
void screen_menu_print()
{
    // header
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
 * screen to list all
 */
void screen_list()
{
    // header
    CC_CLEAR
    printf("+------------------------------------------------------------------------------+\n");
    printf("|                                                                              |\n");
    printf("|                          Listar Conta Corrente                               |\n");
    printf("|                                                                              |\n");
    printf("+------------------------------------------------------------------------------+\n");

    printf("\n");
    // show the account, first zero
    screen_list_cc(0);

    CC_PAUSE
}

static void screen_list_cc(int index)
{
    // get the specific index of list
    account_t cc = account_list()[index];

    // invalid code, no more accounts
    if (! cc.code) {
        // no accounts in program
        if (index == 0) {
            printf("\nNao ha contas cadastradas\n");
        }

        return;
    }

    // print account
    screen_account_print(&cc);

    // get next
    screen_list_cc(++index);
}

/**
 * add an checking account
 */
void screen_add()
{
    unsigned int code = 1;

    // screen header
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

    while (code != 0) {
        printf("\n==> Informe o numero da nova conta: ");
        scanf("%d", &code);
        
        if (code == 0) {
            break; //loop
        }

        screen_add_cc(code);
    }
}

static void screen_add_cc(unsigned int code)
{
    int result;
    account_t cc;

    cc.code = code;

    fflush(stdin);
    printf("Nome: ");
    scanf("%s[^\n]", cc.name);

    fflush(stdin);
    printf("Email: ");
    scanf("%s[^\n]", cc.email);

    fflush(stdin);
    printf("Endereco - Rua: ");
    scanf("%s[^\n]", cc.address.street);

    fflush(stdin);
    printf("Endereco - Número: ");
    scanf("%d", &cc.address.number);

    fflush(stdin);
    printf("Endereco - Bairro: ");
    scanf("%s[^\n]", cc.address.district);

    fflush(stdin);
    printf("Endereco - Cidade: ");
    scanf("%s[^\n]", cc.address.city);

    fflush(stdin);
    printf("Endereco - Estado (UF): ");
    scanf("%s[^\n]", cc.address.state);

    result = account_add(cc);


    if (result) {
        printf("Conta cadastrada!\n");
    } else {
        printf("Conta NAO cadastrada! Codigo < 100 OU codigo já existe.\n");
    }
}

// to print the header
static void screen_delete_print()
{
    // screen header
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

/**
 * screen to delete
 */
void screen_delete()
{
    unsigned int code = 1;
    account_t *cc;
    char del;

    // header
    screen_delete_print();

    while (code != 0) {
        printf("Codigo da conta a ser excluida: ");
        scanf("%d", &code);

        if (code == 0) {
            break;// getting out
        }

        // find account
        cc = account_find_by_code(code);

        if (cc == NULL) {
            printf("\n*** Codigo não encontrado no cadastro!\n\n");
            continue;
        }

        screen_account_print(cc);

        // confirm delete
        getc(stdin);// fflush does not work here
        printf("Confirmar exclusao desta conta? (s/n): ");
        scanf("%c", &del);

        screen_delete_cc(cc, &del);
    }
}

static void screen_delete_cc(account_t *cc, char *op)
{
    int status;

    switch (*op) {
        case 's':
        case 'S':
            status = account_delete(cc);

            if (status) {
                printf("\n - Conta excluida com sucesso!\n");
            } else {
                printf("\n - Ocorreu algum problema verifique o numero da conta.\n");
            }

            CC_PAUSE

            break;
        case 'n':
        case 'N':
            printf("\n - Conta nao excluida.\n");

            // do you want the delete screen again
            screen_delete_print();

            break;
        default:
            printf("\n ** E Sim ou não!!! Tente de novo.**\n");
            CC_PAUSE
    }
}

/**
 * print the account data
 * @param account_t *cc
 */
static void screen_account_print(account_t *cc)
{
    printf("==> Conta Corrente: %d\n", cc->code);
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

#endif // _CC_SCREEN

