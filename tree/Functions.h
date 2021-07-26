
#ifndef Functions_h
#define Functions_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct dictionary
{
    char origin[30];
    char translation[30];
};

struct tree
{
    struct dictionary record;
    struct tree* left;
    struct tree* right;
};

struct dictionary input_info(void);
void output_menu(struct tree *root);
void recursive_output(struct tree *node);
void non_recursive_output(struct tree *node);
void output_record(struct tree *node);
struct tree *push(struct tree *node,struct dictionary pointer);
struct tree *search(struct tree *node,char string[]);
void deletion(struct tree **node,char string[]);
void full_deletion(struct tree **node);
struct tree * minimum(struct tree *node);
int tree_height(struct tree *node);
int tree_difference(struct tree *node);
struct tree * rotate_right(struct tree* node);
struct tree * rotate_left(struct tree* node);
struct tree * tree_balance(struct tree* node);

int menu(void);
int ClearStdin(void);
int input_check_int(void);
int input_check_int_for_sort(void);
int check_string_for_number(char* string);
void string_to_lowercase(char *string);
int check_string(char *string);

#endif /* Functions_h */
