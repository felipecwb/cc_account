/*
 *
 * autor: Felipe Aparecido Francisco
 * email: felipefrancisco.cwb@gmail.com
 * matricula: 1512914
 * 
 * curso: Analise e desenvolvimento de sistemas
 * turma: J
 *
 * Screens
 *
 */

#ifndef _CC_SCREEN
#define _CC_SCREEN 1

#include "account.c"

/**
 * screen view menu options
 * manage the things with non-magic
 *
 * @return void
 */
void screen_menu();

static void screen_menu_print();

/**
 * screen view the list
 * @return void
 */
void screen_list();

/**
 * screen to add more one checking account
 * @param int header
 * @return void
 */
void screen_add(int header);

/**
 * print the checking account
 * @param account_t *cc
 * @return void
 */
static void screen_account_print(account_t *cc);

/**
 * screen to see and choose to delete an account
 * @return void
 */
void screen_delete(int header);

#endif //_CC_SCREEN

