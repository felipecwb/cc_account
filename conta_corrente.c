
// for some cases of simple teste
#define TEST 1

// API implementation of platform environment
#ifdef WIN32
#  include "platform/win.h"
#else
#  include "platform/unix.h"
#endif

#include <stdio.h>
#include "src/screen.c"

/**
 * get the user option
 * @param int *op
 */
void get_option(int *op);


// Where all begins
int main()
{
    int option = 0;

    while (option != 4) {

        screen_menu_print();
        get_option(&option);

        switch(option) {
            case 1:
                screen_add();
                break;
            case 2:
                screen_list();
                break;
            case 3:
                screen_delete();
                break;
            case 4: 
                printf(" - Saindo...\n\n");
                break;
            default:
                printf("***** Opcao desejada nao e valida! *****\n");
                CC_PAUSE
                break;
        }
    }

    CC_PAUSE
    return 0;
}

void get_option(int *op)
{
    fflush(stdin);
    printf("Entre com a opcao digitado: ");
    scanf("%d", op);
}

