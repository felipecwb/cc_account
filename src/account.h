
#ifndef _CC_ACCOUNT
#define _CC_ACCOUNT 1

// define quantity if not defined
#ifndef QTD_ACCOUNTS
#  define QTD_ACCOUNTS 50
#endif

/**
 * struct address
 * the client address
 */
struct s_address {
    char street[50];
    unsigned int number;
    char district[30];
    char city[30];
    char state[3];
};

/**
 * struct address
 * the client account
 */
struct s_account {
    unsigned int code;
    char name[30];
    char email[50];
    struct s_address address;
};

/**
 * defining a type for that
 */
typedef struct s_account account_t;

/**
 * variabe for accounts storage
 */
#ifndef TEST
    static account_t cc_storage[QTD_ACCOUNTS];
    static int cc_storage_point = -1;
#else
    static account_t cc_storage[QTD_ACCOUNTS] = {
        {100,"Felipe Francisco","felipe@francisco.com",{"Someplace there",2000,"Green Village","Curitiba","PR"}},
        {101,"Petter Pan","petter@pan.com",{"Magic Place",1000,"??","In the magic","UU"}}
    };
    static int cc_storage_point = 1;
#endif

/**
 * get the list of that
 *
 * @return account_t[]
 */
account_t *account_list();

/**
 * Find an account with his account code
 *
 * @param int code
 * @return *account_t
 */
account_t *account_find_by_code(unsigned int code);

/**
 * Add the new checking account
 *
 * @param account_t cc
 * @return int 1: success, 0: error
 */
int account_add(account_t cc);

/**
 * Delete from the storage list and return as a new value
 *
 * @param account_t *cc
 * @return int 1: success, o error
 */
int account_delete(account_t *cc);

#endif //_CC_ACCOUNT

