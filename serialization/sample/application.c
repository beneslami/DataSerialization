#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "person_t.h"
#include "serialize.h"

void print_person(person_t *);
void print_company(company_t *);

void
print_person(person_t *obj){

    if(!obj) return;

    int loop_var = 0;
    for(loop_var = 0; loop_var < 4; loop_var++){
        printf("vehicle no[%d] = %d\n", loop_var, obj->vehicle_nos[loop_var]);
    }

     printf("age = %d\n", obj->age);

     if(obj->height){
        printf("height = %d\n", *obj->height);
     }
     else{
        printf("height = NULL\n");
     }

    for(loop_var = 0; loop_var < 5; loop_var++){
        if(obj->last_salary_amounts[loop_var]){
            printf("last_salary_amounts[%d] = %d\n",
                loop_var, *obj->last_salary_amounts[loop_var]);
        }
        else{
            printf("last_salary_amounts[%d] = Nil\n",
                loop_var);
        }
    }
    printf("name = %s\n", obj->name);
    print_company(&obj->company);

    print_person(obj->CEO);

    for(loop_var = 0; loop_var < 5; loop_var++){
        print_person(obj->administrative_staff[loop_var]);
    }
}

void
print_company(company_t *obj){

    if(!obj) return;
    printf("comp_name = %s\n", obj->comp_name);
    printf("emp_strength = %d\n", obj->emp_strength);
    print_person(obj->CEO);
}

int main(int argc, char **argv){

    person_t p1;
    memset(&p1, 0, sizeof(person_t));

    p1.vehicle_nos[0] = 1000; //4
    p1.vehicle_nos[1] = 1001; //4
    p1.vehicle_nos[2] = 1002; //4
    p1.vehicle_nos[3] = 1003; //4
    p1.age = 27;              //4
    p1.height = calloc(1, sizeof(int));
    *p1.height = 176;         //4
    p1.last_salary_amounts[0] = NULL; //10
    p1.last_salary_amounts[1] = NULL; //10
    p1.last_salary_amounts[2] = calloc(1, sizeof(unsigned int));
    *p1.last_salary_amounts[2] = 20000; //4
    p1.last_salary_amounts[3] = calloc(1, sizeof(unsigned int));
    *p1.last_salary_amounts[3] = 40000; //4
    p1.last_salary_amounts[4] = NULL;  //10
    strncpy(p1.name, "Benyamin", strlen("Benyamin"));  //8
    strncpy(p1.company.comp_name, "CISCO", strlen("CISCO"));  //5
    p1.company.emp_strength = 10000; //5
    p1.company.CEO = NULL; //10
    p1.CEO = NULL;          //10
    p1.administrative_staff[0] = NULL; //10
    p1.administrative_staff[1] = NULL;  //10
    p1.administrative_staff[2] = NULL;  //10
    p1.administrative_staff[3] = NULL;   //10
    p1.administrative_staff[4] = NULL;  //10
    printf("printing the object to be serialized on sending machine\n\n");
    print_person(&p1);

    ser_buff_t *b;
    init_serialized_buffer_of_defined_size(&b, 512);
    serialize_person_t(&p1, b);

    /* now suppose we sent our data through socket to the desitnation. Now from
    this line below, we are in receiving side */

    reset_serialize_buffer(b);
    person_t *p2 = de_serialize_person_t(b);

    free_serialize_buffer(b);
    b = NULL;

    printf("\nprinting the deserialized object on recieving machine\n\n");
    print_person(p2);

    return 0;
}
