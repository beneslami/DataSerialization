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

    for(loop_var = 0; loop_var < 3; loop_var++){
        print_company(&obj->dream_companies[loop_var]);
    }

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

    p1.vehicle_nos[0] = 1000;
    p1.vehicle_nos[1] = 1001;
    p1.vehicle_nos[2] = 1002;
    p1.vehicle_nos[3] = 1003;
    p1.age = 31;
    p1.height = calloc(1, sizeof(int));
    *p1.height = 167;
    p1.last_salary_amounts[0] = NULL;
    p1.last_salary_amounts[1] = NULL;
    p1.last_salary_amounts[2] = calloc(1, sizeof(unsigned int));
    *p1.last_salary_amounts[2] = 20000;
    p1.last_salary_amounts[3] = calloc(1, sizeof(unsigned int));
    *p1.last_salary_amounts[3] = 40000;
    p1.last_salary_amounts[4] = NULL;
    strncpy(p1.name, "Abhishek", strlen("Abhishek"));
    strncpy(p1.company.comp_name, "Juniper", strlen("Juniper"));
    p1.company.emp_strength = 10000;
    p1.company.CEO = NULL;

    printf("printing the object to be serialized on sending machine\n\n");
    //print_person(&p1);


    ser_buff_t *b;
    init_serialized_buffer(&b);

    //serialize_person_t(&p1, b);
    //print_buffer_details(b);
    //reset_serialize_buffer(b);

    //person_t *p2 = de_serialize_person_t(b);

    //free_serialize_buffer(b);
    //b = NULL;

    //printf("\nprinting the deserialized object on recieving machine\n\n");
    //print_person(p2);

    return 0;
}
