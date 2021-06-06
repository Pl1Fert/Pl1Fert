#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct inttree
{
    int number;
    struct inttree *left;
    struct inttree *right;
};

struct stringtree
{
    char string[20];
    struct inttree *left;
    struct inttree *right;
};

struct tree_15
{
    char surname[20];
    int year;
    struct inttree *left;
    struct inttree *right;
};

// ВОПРОС 1.1

// ВОПРОС 1.2


void output(struct inttree *root)
{
    if(root != NULL)
    {
        output(root -> left);
        printf("%d",root -> number);
        output(root -> right);
    }
}

// ВОПРОС 2.1

// ВОПРОС 2.2

void deletion(struct inttree **node,int key)
{
    if((*node) != NULL)
    {
        if((*node) -> number == key)
        {
            struct inttree *pointer = (*node);
            
            if ((*node) -> left == NULL && (*node) -> right == NULL ) (*node) = NULL;
            
            else if ((*node)->left == NULL) (*node) = pointer->right;

            else if ((*node)->right == NULL) (*node) = pointer->left;
            
            else
            {
                // переносим "вершину" на правого потомка
                (*node) = pointer -> right;
                // создаем адресную переменную
                struct inttree **reserve;
                // передаем адрес вершины созданной переменной
                reserve = node;
                // до тех пор, пока не достигнем конца левой части дерева
                // присваиваем адреса левых потомков адресной переменной
                while (*reserve != NULL)
                        reserve = &((*reserve) -> left);
                // после чего присваиваем указатель на самого левого потомка
                (*reserve) = pointer -> left;
            }
            free(pointer);
            deletion(node, key);
        }
        else
        {
            if((*node) -> number < key)
                deletion(&((*node) -> right),key);
            else
                deletion(&((*node) -> left),key);

        }
    }
}

// ВОПРОС 3.1

// ВОПРОС 3.2

void non_recursive_output(struct inttree *node)
{
 
    struct stack
    {
        struct inttree *tree;
        struct stack *next;
    };
    struct stack *stack_element, *tree_element = NULL;
    
 
    bool traffic = true;
 
    stack_element = (struct stack *)calloc(1, sizeof(struct stack));
    stack_element->tree = node;
    stack_element -> next = tree_element;
 
    //output_record(node);
    printf("%d",node -> number);
    
 
    while (stack_element || node -> right)
    {
        while(node -> left || node -> right)
        {
            if(traffic && node -> left)
                node = node -> left;
 
            else if(node -> right)
                node = node -> right;
            
            traffic = true;
 
            if(node -> left && node -> right)
            {
                tree_element = stack_element;
                stack_element = (struct stack *)calloc(1, sizeof(struct stack));
                stack_element -> tree = node;
                stack_element -> next = tree_element;
            }
            
            //output_record(node);
            printf("%d",node -> number);
        }
 
        if (stack_element)
        {
            node = stack_element -> tree;
            tree_element = stack_element -> next;
            free(stack_element);
        }
 
        stack_element = tree_element;
 
        if (node -> left && node -> right)
            traffic = false;
        else
            break;
    }
}

// ВОПРОС 4.1

// ВОПРОС 4.2

// ВОПРОС 5.1

// ВОПРОС 5.2

// ВОПРОС 6.1

// ВОПРОС 6.2

// ВОПРОС 7.1

// ВОПРОС 7.2

// ВОПРОС 8.1

// ВОПРОС 8.2

// ВОПРОС 9.1

// ВОПРОС 9.2

// ВОПРОС 10.1

// ВОПРОС 10.2

// ВОПРОС 11.1

// ВОПРОС 11.2

// ВОПРОС 12.1

// ВОПРОС 12.2

// ВОПРОС 13.1

// ВОПРОС 13.2

// ВОПРОС 14.1

// ВОПРОС 14.2

struct stringtree *input(struct stringtree *node,char temp[])
{
    int comparison;
    if(node == NULL)
    {
        node = (struct stringtree*)malloc(sizeof(struct stringtree));
        node -> left = node -> right = NULL;
        strcpy(node -> string,temp);
    }else
    {
        if((comparison = strcmp(temp,node -> string)) < 0)
        {
                node -> left = input(node -> left,temp);
        }
        
        if(comparison > 0)
        {
            node -> right = input(node -> right,temp);
        }
    }
    return node;
}

int main(int argc,char **argv)
{
    struct stringtree *root = NULL;
    char temp[20];
    char *filename = (char*)malloc(strlen(argv[1])+1);
    strcpy(filename,argv[1]);
    strcat(filename,".txt");
    FILE *file;
    if(!(file = fopen(filename,"r")))
    {
        return 0;
    }
       
    while((fscanf(file,"s",temp)) == 1)
          root = input(root,temp);
    
    fclose(file);
    return 0;
}

// ВОПРОС 15.1

// ВОПРОС 15.2

struct tree_15 *push(struct tree_15 *node,int number,char string[20])
{
    int comparison;

    if(node == NULL)
    {
        node = (struct tree_15*)malloc(sizeof(struct tree_15));
        node -> left = node -> right = NULL;
        
        node -> year = number;
        strcpy(node -> surname,string);
    }else
    {
        if((comparison = strcmp(string,node -> surname)) < 0)
        {
                node -> left = push(node -> left,number,string);
        }
        
        if(comparison > 0)
        {
            node -> right = push(node -> right,number,string);
        }
    }
    
    return node;
}

int main()
{
    int number;
    char string[20];
    struct tree_15 *root = NULL;
    fgets(string,20,stdin);
    scanf("%d",&number);
    root = push(root,number,string);
    return 0;
}


// ВОПРОС 16.1

// ВОПРОС 16.2

void print(struct stringtree *node,char* filename,FILE *file)
{
    if(!(file = fopen(filename,"wb")))
        return;
    
    fclose(file);
}

int main(int argc,char **argv)
{
    struct stringtree *root = NULL;
    char *filename = (char*)malloc(strlen(argv[1])+1);
    strcpy(filename,argv[1]);
    strcat(filename,".bin");
    FILE *file;
    if(!(file = fopen(filename,"rb")))
    {
        return 0;
    }
    
    print(root,filename,file);
    
    fclose(file);
    return 0;
}

// ВОПРОС 17.1

// ВОПРОС 17.2

// ВОПРОС 18.1

// ВОПРОС 18.2

// ВОПРОС 19.1

// ВОПРОС 19.2

// ВОПРОС 20.1

// ВОПРОС 20.2

// ВОПРОС 21.1

// ВОПРОС 21.2

// ВОПРОС 22.1

// ВОПРОС 22.2

// ВОПРОС 23.1

// ВОПРОС 23.2
