#ifndef PERSON_H
#define PERSON_H
#include "serialize.h"

typedef struct person_ person_t;

typedef struct company_ {
  char comp_name[30];
  int emp_strength;
  person_t *CEO;
}company_t;

struct person_{
  unsigned int vehicle_nos[4];
  int age;
  int *height;
  unsigned int *last_salary_amounts[5];
  char name[30];
  company_t company; /* embedded structure */
  struct person_ *CEO; /* pointer structure */
  struct person_ *administrative_staff[5];
};

void serialize_person_t(person_t *obj, ser_buff_t *b);
void serialize_company_t(company_t *obj, ser_buff_t *b);
company_t *de_serialize_company_t(ser_buff_t *b);
person_t *de_serialize_person_t(ser_buff_t *b);

#endif
