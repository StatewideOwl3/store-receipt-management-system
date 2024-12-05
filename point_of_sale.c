#include "point_of_sale.h"

int receipt_number = 0; //datavbase array indexer


void create_receipt(database* db){
    receipt* new_receipt = (receipt*)malloc(sizeof(receipt));
    new_receipt->receipt_number = receipt_number++;
    new_receipt->receipt_arrays_indexer=0;

    int flag=1;
    do{
        printf("Enter Product Name and Product Qty: ");
        char product_name[30];
        int product_qty;
        scanf("%s %d",product_name,&product_qty);

        //check if purchase is available ie qty is there in the inventory
        product* item = find_prod_by_name(&(db->store_inventory),product_name);
        if (item==NULL){
            printf("Item does not exist, try again.\n");
        }
        else if (purchase_validity(item)==false){
            printf("Invalid Quantity. Try again with a lesser quantity.\n");
        }
        else{
            //finish receipt
            new_receipt->items_bought[new_receipt->receipt_arrays_indexer] = *find_prod_by_name(&(db->store_inventory),product_name);
            new_receipt->qty_bought[new_receipt->receipt_arrays_indexer] = product_qty;
            new_receipt->item_values[new_receipt->receipt_arrays_indexer] = product_qty*(find_prod_by_name(&(db->store_inventory),product_name)->prod_price);
            new_receipt->total_bill+=new_receipt->item_values[new_receipt->receipt_arrays_indexer];
            new_receipt->receipt_arrays_indexer++;
            
            //update inventory
            inventory* invent = &(db->store_inventory);
            update_product_stock(invent, product_name, item->prod_stock - product_qty);

            printf("Do you want to buy more products? 1/0: ");
            scanf("%d",&flag);
        }
        

    }while(flag);

    printf("Enter customer phone number: ");
    long long int phone;
    scanf("%lld",&phone);

    customer* cust = find_cust_ph(db,phone);

    //update database
    db->all_receipts[new_receipt->receipt_number]=*new_receipt;
    db->receipt_count++;

    //update cust
    cust->receipts_generated_indicies[cust->array_indexer] = new_receipt->receipt_number;
    cust->total_money_spent += new_receipt->total_bill;

//terrible function but we ball.
//can split this into so many smaller more understandable functions.
    
}

void print_receipt_by_id(database* db, int receipt_id){
    printf("********************BONDA'S GENERAL STORES********************\n");
    printf("--------------------------------------------------------------\n");
    printf("\t\tReceipt ID: %d\t\t\n",);



}