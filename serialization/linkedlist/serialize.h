#ifndef SERIALIZE_H
#define SERIALIZE_H

typedef struct ser_buff_ ser_buff_t;

void init_serialized_buffer_of_defined_size(ser_buff_t **b, int size);
void serialize_buffer_skip(ser_buff_t *, int);
void free_serialize_buffer(ser_buff_t *);
void serialize_data(ser_buff_t *, char *, int);
void de_serialize_data(char *, ser_buff_t *, int);
void free_serialize_buffer(ser_buff_t *);
int get_serialize_buffer_size(ser_buff_t*);
int get_serialize_buffer_length(ser_buff_t*);
void print_buffer_detail(ser_buff_t *b);
void buffer_copy(ser_buff_t *, char*, int);
void serialize_reset_buffer(ser_buff_t*);
#endif
