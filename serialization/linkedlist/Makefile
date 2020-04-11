TARGET:
	gcc -g -c linkedlist.c -o linkedlist.o
	gcc -g -c serialize.c -o serialize.o
	gcc -g -c serialize_linked_list.c -o serialize_linked_list.o
	gcc -g -c server.c -o server.o
	gcc -g -c client.c -o client.o
	gcc server.o linkedlist.o serialize_linked_list.o serialize.o -o server
	gcc client.o linkedlist.o serialize_linked_list.o serialize.o -o client

clean:
	rm linkedlist.o server.o client.o serialize_linked_list.o serialize.o client server
