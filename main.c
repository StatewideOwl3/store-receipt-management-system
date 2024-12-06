#include "inventory.h"
#include "database.h"
#include "point_of_sale.h"
#include "customer.h"

void print_main_functions(){
    printf("\n\n====================SRMS====================\n");
    printf("Choose Module:\n1. Inventory Module\n2. Sale Module(New Sale)\n3. Database Module\n4.Exit\n");
}

void print_inventory_module(){
    printf("===========SRMS-InventoryModule===========\n");
    printf("Inventory Functions:\n1.Print Current Inventory\n2.Add New Item\n3.Update Existing Item\n");
}

void print_database_module(){
    printf("===========SRMS-DatabaseModule===========\n");
    printf("Database Functions:\n1.Print Database Stats\n2.Print All Customer Details\n3.Add New Customer to DB\n");
}

int main(){
    database* db = (database*)malloc(sizeof(database));
    inventory* invent = (inventory*)malloc(sizeof(inventory));
    db->customer_count=0;
    db->receipt_count=0;
    db->store_inventory = *invent;

    while(1){
        print_main_functions();
        int main_op_code;
        scanf("%d",&main_op_code);

        if (main_op_code==4)
        return 0;
        
        if (main_op_code==1){
            print_inventory_module();
            int inventory_code;
            scanf("%d",&inventory_code);

            switch(inventory_code){
                case 1:{
                    print_inventory(&(db->store_inventory));
                    break;
                }
                case 2:{
                    printf("Enter product name, price and qty to add to stock: ");
                    char item_name[30];
                    float item_price;
                    int item_qty;
                    scanf("%s %f %d",item_name, &item_price, &item_qty);

                    product* new_product = create_new_product(item_name, item_price, item_qty);
                    db->store_inventory = *(add_product_to_inventory(&(db->store_inventory),new_product));
                    break;
                }
                case 3:{
                    printf("Enter product name, new price and new quantity: ");
                    char item_name[30];
                    float new_price;
                    int new_qty;
                    scanf("%s %f %d",item_name,&new_price,&new_qty);
                    product* item = find_prod_by_name(&(db->store_inventory),item_name);
                    db->store_inventory = *(update_product(&(db->store_inventory),item_name,new_price,new_qty));
                    break;
                }
            }
        }
        else if (main_op_code==2){
            create_receipt(db);
        }
        else if (main_op_code==3){
            print_database_module();
            int db_op_code;
            scanf("%d",&db_op_code);
            switch(db_op_code){
                case 1:{
                    print_db_stats(db);
                    break;
                }
                case 2:{
                    print_customer_detials(db);
                    break;
                }
                case 3:{
                    printf("Creating New Customer:\n");
                    printf("Enter name and phone number: ");
                    char cust_name[30];
                    long long int cust_ph;
                    scanf("%s %lld",cust_name,&cust_ph);
                    db = add_customer_to_db(db,cust_name,cust_ph);
                    printf("Successfully added new customer!\n");
                }
            }
        }
    }

    return 0;
}