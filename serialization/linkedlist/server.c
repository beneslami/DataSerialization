#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

table_t *table;
int main (int argc, char **argv){

  table = init();
  add(table, 1);
  add(table, 2);
  add(table, 3);
  add(table, 4);
  add(table, 5);
  show(table);
  table_entry_t *node = find(table, 3);
  int i = del(table, node);
  printf("\n");
  if (i == 0){
    show(table);
  }
  // Call any function


  free(table);
  return 0;
}
