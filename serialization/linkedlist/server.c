#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>
#include "linkedlist.h"
#include "serialize.h"
#include "serialize_linked_list.h"

#define SOCEKT_NAME "/tmp/socket"

int main (int argc, char **argv){
  struct sockaddr_un name;
  int ret;
  int connection_socket;
  int data_socket;
  int result;

  ser_buff_t *b;
  init_serialized_buffer_of_defined_size(&b, 128);
  table_t *table;
  table = init();

  /* socket routine */
  unlink(SOCEKT_NAME);
  connection_socket = socket(AF_UNIX, SOCK_STREAM, 0);
  if(connection_socket == -1){
    perror("socket");
    exit(EXIT_FAILURE);
  }
  memset(&name, 0, sizeof(struct sockaddr_un));
  name.sun_family = AF_UNIX;
  strncpy(name.sun_path, SOCEKT_NAME, sizeof(name.sun_path) - 1);
  ret = bind(connection_socket, (const struct sockaddr*)&name, sizeof(struct sockaddr_un));
  if(ret == -1){
    perror("bind");
    exit(EXIT_FAILURE);
  }
  ret = listen(connection_socket, 20);
  if(ret == -1){
    perror("listen");
    exit(EXIT_FAILURE);
  }
  for(;;){
    data_socket = accept(connection_socket, NULL, NULL);
    if(data_socket == -1){
      perror("accpet");
      exit(EXIT_FAILURE);
    }

    ret = read(data_socket, b, 128);
    serialize_reset_buffer(b);
    print_buffer_detail(b);
    /* de-serialization routine */
    de_serialize_linkedlist(b, table);

    result = add_linked_list_item(table);

    ret = write(data_socket, &result, sizeof(int));
    if(ret == -1){
      perror("write");
      exit(EXIT_FAILURE);
    }
    close(data_socket);
  }
  close(connection_socket);
  free(table);
  return 0;
}
