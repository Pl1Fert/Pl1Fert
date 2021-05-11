#ifndef Functions_h
#define Functions_h

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
};

struct queue
{
    struct car car;
    struct queue *next;
};

struct car input_info(void);
void push(struct queue **top,struct queue **last);
void output_info(struct queue *top);
void output_car(struct queue *pointer ,int index);
void deletion(struct queue **top,struct queue **last,int number);
void search(struct queue *top);
void input_in_file(struct queue *top);
void load_from_file(struct queue **top,struct queue **last);


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

#endif /* Functions_h */
