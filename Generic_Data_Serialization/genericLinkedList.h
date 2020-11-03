#ifndef GENERICLINKEDLIST
#define GENERICLINKEDLIST
#include "serialize.h"

typedef struct linkedlist_  linkedlist_t;  /* opaque Data Strutcure */
typedef void (*serialize_ll_app_callback)(linkedlist_t*, ser_buff_t*);
typedef void (*de_serialize_ll_app_callback)(ser_buff_t*);

void set_serialize_app_callback_assignment(linkedlist_t *ll, serialize_ll_app_callback);
void set_de_serialize_app_callback_assignment(linkedlist_t *ll, de_serialize_ll_app_callback);
void set_ll_data(linkedlist_t*, void*);
void *get_ll_data(linkedlist_t*);
linkedlist_t *get_ll_next_node(linkedlist_t*);
void set_ll_next_node(linkedlist_t*, linkedlist_t*);

#endif
