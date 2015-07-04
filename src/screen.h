
#ifndef _CC_SCREEN
#define _CC_SCREEN 1

#include "account.c"

/**
 * Print the first screen
 */
void screen_menu_print();

/**
 * screen view the list
 * @return void
 */
void screen_list();

static void screen_list_cc(int index);

/**
 * screen to add more one checking account
 * @param int header
 * @return void
 */
void screen_add();

static void screen_add_cc(unsigned int code);

/**
 * screen to see and choose to delete an account
 * @return void
 */
void screen_delete();

static void screen_delete_print();
static void screen_delete_cc(account_t *cc, char *op);

/**
 * print the checking account
 * @param account_t *cc
 * @return void
 */
static void screen_account_print(account_t *cc);

#endif //_CC_SCREEN

