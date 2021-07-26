
#ifndef Functionss_h
#define Functionss_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct car
{
    float cost;
    char *car_model;
    union types
    {
        char body_type[15];
        float engine_volume;
    } type;
    
    int flag;
    struct car *next;
};

int menu(void);
int confirmation(void);
int ClearStdin(void);
int input_check_int(void);
int input_check_int_for_sort(void);
int check_string_for_number(char* string);
float input_check_float(void);
void string_to_lowercase(char *string);
void putstring(char* string, int len);
void getstring(char *string,int size);
void put_cost(float num);
void put_engine_volume(float num);
void put_header(void);
int check_string(char *string);
int check_name(char *string);
char* get_model(void);
int records_number(struct car *top);

void input_info(struct car **top,struct car **last);
void output_info(struct car *top);
void output_car(struct car *top , int index);
void search(struct car *top);
void deletion(struct car **top,struct car **last,int number);
void input_in_file(struct car *top);
void load_from_file(struct car **top,struct car **last);

#endif /* Functionss_h */
