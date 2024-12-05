#include "inventory.h"

int product_counter=0;

product* create_new_product(char* name, float price, int qty){
    product* new_product = (product*)malloc(sizeof(product));
    if(new_product == NULL){
        printf("New Product Malloc Unsuccessful! Returning NULL ptr.\n");
        return NULL;
    }

    strcpy(new_product->prod_name,name);
    new_product->prod_id = product_counter++; //its ID is its location in the inventory array
    new_product->prod_price = price;
    new_product->prod_stock = qty;
    return new_product;
}

inventory* add_product_to_inventory(inventory* invent, product* new_product){
    invent->products_array[invent->products_count++] = *new_product;
    //in sqr [], new_product->prod_id should also work fine with my desing?
    return invent;
}

product* find_prod_by_id(inventory* invent, int id){
    for (int i=0; i<invent->products_count; i++){
        if (invent->products_array[i].prod_id==id)
          return &(invent->products_array[i]);
    }
    return NULL;
}

product* find_prod_by_name(inventory* invent, char* name){
    for (int i=0; i<invent->products_count;i++){
        if (strcpy(invent->products_array[i].prod_name,name)==0)
          return &(invent->products_array[i]);
    }
    return NULL;
}

inventory* update_product_price(inventory* invent, char* name, float new_price){
    product* item = find_prod_by_name(invent,name);
    item->prod_price = new_price;
    return invent;
}

inventory* update_product_stock(inventory* invent, char* name, int qty){
    product* item = find_prod_by_name(invent, name);
    item->prod_stock=qty;
    return invent;
}

void print_item(product* item){
    //to use in printing inventory:
    //NOT RECEPIPT, INVENTORY VIEWING PURPOSE
    printf("%d\t%s\t\t%.2f\t%d\n",item->prod_id,item->prod_name,item->prod_price,item->prod_stock);
}

void print_inventory(inventory* invent){
    printf("**********CURRENT INVENTORY**********\n");
    printf("ProductID\tName\t\tPrice\tStock\n"
           "----------------------------------------\n");
    for (int i=0; i<invent->products_count;i++){
        print_item(&(invent->products_array[i]));
    }
}