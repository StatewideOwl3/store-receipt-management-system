#include "database.h"

#include "point_of_sale.h"


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
        else if (purchase_validity(item,product_qty)==false){
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
            invent = update_product(invent, product_name, item->prod_price,item->prod_stock - product_qty);

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

receipt* find_receipt_by_id(database*db, int rec_id){
    for (int i=0; i< db->receipt_count; i++){
        if ((db->all_receipts[i]).receipt_number==rec_id)
          return &(db->all_receipts[i]);
    }
    return NULL;
}

void print_receipt_by_id(database* db, int receipt_id){
    receipt* rec = find_receipt_by_id(db,receipt_id);
    if (rec==NULL){
        printf("Receipt ID invalid!\n");
        return;
    }

    printf("********************BONDA'S GENERAL STORES RECEIPT********************\n");
    printf("----------------------------------------------------------------------\n");
    printf("\t\t\tReceipt ID: %d\t\t\t\n",receipt_id);
    printf("======================================================================\n");
    printf("Code\t\t\tQty\t\t\tDescription\t\t\tPrice/$\n");
    printf("------------------------------------------------------------\n");
    for (int i=0;i<rec->receipt_arrays_indexer;i++){
        product p = rec->items_bought[i];
        printf("%d\t\t\t%d\t\t\t%s\t\t\t%.2f\n",p.prod_id,rec->qty_bought[i],p.prod_name,rec->item_values[i]);
    }

    printf("\n\n");
    printf("------------------------------------------------------------\n");
    printf("Date: \t\t\tTOTAL: %.2f\n",rec->total_bill);
    customer c = *find_cust_ph(db,rec->customer_phone);
    printf("Customer: %s %lld\n",c.name,c.phone_no);
    printf("===================================================================\n");

}