#ifndef PERSON_H
#define PERSON_H
#include "serialize.h"

typedef struct company_ company_t; /* opaque structure */
typedef struct person_ person_t;   /* opaque structure */

void serialize_person_t(person_t *obj, ser_buff_t *b);
void serialize_company_t(company_t *obj, ser_buff_t *b);
company_t *de_serialize_company_t(ser_buff_t *b);
person_t *de_serialize_person_t(ser_buff_t *b);

#endif
