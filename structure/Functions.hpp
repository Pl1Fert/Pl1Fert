#ifndef Functions_hpp
#define Functions_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct student
{
    char lastname[20];
    char name[20];
    char patronymic[20];
    char address[20];
    char group_number[20];
    float rating;

};

int menu(void);
int confirmation(void);
int ClearStdin(void);
int input_check_int(void);
int input_check_int_for_sort(void);
int check_string_for_number(char* string);
float input_check_float(void);

void enter_struct(struct student*,int amount);
void output_struct(struct student*,int amount);
void header_delete(struct student*,int &amount);
void delete_student(struct student*,int index,int &amount);
void edit_student(struct student*,int amount);
void add_student(struct student*,int &amount);

void find(struct student*,int amount);
void part_find(struct student*,int amount);
void getstring(char* string,int size);
void string_to_lowercase(char *string);
void output_student(struct student pointer);

void header_sort(struct student*,int amount);
void sort_lastname(struct student*,int amount);
void sort_name(struct student*,int amount);
void sort_patronymic(struct student*,int amount);
void sort_address(struct student*,int amount);
void sort_groupnumber(struct student*,int amount);
void sort_rating(struct student*,int amount);


#endif /* Functions_hpp */
