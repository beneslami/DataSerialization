#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <stdio.h>
#include "serialize.h"

struct ser_buff_ {
  void *b;
  int size;
  int next;
};

void
init_serialized_buffer_of_defined_size(ser_buff_t **b, int size){
  (*b) = (ser_buff_t*)calloc(1, sizeof(ser_buff_t));
  (*b)->b  = calloc(1, size);
  (*b)->size = size;
  (*b)->next = 0;
}

void
serialize_buffer_skip(ser_buff_t *b, int size){
  int available_size = b->size - b->next;
  if(available_size >= size){
    b->next = b->next + size;
    return;
  }
  while(available_size < size){
    b->size = b->size * 2;
    available_size = b->size - b->next;
    b->b = realloc(b->b, b->size);
  }
  b->next += size;
  return;
}

void
serialize_data(ser_buff_t *b, char *data, int nbytes){
  if(b == NULL) assert(0);
  ser_buff_t *buff = b;
  int available_size = buff->size - buff->next;
  int isResize = 0;

  while(available_size < nbytes){
    buff->size *= 2;
    available_size = buff->size - buff->next;
    isResize = 1;
  }
  if(isResize == 0){
    memcpy((char*)buff->b + buff->next, data, nbytes);
    buff->next += nbytes;
    return;
  }
  buff->b = realloc(buff->b , buff->size);
  memcpy((char*)buff->b + buff->next, data, nbytes);
  buff->next += nbytes;
  return;
}

void
de_serialize_data(char *dest, ser_buff_t *b, int nbytes){
  if(!b || !b->b) assert(0);
  if(!nbytes) return;
  if((b->size - b->next) < nbytes) assert(0);
  memcpy((char*)dest, (char*)b->b + b->next, nbytes);
  b->next += nbytes;
}

void
free_serialize_buffer(ser_buff_t *b){
    free(b->b);
    free(b);
}

int
get_serialize_buffer_size(ser_buff_t *b){
  return b->size;
}

int
get_serialize_buffer_length(ser_buff_t *b){
  return b->next;
}

void
print_buffer_detail(ser_buff_t *b){
  if(!b || !b->b) {
    assert(0);
  }
  printf("%d\n", b->size);
  printf("%d\n", b->next);
}

void
serialize_reset_buffer(ser_buff_t *b){
  b->next = 0;
}

char
*get_serialize_buffer(ser_buff_t* b){
  return (char*)b->b;
}

void
set_serialize_buffer(ser_buff_t *b, char *data, int nbytes){
  memcpy((char*)b->b, data, nbytes);
}
