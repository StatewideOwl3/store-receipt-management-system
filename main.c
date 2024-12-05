#include "inventory.h"

int main(){
    inventory* invent = (inventory*)malloc(sizeof(inventory));

    product* item1 = create_new_product("AirPods",259.99,100);
    product* item2 = create_new_product("MacBook",2399.99,50);
    product* item3 = create_new_product("iPhone16",889.33,80);
    product* item4 = create_new_product("DELL XPS 13 DE",2500,30);
    product* item5 = create_new_product("Lenovo Thinkpad",799,40);

    invent = add_product_to_inventory(invent,item1);
    invent = add_product_to_inventory(invent,item2);
    invent = add_product_to_inventory(invent,item3);
    invent = add_product_to_inventory(invent,item4);
    invent = add_product_to_inventory(invent,item5);

    print_inventory(invent);
    return 0;
}