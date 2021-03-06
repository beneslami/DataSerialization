#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/socket.h>
#include "serialize.h"
#include "serialize_linked_list.h"

#define SOCEKT_NAME "/tmp/socket"

int main(int argc, char **argv){
  struct sockaddr_un addr;
  int ret, i, data_socket, result;
  table_t *table;
  table = init();

  data_socket = socket(AF_UNIX, SOCK_STREAM, 0);
  if(data_socket == -1){
    perror("socket");
    exit(EXIT_FAILURE);
  }
  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SOCEKT_NAME, sizeof(addr.sun_path));

  ret = connect(data_socket, (const struct sockaddr*) &addr, sizeof(struct sockaddr_un));
  if(ret == -1){
    perror("connect");
    exit(EXIT_FAILURE);
  }
  /* creating linked list */
  table = init();
  add(table, 1);
  add(table, 2);
  add(table, 3);
  add(table, 4);
  add(table, 5);
  add(table, 6);

  ser_buff_t *b;
  init_serialized_buffer_of_defined_size(&b, 128);
  serialize_linkedlist(table, b);
  ret = write(data_socket, get_serialize_buffer(b), get_serialize_buffer_length(b));

  /* wait for the result */
  ret = read(data_socket, &result, sizeof(int));
  if(ret == -1){
    perror("read");
    exit(EXIT_FAILURE);
  }

  printf("%d\n", result);
  close(data_socket);
  return 0;
}
