#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "genericLinkedList.h"

typedef struct table_{
	linkedlist_t *next;
}table_t;

table_t *init();
int add(table_t *, int);
void show(table_t *);
table_entry_t *find(table_t *, int);
int del(table_t *, table_entry_t *);
int sum_linked_list_item(table_t*);

#endif
