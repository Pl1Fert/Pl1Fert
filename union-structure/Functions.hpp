//
//  Functions.hpp
//  MainFile
//
//  Created by AlexeyRusel on 3/9/21.
//  Copyright © 2021 PL1Fert. All rights reserved.
//

#ifndef Functions_hpp
#define Functions_hpp

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
    };
    union types type;
    
    int flag;
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
void put_engine_volume(float num,struct car pointer);

void enter_struct(struct car*,int amount);
void output_struct(struct car*,int amount);
void add_car(struct car*,int &amount);
void find(struct car*,int amount);
void output_car(struct car pointer,int index);
void header_delete(struct car*,int &amount);
void delete_car(struct car*,int index,int &amount);
void find_max_engine_volume(struct car*,int amount);
void put_cost(float num,struct car* pointer);
void put_header(void);
#endif /* Functions_hpp */
