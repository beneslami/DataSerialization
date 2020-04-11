TARGET:
	gcc -g -c linkedlist.c -o linkedlist.o
	gcc -g -c server.c -o server.o
	gcc -g -c client.c -o client.o
	gcc server.o linkedlist.o -o server
	gcc client.o linkedlist.o -o client

clean:
	rm exe linkedlist.o server.o client.o
