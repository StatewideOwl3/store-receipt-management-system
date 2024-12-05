#ifndef INVENTORY_H
#define INVENTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct product{
    int prod_id;//using product_counter in inventory.c
    char prod_name[30];
    float prod_price;
    int prod_stock;
}product;

typedef struct inventory{
    product products_array[100];
    int products_count;
}inventory;

//assuming in main we initialise inventory and its product_count to 0;

product* create_new_product(char* name, float price, int qty);

inventory* add_product_to_inventory(inventory* invent, product* new_product);

product* find_prod_by_id(inventory* invent, int id);

product* find_prod_by_name(inventory* invent, char* name);

inventory* update_product_price(inventory* invent, char* name, float new_price);

inventory* update_product_stock(inventory* invent, char* name, int qty);

void print_item(product* item);

void print_inventory(inventory* invent);

#endif