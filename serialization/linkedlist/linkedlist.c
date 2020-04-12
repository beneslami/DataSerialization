#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

table_t
*init(){
  table_t *table = (table_t*)calloc(1, sizeof(table_t));
  table_entry_t *node = calloc(1, sizeof(table_entry_t));
  node->data = 0;
  node->next = node;
  table->next = node;
  return table;
}

int
add(table_t *table, int data){
  table_entry_t *head = table->next;
  if(head->data == 0){
    head->data = data;
    head->next = NULL;
    return 0;
  }
  while(head->next){
    head = head->next;
  }
  table_entry_t *node = calloc(1, sizeof(table_entry_t));
  node->data = data;
  node->next = NULL;
  head->next = node;
  return 0;
}

void
show(table_t *table){
  table_entry_t *head = table->next;
  while(head){
    printf("%d\t", head->data);
    head = head->next;
  }
}

table_entry_t
*find(table_t *table, int data){
  table_entry_t *head = table->next;
  while(head){
    if(head->data == data){
      return head;
    }
    else{
      head = head->next;
    }
  }
  return NULL;
}

int
del(table_t *table, table_entry_t *entry){
  table_entry_t *head = table->next;
  table_entry_t *temp, *current, *previous;
  current = head;
  previous = head;

  if(!head->next){
    return -1;
  }
  while(current){
    if(current->data == entry->data){
      previous->next = current->next;
      free(current);
      return 0;
    }
    previous = current;
    current = current->next;
  }
  return -1;
}

int
sum_linked_list_item(table_t *table){
	int result = 0;
	table_entry_t *node = table->next;
	while(node){
		result += node->data;
		node = node->next;
	}
	return result;
}
