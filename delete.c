#include "delete.h"
#include <stdlib.h>
#include <stdio.h>

void delete_item(dataset** head, int id){
    if (*head == NULL){
        printf("List empty\n");
        return;
    }
    else {
        if ((*head)->id == id){
            dataset* temp = *head;
            *head = (*head)->next;
            free(temp);
        }
        else {
            dataset* prev = *head;
            dataset* now = (*head)->next;
            while (now != NULL && now->id != id){
                now = now->next;
                prev = prev->next;
            }
            if (now != NULL){
                prev->next = now->next;
                free(now);
                return;
            }
            else {
                printf("ID not found\n");
                return;
            }
        }
    }
}