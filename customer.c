#include "customer.h"

database* add_customer_to_db(database* db, char* name, long long int phone){
    customer* new_customer = (customer*)malloc(sizeof(customer));
    new_customer->array_indexer=0;
    strcpy(new_customer->name,name);
    new_customer->phone_no = phone;
    new_customer->total_money_spent=0;
    
    db->all_customers[db->customer_count++] = *new_customer;
    return db;
}

customer* find_cust_ph(database* db, long long int phone){
    for (int i=0; i< db->customer_count; i++){
        if (db->all_customers[i].phone_no==phone)
          return &(db->all_customers[i]);
    }
    return NULL;
}