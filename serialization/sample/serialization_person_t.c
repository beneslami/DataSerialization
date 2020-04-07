#include "person_t.h"
#include "sentinel.h"

struct company_ {
  char comp_name[30];
  int emp_strength;
  person_t *CEO;
};

struct person_{
  unsigned int vehicle_nos[4];
  int age;
  int *height;
  unsigned int *last_salary_amounts[5];
  char name[30];
  company_t company; /* embedded structure */
  company_t dream_companies[3];
  struct person_ *CEO; /* pointer structure */
  struct person_ *administrative_staff[5];
};

void
serialize_person_t(person_t *obj, ser_buff_t *b) {
  int loop_var = 0;
  unsigned int sentinel = 0xFFFFFFFF;
  /*
  in the beginning of every serialization routine, always encode 0xFFFFFFFF in
  the serialized buffer if the object being serialized is NULL.
  *
  *
  * sentinel insertion code ... */
  SENTINEL_INSERTION_CODE(obj, b));

  for(loop_var = 0; loop_var < 4; loop_var++){
    serialize_data(b, (char*)&obj->vehicle_nos[loop_var], sizeof(unsigned int));
  }

  serialize_data(b, (char*)&obj->age, sizeof(int));

  if(obj->height)
    serialize_data(b, (char*)obj->height, sizeof(int));
  else
    serialize_data(b, (char*)&sentinel, sizeof(unsigned int));

  for(loop_var = 0; loop_var < 5; loop_var++){
    if(obj->last_salary_amounts[loop_var])
      serialize_data(b, (char*)obj->last_salary_amounts[loop_var], sizeof(unsigned int));
    else
      serialize_data(b, (char*)&sentinel, sizeof(unsigned int));
  }

  serialize_data(b, (char*)obj->name, sizeof(char)*strlen(obj->name));

  serialize_company_t(&obj->company, b);

  for(loop_var = 0; loop_var < 3; loop_var++){
    serialize_company_t(&obj->dream_companies[loop_var], b);
  }

  serialize_person_t(obj->CEO, b);

  for(loop_var = 0; loop_var < 5; loop_var++){
    serialize_person_t(obj->administrative_staff[loop_var], b);
  }
}

void serialize_company_t(company_t *obj, ser_buff_t *b){
  SENTINEL_DETECTION_CODE(obj, b);

  serialize_data(b, (char*)obj->comp_name, sizeof(char)*strlen(comp_name));
  serialize_data(b, (char*)&obj->emp_strength, sizeof(int));
  serialize_person_t(obj->CEO, b);
}
