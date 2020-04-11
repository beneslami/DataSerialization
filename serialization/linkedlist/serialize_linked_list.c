#include <stdio.h>
#include "serialize.h"
#include "linkedlist.h"
#include "serialize_linked_list.h"

void
serialize_linkedlist(table_t *table, ser_buff_t *b){
  table_entry_t *head = table->next;
  while(head){
    int temp = head->data;
    serialize_data(b, (char*)&temp, sizeof(int));
    head = head->next;
  }
  unsigned int sentinel = 0xFFFFFFFF;
  serialize_data(b, (char*)&sentinel, sizeof(unsigned int)); // mark the tail
}

table_t
*de_serialize_linkedlist(ser_buff_t *b){
  int i = 1;
  table_t *table;
  table = init();
  unsigned int sentinel = 0;
  while(i){
    de_serialize_data((char*)&sentinel, b, sizeof(unsigned int));
    if(sentinel == 0xFFFFFFFF){
      break;
    }
    else{
      serialize_buffer_skip(b, sizeof(unsigned int)* (-1));
      de_serialize_data((char*)&i, b, sizeof(int));
      add(table, i);
    }
  }
  return table;
}
