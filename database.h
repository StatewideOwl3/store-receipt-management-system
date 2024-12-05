#ifndef database_h
#define DATABASE_h


#include "customer.h"
#include "point_of_sale.h"
#include "inventory.h"


typedef struct database{
    customer all_customers[100];
    receipt all_receipts[100];
    int customer_count;
    int receipt_count;
    inventory store_inventory;
}database;

//write db to file
//read db from file

#endif

