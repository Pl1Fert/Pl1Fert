#include "Functions.h"

int menu(void)
{
    printf("\nChoose a number\n");
    printf("1-Enter info\n");
    printf("2-Output info\n");
    printf("3-Find selected record\n");
    printf("4-delete record\n");
    printf("5-Exit\n");
    printf("Your choice: ");
    return input_check_int();
}

struct dictionary input_info(void)
{
    struct dictionary pointer;
    do
    {
        printf("Еnter the original word: ");
        rewind(stdin);
        fgets(pointer.origin,30,stdin);
    }while(check_string_for_number(pointer.origin) == 1);
    
    do
    {
        printf("Еnter the translation of this word: ");
        rewind(stdin);
        fgets(pointer.translation,30,stdin);
    }while(check_string_for_number(pointer.translation) == 1);
    
    return pointer;
}

struct tree *push(struct tree *node,struct dictionary pointer)
{
    int comparison;
    
    if(node == NULL)
    {
        node = (struct tree*)malloc(sizeof(struct tree));
        
        strcpy(node -> record.origin, pointer.origin);
        strcpy(node -> record.translation, pointer.translation);
        
        node -> left = node -> right = NULL;
    }else
    {
        if((comparison = strcmp(pointer.origin,node -> record.origin)) < 0)
        {
                node -> left = push(node -> left,pointer);
        }
        
        if(comparison > 0)
        {
            node -> right = push(node -> right,pointer);
        }
    }
    
    node = tree_balance(node);
    return node;
}

void output_menu(struct tree *root)
{
    printf("1-recursive output\n");
    printf("2-non-recursive output\n");
    printf("3-exit\n");
    rewind(stdin);
    switch(input_check_int())
    {
        case 1:
            puts("\n");
            recursive_output(root);
            break;
        case 2:
            puts("\n");
            non_recursive_output(root);
            break;
        case 3:
            return;
    }
}

void recursive_output(struct tree *node)
{
    if(node != NULL)
    {
        output_record(node);
        recursive_output(node -> left);
        recursive_output(node -> right);
    }
}

void non_recursive_output(struct tree *node)
{
 
    struct stack
    {
        struct tree *tree;
        struct stack *next;
    };
    struct stack *stack_element, *tree_element = NULL;
    
 
    bool traffic = true;
 
    stack_element = (struct stack *)calloc(1, sizeof(struct stack));
    stack_element->tree = node;
    stack_element -> next = tree_element;
 
    output_record(node);
 
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
            
            output_record(node);
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

void output_record(struct tree *node)
{
    if (node == NULL)
    {
        printf("No records :(");
        return;
    }
     
    printf("Origin: %s\n", node -> record.origin);
    printf("Translation: %s\n\n", node -> record.translation);
    
}

int tree_height(struct tree *node)
{
    int height = 0;
    if(node != NULL)
    {
        int max_height = tree_height(node -> left) > tree_height(node -> right) ? tree_height(node -> left) : tree_height(node -> right);
        height = max_height + 1;
    }
    
    return height;
}

int tree_difference(struct tree *node)
{
    return tree_height(node -> right) - tree_height(node -> left);
}

struct tree * rotate_right(struct tree* node)
{
    struct tree *pointer = node -> left;
    node -> left = pointer -> right;
    pointer -> right = node;
    tree_height(pointer);
    tree_height(node);
    return pointer;
}

struct tree * rotate_left(struct tree* node)
{
    struct tree *pointer = node -> right;
    node -> right = pointer -> left;
    pointer -> left = node;
    tree_height(pointer);
    tree_height(node);
    return pointer;
}

struct tree * tree_balance(struct tree* node)
{
    tree_height(node);
    if(tree_difference(node) == 2)
    {
        if(tree_difference(node -> right) < 0)
            node -> right = rotate_right(node -> right);
        return rotate_left(node);
    }
    if(tree_difference(node) == -2)
    {
        if(tree_difference(node -> left) < 0)
            node -> left = rotate_left(node -> left);
        return rotate_right(node);
    }
    return node;
}

struct tree *search(struct tree *node,char string[])
{
    if(node != NULL)
    {
        int comparison = strcmp(node -> record.origin,string);
        
        if(comparison == 0) return node;
        
        if(comparison > 0) return search(node -> left,string);
        
        if(comparison < 0) return search(node -> right,string);
    }
    
    return NULL;
}

struct tree * minimum(struct tree *node)
{
    if (!node->left->left) return node;
    return minimum(node->left);
}

void deletion(struct tree **node,char string[])
{
    int comparison;
    if((*node) != NULL)
    {
        if((comparison = strcmp((*node) -> record.origin,string)) == 0)
        {
            struct tree *pointer = (*node);
            
            if ((*node) -> left == NULL && (*node) -> right == NULL ) (*node) = NULL;
            
            else if ((*node)->left == NULL) (*node) = pointer->right;

            else if ((*node)->right == NULL) (*node) = pointer->left;
            
            else
            {
                if(!(*node) -> right -> left)
                {
                    (*node) -> record = (*node) -> right -> record;
                    struct tree * temp = (*node) -> right -> right;
                    free((*node) -> right);
                    (*node) -> right = temp;
                }else{
                    struct tree *min = minimum((*node)-> right);
                    (*node) -> record = min -> left -> record;
                    free(min -> left);
                    min -> left = NULL;
                }
            }
            pointer = NULL;
            free(pointer);
            //pointer = NULL;
            deletion(node, string);
        }
        else
        {
            if(comparison < 0)
                deletion(&((*node) -> right),string);
            else
                deletion(&((*node) -> left),string);

        }
    }
}

void full_deletion(struct tree **node)
{
    if(!(*node))
        return;
    if((*node) -> left)
        full_deletion(&((*node) -> left));
    if((*node)->right)
        full_deletion(&((*node) -> right));
    //full_deletion(node);
    *node = NULL;
    free(*node);
}

int ClearStdin()
{
    int rv = 1;
    int ch;
    while (1)
    {
        ch = getchar();
        if (ch == '\n' || ch == EOF)
        {
            break;
        }
        rv = 0;
    }
    return rv;
}

int input_check_int()
{
    int read_count, is_empty;
    int number;
     
    while (1)
    {
         read_count = scanf("%d", &number);
         is_empty = ClearStdin();
         if (read_count == 1 && is_empty != 0 && number > 0)
         {
             break;
         }
         printf("Invalid number format. Please enter the number\n");
    }
    return number;
}

int input_check_int_for_sort()
{
    int read_count, is_empty;
    int number;
     
    while (1)
    {
         read_count = scanf("%d", &number);
         is_empty = ClearStdin();
         if (read_count == 1 && is_empty != 0 && (number == 1 || number == 2))
         {
             break;
         }
         printf("Invalid number format. Please enter the number\n");
    }
    return number;
}

int check_string_for_number(char *string)
{
    int i = 0;
    while(string[i])
    {
        if(isdigit(string[i]) != 0)
        {
            return 1;
        }
        i++;
    }
    return 0;
}

void string_to_lowercase(char *string)
{
    int i = 0;
    
    while(string[i])
    {
        string[i]=tolower(string[i]);
        i++;
    }
}
