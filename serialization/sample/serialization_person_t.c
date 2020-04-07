#include "person_t.h"
#include "sentinel.h"
#include "serialize.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

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
  SENTINEL_INSERTION_CODE(obj, b);

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

void
serialize_company_t(company_t *obj, ser_buff_t *b){
  SENTINEL_INSERTION_CODE(obj, b);

  serialize_data(b, (char*)obj->comp_name, sizeof(char)*strlen(obj->comp_name));
  serialize_data(b, (char*)&obj->emp_strength, sizeof(int));
  serialize_person_t(obj->CEO, b);
}

person_t *
de_serialize_person_t(ser_buff_t *b){
  int loop_var;
  unsigned int sentinel = 0;
  /* for envery de_serialization routine, always first insert sentinel detection
  code.
  *
  sentinel detection code */

  SENTINEL_DETECTION_CODE(b);
  printf("here\n");                                               
  person_t *obj = calloc(1, sizeof(person_t));

  for(loop_var = 0; loop_var < 4; loop_var++){
    de_serialize_data((char*)&obj->vehicle_nos[loop_var], b, sizeof(unsigned int));
  }

  de_serialize_data((char*)&obj->age, b, sizeof(int));

 /* since the next field is pointer, force the next 4 bytes in the serialized
    buffer to check for the sentinel presence. */
  de_serialize_data((char*)&sentinel, b, sizeof(unsigned int));
  if(sentinel == 0xFFFFFFFF){
    obj->height = NULL;
  }
  else{
    serialize_buffer_skip(b, -1 * sizeof(unsigned int));
    obj->height = calloc(1, sizeof(int));
    de_serialize_data((char*)obj->height, b, sizeof(int));
  }

  for(loop_var = 0; loop_var < 5; loop_var++){
    de_serialize_data((char*)&sentinel, b, sizeof(unsigned int));
    if(sentinel == 0xFFFFFFFF){
      obj->last_salary_amounts[loop_var] = NULL;
    }
    else{
      serialize_buffer_skip(b, sizeof(unsigned int) * -1);
      obj->last_salary_amounts[loop_var] = calloc(1, sizeof(unsigned int));
      de_serialize_data((char*)obj->last_salary_amounts[loop_var], b, sizeof(unsigned int));
    }
  }

  de_serialize_data((char*)obj->name, b, sizeof(char)*strlen(obj->name));

  company_t *company = de_serialize_company_t(b);
  obj->company = *company; /* shallow copy */
  free(company); /* shallow free */

  for(loop_var = 0; loop_var < 3; loop_var++){
    company_t *company = de_serialize_company_t(b);
    obj->dream_companies[loop_var] = *company; /* shallow copy */
    free(company); /* shallow free */
  }

  obj->CEO = de_serialize_person_t(b);

  for(loop_var = 0; loop_var < 5; loop_var++){
    obj->administrative_staff[loop_var] = de_serialize_person_t(b);
  }

  return obj;
}

company_t *
de_serialize_company_t(ser_buff_t *b){

  SENTINEL_DETECTION_CODE(b);
  company_t *obj = calloc(1, sizeof(company_t));

  de_serialize_data((char*)obj->comp_name, b, sizeof(char)*strlen(obj->comp_name));
  de_serialize_data((char*)&obj->emp_strength, b, sizeof(int));
  obj->CEO = de_serialize_person_t(b);

  return obj;
}
