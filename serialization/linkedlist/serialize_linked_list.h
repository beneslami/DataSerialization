#ifndef SERIALIZE_LINKED_LIST_H
#define SERIALIZE_LINKED_LIST_H
#include "serialize.h"
#include "linkedlist.h"
void serialize_linkedlist(table_t*, ser_buff_t*);
void de_serialize_linkedlist(ser_buff_t *, table_t *);

#endif
