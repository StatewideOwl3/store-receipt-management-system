#ifndef database_h
#define DATABASE_h

#include "customer.h"


typedef struct database{
    customer all_customers[100];
    receipt all_receipts[100];
    int customer_count;
    int receipt_count;
    inventory store_inventory;
}database;

void create_receipt(database* db);

receipt* find_receipt_by_id(database*db, int rec_id);

void print_receipt_by_id(database* db, int receipt_id); //0 indexed id ie index in db receipt array

//write db to file
//read db from file

database* add_customer_to_db(database* db, char* name, long long int phone);

customer* find_cust_ph(database* db, long long int phone);


#endif

