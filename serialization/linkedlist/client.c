#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/socket.h>
#define SOCEKT_NAME "/tmp/socket"

int main(int argc, char **argv){
  struct sockaddr_un addr;
  int ret, i, data_socket, result;

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

  /* serialization routine */
  i = 10;
  ret = write(data_socket, &i, sizeof(int));
  if(ret == -1){
    perror("write");
    exit(EXIT_FAILURE);
  }
  ret = read(data_socket, &result, sizeof(int));
  if(ret == -1){
    perror("read");
    exit(EXIT_FAILURE);
  }
  printf("%d\n", result);
  close(data_socket);
  return 0;
}
