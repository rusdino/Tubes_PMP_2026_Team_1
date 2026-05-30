#include "find_and_update.h"
#include <stdio.h>
#include <string.h>

void find(dataset* list, int id, dataset** node){
    dataset* temp = list;
    while (temp != NULL && temp->id != id){
        temp = temp->next;
    }
    *node = temp;
    return;
}

void update_status(dataset** list, int id, char status[]){
    dataset* updated_node;
    find(*list, id, &updated_node);
    if (updated_node != NULL){
        strcpy(updated_node->status, status);
    }
    else {
        printf("ID not found\n");
    }
}

void update_stock(dataset** list, int id, int amount){
    dataset* updated_node;
    find(*list, id, &updated_node);
    if (updated_node != NULL){
        if (updated_node->jumlah_stok - amount <0){
            printf ("Requirement amount not available\n");
            printf ("Available stock %d\n", updated_node->jumlah_stok);
        }
        else {
            updated_node->jumlah_stok -= amount;
            printf ("Stock updated\n");
            printf ("Current stock of ID %d is %d\n", id, updated_node->jumlah_stok);
        }
    }
    else {
        printf("ID not found\n");
    }
}