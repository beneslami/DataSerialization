CC = gcc
FLAGS = -g -c

TARGET:
	$(CC) $(FLAGS) serialization_person_t.c -o serialization_person_t.o
	$(CC) $(FLAGS) serialize.c -o serialize.o
	$(CC) $(FLAGS) application.c -o application.o
	$(CC) -g application.o serialization_person_t.o serialize.o -o exe
clean:
	rm -rf serialization_person_t.o serialize.o application.o exe
