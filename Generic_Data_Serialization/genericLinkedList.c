#include "genericLinkedList.h"

struct linkedlist_ {
  void *data;
  struct linkedlist_ *next;
  serialize_ll_app_callback serialize_ll_callback(linkedlist_t*, ser_buff_t *);
  de_serialize_ll_app_callback de_serialize_ll_callback(ser_buff_t *);
};

void
set_serialize_app_callback_assignment(linkedlist_t *ll, serialize_ll_app_callback call_back){
  ll->serialize_ll_callback = call_back;
}

void
set_de_serialize_app_callback_assignment(linkedlist_t *ll, de_serialize_ll_app_callback call_back){
  ll->de_serialize_ll_callback = call_back;
}

void
set_ll_data(linkedlist_t *ll, void *data){
  ll->data = data;
}

void*
get_ll_data(linkedlist_t *ll){
  return ll->data;
}

linkedlist_t*
get_ll_next_node(linkedlist_t *ll){
  return ll->next;
}

void
set_ll_next_node(linkedlist_t *current, linkedlist_t *next){
  current->next = next;
}
