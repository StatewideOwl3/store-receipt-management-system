#ifndef POINT_OF_SALE_H
#define POINT_OF_SALE_H

#include <time.h>

#include "inventory.h"


typedef struct receipt{
    //time
    int receipt_number;//global++
    int receipt_arrays_indexer;//initialise to 0 WTF IS THIS - INDEXING FOR BELOW ARRAYS
    product items_bought[100];
    int qty_bought[100];//one one index mapping
    float item_values[100];//one one index mapping
    float total_bill;//summing item_values array
    long long int customer_phone;
}receipt;


#endif