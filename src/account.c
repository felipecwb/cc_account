
#include "account.h"

#ifdef _CC_ACCOUNT

#include <stdio.h>

/**
 * LIST
 */
account_t *account_list()
{
    return cc_storage;
}

/**
 * FIND BY ID
 */
account_t *account_find_by_code(unsigned int code)
{
    int i;
    for (i = 0; i < QTD_ACCOUNTS; i++) {
        if (! cc_storage[i].code) {
            return NULL;
        }

        if (cc_storage[i].code == code) {
            return &cc_storage[i];
        }
    }

    return NULL;
}

/**
 * ADD
 */
int account_add(account_t cc)
{
    // code less than 100
    if (cc.code < 100) {
        return 0;
    }

    // storage full
    if (cc_storage_point > QTD_ACCOUNTS) {
        return 0;
    }

    // code already exists
    if (account_find_by_code(cc.code) != NULL) {
        return 0;
    }

    cc_storage[++cc_storage_point] = cc;

    return 1;
}

/**
 * DELETE
 */
int account_delete(account_t *cc)
{
    if (account_find_by_code(cc->code) == NULL) {
        return 0;
    }

    int i;
    for (i = 0; i < QTD_ACCOUNTS; i++) {
         if (! cc_storage[i].code) {
             return 0;
         }

        if (cc_storage[i].code == cc->code) {
            break;
        }
    }

    // swap
    cc_storage[i] = cc_storage[cc_storage_point];
    // hackround for stop and hide the suppost deleted
    cc_storage[cc_storage_point].code = 0;
    cc_storage_point--;

    return 1;
}

#endif // _CC_ACCOUNT

