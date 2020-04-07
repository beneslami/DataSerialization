#ifndef SERIALIZE_H
#define SERIALIZE_H

typedef struct ser_buff_ ser_buff_t; /* opaque data structure */

/* init functions*/
void init_serialized_buffer(ser_buff_t **b);
void init_serialized_buffer_of_defined_size(ser_buff_t **b, int size);

/* Serialize functions*/
char is_serialized_buffer_empty(ser_buff_t *b);

/* get functions*/
int get_serialize_buffer_size(ser_buff_t *b);
int get_serialize_buffer_length(ser_buff_t *b);
int get_serialize_buffer_current_ptr_offset(ser_buff_t *b);
char *get_serialize_buffer_current_ptr(ser_buff_t *b);
void serialize_buffer_skip(ser_buff_t *b, unsigned long size);
void copy_in_serialized_buffer_by_offset(ser_buff_t *b, int size, char *value, int offset);

/* De-Serialize function */
void serialize_data(ser_buff_t *b, char *data, int nbytes);
void de_serialize_data(char *dest, ser_buff_t *b, int size);

/* free Resourse*/
void free_serialize_buffer(ser_buff_t *b);

/*reset function*/
void truncate_serialize_buffer(ser_buff_t **b);
void reset_serialize_buffer(ser_buff_t *b);
/* Details*/
void print_buffer_details(ser_buff_t *b, const char *fn, int lineno);

#endif
