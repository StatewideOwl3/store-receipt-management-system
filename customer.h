#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "inventory.h"
#include "point_of_sale.h"


typedef struct customer{
    char name[30];
    long long int phone_no;
    int receipts_generated_indicies[100];//linked to db
    int array_indexer;
    float total_money_spent;
}customer;


#endif