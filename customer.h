#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "database.h"
#include "inventory.h"
#include "point_of_sale.h"
#include <string.h>

typedef struct customer{
    char name[30];
    long long int phone_no;
    int receipts_generated_indicies[100];//linked to db
    int array_indexer;
    float total_money_spent;
}customer;

database* add_customer_to_db(database* db, char* name, long long int phone);

customer* find_cust_ph(database* db, long long int phone);

#endif