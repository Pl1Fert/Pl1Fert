#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

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
    struct tree_15 *left;
    struct tree_15 *right;
};

struct queue
{
    struct queue *next;
    char *string;
};

struct two_direction_ring
{
    int number;
    struct two_direction_ring *next;
    struct two_direction_ring *prev;
};

struct one_direction_ring
{
    int number;
    struct one_direction_ring *next;
};

struct library
{
    char author[20];
    char book_name[20];
    int year;
};

struct figures
{
    char name[20];
    union types
    {
        float radius;
        float perimetr;
    };
    union types type;
};

struct student
{
    struct marks *mark;
    struct group_info *group;
};

struct marks
{
    int marks[4];
};

struct group_info
{
    char name[20];
    char group_name[20];
};

typedef struct bField
{
    unsigned i0:1, i1:1, i2:1, i3:1, i4:1, i5:1, i6:1, i7:1, i8:1, i9:1, i10:1, i11:1, i12:1, i13:1, i14:1, i15:1;
} Field;

struct pole
{
    union
    {
        struct
        {
            unsigned i1 : 1;
            int : 1;
        } st1;
        struct
        {
            unsigned i1 : 2;
        } st2;
    } un;
    int: size - 2;
    //#define size sizeof(int)*8
};


////////////////////////////////////////////////////////////////////////////////

// ВОПРОС 1.1

int main()
{
    char filename[20];
    fgets(filename,20,stdin);
    strcat(filename,".bin");
    FILE *firstfile,*secondfile,*thirdfile;
    
    if(!(firstfile = fopen(filename,"rb")))
    {
        return 0;
    }
    if(!(secondfile = fopen(filename,"rb")))
    {
        return 0;
    }
    if(!(thirdfile = fopen(filename,"wb")))
    {
        return 0;
    }
    
    int k = sizeof(int);
    
    int buf1,buf2;
    fpos_t pos;
    rewind(firstfile);
    fseek(firstfile,-k,2);
    fgetpos(firstfile, &pos);
    fread(&buf1,sizeof(int),1,firstfile);
    rewind(secondfile);
    fread(&buf2,sizeof(int),1,secondfile);
    
    do
    {
        while(!feof(secondfile) && buf2 > buf1)
        {
            fwrite(&buf2, sizeof(int), 1, thirdfile);
            fread(&buf2,sizeof(int),1,secondfile);
        }
        
        if(feof(secondfile))break;
        
        while(pos >= 0 && buf2 <= buf1)
        {
            fwrite(&buf1, sizeof(int), 1, thirdfile);
            fseek(firstfile,-k * 2,1);
            fgetpos(firstfile, &pos);
            if(pos < 0) break;
            fread(&buf1,sizeof(int),1,firstfile);
        }
        
        
    }while(pos > 0);
    
    while(!feof(secondfile))
    {
        fwrite(&buf2, sizeof(int), 1, thirdfile);
        fread(&buf2,sizeof(int),1,secondfile);
    }
    
    while(pos >= 0)
    {
        fwrite(&buf1, sizeof(int), 1, thirdfile);
        fseek(firstfile,-k * 2,1);
        fgetpos(firstfile, &pos);
        if(pos < 0) break;
        fread(&buf1,sizeof(int),1,firstfile);
    }
    
    fclose(firstfile);
    fclose(secondfile);
    fclose(thirdfile);
    
    return 0;
}

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

int main()
{
    char filename[20];
    fgets(filename,20,stdin);
    strcat(filename,".txt");
    FILE *firstfile,*secondfile,*thirdfile;
    
    if(!(firstfile = fopen(filename,"r")))
    {
        return 0;
    }
    if(!(secondfile = fopen(filename,"r")))
    {
        return 0;
    }
    if(!(thirdfile = fopen(filename,"w")))
    {
        return 0;
    }
    
    
    int buf1,buf2;
    fpos_t pos1,pos2;
    
    fseek(firstfile,-2,2);
    fseek(secondfile,-2,2);
    
    fgetpos(firstfile, &pos1);
    fgetpos(secondfile, &pos2);
    
    fscanf(firstfile,"%d", &buf1);
    fscanf(secondfile,"%d", &buf2);
    
    do
    {
        while(pos1 > 0 && buf1 > buf2)
        {
            fprintf(thirdfile,"%d",buf1);
            pos1 -= 2;
            fsetpos(firstfile,&pos1);
            fscanf(firstfile,"%d", &buf1);
        }
        
        while(pos2 > 0 && buf2 >= buf1)
        {
            fprintf(thirdfile,"%d",buf2);
            pos2 -= 2;
            fsetpos(secondfile,&pos2);
            fscanf(secondfile,"%d", &buf2);
        }
    }while(pos1 > 0 || pos2 > 0);
    
    while(pos1 > 0)
    {
        fprintf(thirdfile,"%d",buf1);
        pos1 -= 2;
        fsetpos(firstfile,&pos1);
        fscanf(firstfile,"%d", &buf1);
    }
    
    while(pos2 > 0)
    {
        fprintf(thirdfile,"%d",buf2);
        pos2 -= 2;
        fsetpos(secondfile,&pos2);
        fscanf(secondfile,"%d", &buf2);
    }
    
    fclose(firstfile);
    fclose(secondfile);
    fclose(thirdfile);
    
    return 0;
}

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

int main()
{
    char filename[20];
    fgets(filename,20,stdin);
    strcat(filename,".txt");
    FILE *file;
    
    if(!(file = fopen(filename,"w+")))
    {
        return 0;
    }
    
    
    int buf1,buf2,minbuf;
    fpos_t pos1,pos2,minpos;
    
    rewind(file);
    
    while(1)
    {
        fgetpos(file, &pos1);
        fscanf(file,"%d", &buf1);
        if(feof(file))break;
        minbuf = buf1;
        minpos = pos1;
        while(1)
        {
            fgetpos(file, &pos2);
            fscanf(file,"%d", &buf2);
            if(feof(file))break;
            if(buf1 > buf2)
            {
                minpos = pos2;
                minbuf = buf2;
            }
        }
        
        if(pos1 != minpos)
        {
            fsetpos(file,&pos1);
            fprintf(file,"%d",minbuf);
            fsetpos(file,&minpos);
            fprintf(file,"%d",buf1);
        }
        pos1+=2;
        fsetpos(file,&pos1);
    }
    fclose(file);
    return 0;
}
// ВОПРОС 3.1 c черточкой

int main()
{
    char filename[20];
    fgets(filename,20,stdin);
    strcat(filename,".txt");
    FILE *file;
    
    if(!(file = fopen(filename,"w+")))
    {
        return 0;
    }
    
    
    int buf1,buf2;
    fpos_t pos1,pos2;
    
    rewind(file);
    fseek(file, 2, 0);
    
    while(1)
    {
        fgetpos(file, &pos1);
        fscanf(file,"%d", &buf1);
        if(feof(file))rewind(file);
        
        pos2 = pos1 - 2;
        fsetpos(file,&pos2);
        while(pos2 >= 0)
        {
            fgetpos(file, &pos2);
            fscanf(file,"%d", &buf2);
            if(buf2 > buf1)
            {
                pos2 +=2;
                fsetpos(file,&pos2);
                fprintf(file,"%d",buf2);
                buf2 -= 2;
            }else
                break;
            pos2 -= 2;
            if(pos2 >= 0) fgetpos(file, &pos2);
        }
        pos2 += 2;
        fsetpos(file,&pos2);
        fprintf(file,"%d",buf2);
        pos1 += 2;
        if(pos1 >= filelength(fileno(file))) break;
        fsetpos(file,&pos1);
    }
    
    fclose(file);
    return 0;
}

// ВОПРОС 3.2

void non_recursive_output(struct inttree *node)
{
    if(!node)return;
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

void deletion(struct two_direction_ring **first, int number)
{
    if (!(*first))return;
    
    //struct two_direction_ring *prev,*next;
    struct two_direction_ring *pointer = (*first);
    
    for(int i = 1;i < number && pointer -> next != (*first);i++)
        pointer = pointer -> next;
    
    if(pointer)
    {
        if(pointer -> next == (*first))
        {
            (*first) = NULL;
            free(pointer);
            return;
        }

        pointer->prev->next = pointer->next;
        pointer->next->prev = pointer->prev;
        
        free(pointer);
    }
}

// ВОПРОС 5.1

// ВОПРОС 5.2 возможно

void non_recursive_output(struct inttree *node)
{
    if(!node)return;
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
    //printf("%d",node -> number);
    
 
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

// ВОПРОС 6.1

// ВОПРОС 6.2

void sort_queue(struct queue **head)
{
    if (!(*head))
        return;
    struct queue *pointer1 = (*head);
    struct queue *pointer2;
    struct queue *buf = NULL;
    struct queue *flag = NULL;
    struct queue *pointer3 = (*head);


    for(;pointer1 -> next;pointer1 = pointer1 -> next)
    {
        for(pointer2 = pointer1 -> next; pointer2 ;pointer2 = pointer2 -> next,pointer3 = pointer3 -> next)
        {
            if(pointer2 == pointer1 -> next) pointer3 = pointer1;
            if((strcmp(pointer1 -> string,pointer2 -> string) > 0))
            {
                pointer3 -> next = pointer2 -> next;
                pointer2 -> next = pointer1;
                buf -> next = pointer2;
                pointer1 = pointer2;
            }
        }
        if(!flag)
        {
            flag = pointer1;
            free(buf);
        }
        buf = pointer1;
    }
    *head = flag;
}

// ВОПРОС 7.1

// ВОПРОС 7.2

void sort_two_direction_ring(struct two_direction_ring **first)
{
    if (!(*first))
        return;
    
    struct two_direction_ring * pointer1,*pointer2,*pointer3;
    
    pointer1 = (*first);
    
    do
    {
        pointer2 = pointer1 -> next;
        pointer3 = pointer1;
        do
        {
            if(pointer3 -> number > pointer2 -> number) pointer3 = pointer2;
            pointer2 = pointer2 -> next;
        }while(pointer2 != (*first));
        if(pointer3 != pointer1)
        {
            if((*first) == pointer1) (*first) = pointer3;
            pointer3 -> prev -> next = pointer3 -> next;
            pointer3 -> next -> prev = pointer3 -> prev;
            pointer1 -> prev -> next = pointer3;
            pointer3 -> next = pointer1;
            pointer3 -> prev = pointer1 -> prev;
            pointer1 -> prev = pointer3;
        }else
        {
            pointer1 = pointer1 -> next;
        }
    }while(pointer1 -> next != (*first));
}

// ВОПРОС 8.1

// ВОПРОС 8.2

void deletion(struct one_direction_ring **first,int number)
{
    if (!(*first)) return;
    
    //struct one_direction_ring *prev,*next;
    struct one_direction_ring *pointer = (*first);
    struct one_direction_ring *temp = (*first);
    
    for(int i = 1;i < number && pointer -> next != (*first);i++)
        pointer = pointer -> next;
    
    for(;temp -> next != pointer;)
        temp = temp -> next;
    
    if(pointer && temp)
    {
        if(pointer -> next == (*first))
        {
            (*first) = NULL;
            free(pointer);
            free(temp);
            return;
        }
        temp -> next = pointer -> next;
        free(pointer);
        free(temp);
    }
}

// ВОПРОС 9.1

// ВОПРОС 9.2

int main(int argc, char *argv[])
{
    float square_circle;
    struct figures *pointer;
    
    pointer = (struct figures*)malloc(10*sizeof(struct figures));
    
    for(int i = 1;i < 11;i++)
    {
        strcpy(pointer[i].name,argv[i]);
        if(strcmp(pointer[i].name,"circle") == 0)
        {
            scanf("%f",&(pointer[i].type.radius));
            square_circle = pointer[i].type.radius * pointer[i].type.radius * 3.14;
            printf("%f",square_circle);
        }
        
        if(strcmp(pointer[i].name,"rectangle") == 0)
        {
            scanf("%f",&(pointer[i].type.perimetr));
        }
    }
    return 0;
}

// ВОПРОС 10.1

// ВОПРОС 10.2

void deletion(struct queue **top,struct queue **last)
{
    if (!(*top))
    {
        return;
    }
    
    int number;
    scanf("%d",&number);
    
    struct queue *pointer = *top;
    struct queue *temp;

    for(int i = 1;i < number && pointer != NULL;i++)
    {
        pointer = pointer -> next;
    }
    
    if(pointer)
    {
        if(pointer == *top)
        {
            (*top) = (*top) -> next;

            free(pointer);
            return;
        }
        
        if (pointer == *last)
        {
            temp = (*top);
            while (temp -> next != pointer) temp = temp -> next;
            *last = temp;
            (*last) -> next = pointer -> next;

            free(temp);
            free(pointer);
            return;
        }
        
        if(pointer != *top && pointer != *last)
        {
            temp = (*top);
            while(temp -> next != pointer) temp = temp -> next;
            temp -> next = pointer -> next;

            free(temp);
            free(pointer);
            return;
        }
    }
}

// ВОПРОС 11.1

// ВОПРОС 11.2

// ВОПРОС 12.1

// ВОПРОС 12.2

struct inttree *nonRecursiveCreation(struct inttree *root, int num)
{
    struct inttree *tempRoot1, *tempRoot2;

    tempRoot1 = (struct inttree *)malloc(sizeof(struct inttree));
    tempRoot1 -> number = num;
    tempRoot1 -> left = tempRoot1 -> right = NULL;

    if (root == NULL)
        return tempRoot1;
    else {
        tempRoot2 = root;

        while (tempRoot2)
        {
            if (tempRoot1 -> number == tempRoot2 -> number)
            {
                free(tempRoot1);
                break;
            }
            else {
                if (tempRoot1 -> number < tempRoot2 -> number)
                    if (tempRoot2 -> left == NULL)
                    {
                        tempRoot2 -> left = tempRoot1;
                        tempRoot2 = NULL;
                    } else
                        tempRoot2 = tempRoot2 -> left;
                else
                {
                    if (tempRoot2 -> right == NULL)
                    {
                        tempRoot2 -> right = tempRoot1;
                        tempRoot2 = NULL;
                    }
                    else
                        tempRoot2 = tempRoot2 -> right;
                }
            }
        }
        return root;
    }
}

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

int main(int argc,char *argv[])
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

// ВОПРОС 15.1  переделать

int main()
{
    char filename[20];
    fgets(filename,20,stdin);
    strcat(filename,".txt");
    FILE *file;
    
    if(!(file = fopen(filename,"w+")))
    {
        return 0;
    }
    
    
    int buf1,buf2,buf;
    fpos_t pos1,pos2;
    
    rewind(file);
    fgetpos(file, &pos1);
    fscanf(file,"%d", &buf1);
        
    rewind(file);
    fseek(file,-2,2);
    fgetpos(file, &pos2);
    fscanf(file,"%d", &buf2);
    rewind(file);
    
    while(pos2 >= 0 || pos1 <= filelengh(fileno(file)))
    {
        fsetpos(file, &pos1);
        fprintf(file,"%d",buf2);
        fsetpos(file, &pos2);
        fprintf(file,"%d",buf1);
        pos1+=2;
        pos2-=2;
        fsetpos(file, &pos1);
        fgetpos(file, &pos1);
        fscanf(file,"%d", &buf1);
        rewind(file);
        fsetpos(file, &pos2);
        fgetpos(file, &pos2);
        fscanf(file,"%d", &buf2);
    }
    
    fclose(file);
    return 0;
}

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

int main()
{
    struct pole *pl;
    int k = 27;
    pl = (struct pole *)&k;
    printf("\nостаток от деления на 2 = %u\n", (unsigned int)pl->un.st1.i1);
    printf("остаток от деления на 4 = %u\n", (unsigned int)pl->un.st2.i1);
    return 0;
}

// ВОПРОС 16.2

void print(struct stringtree *node,char* filename)
{
    FILE *file;
    if(!(file = fopen(filename,"w")))
        return;
    
       struct stack
       {
           struct stringtree *tree;
           struct stack *next;
       };
       struct stack *stack_element, *tree_element = NULL;
       
    
       bool traffic = true;
    
       stack_element = (struct stack *)calloc(1, sizeof(struct stack));
       stack_element->tree = node;
       stack_element -> next = tree_element;
    
       //output_record(node);
        fprintf(file,"%s",node -> string);
       
    
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
               fprintf(file,"%s",node -> string);
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
    
    fclose(file);
}

int main(int argc,char **argv)
{
    struct stringtree *root = NULL;
    char *filename = (char*)malloc(strlen(argv[1])+1);
    strcpy(filename,argv[1]);
    strcat(filename,".txt");
    FILE *file;
    if(!(file = fopen(filename,"r")))
    {
        return 0;
    }
    
    print(root,filename);
    
    fclose(file);
    return 0;
}

// ВОПРОС 17.1

// ВОПРОС 17.2

void create(struct two_direction_ring **first)
{
    int ask,number;
    scanf("%d",&ask);
    if(ask == 1)return;
    
    struct two_direction_ring *pointer = (struct two_direction_ring*)malloc(sizeof(struct two_direction_ring));
    scanf("%d",&number);
    
    pointer -> number = number;
    
    if(!(*first))
    {
        pointer -> next = pointer -> prev = pointer;
        (*first) = pointer;
    }else
    {
        pointer -> next = (*first) -> next;
        (*first) -> next -> prev = pointer;
        (*first) -> next = pointer;
        pointer -> prev = (*first);
    }
    
    create(first);
}

// ВОПРОС 18.1

void print (Field *pl)
{
    printf(" %d %d %d %d %d %d %d %d    %d %d %d %d %d %d %d %d\n",
           pl->i15, pl->i14, pl->i13, pl->i12, pl->i11, pl->i10, pl->i9,
           pl->i8, pl->i7, pl->i6, pl->i5, pl->i4, pl->i3, pl->i2, pl->i1, pl->i0);
}

int main()
{

    char alphabet[33];
    int code = 224;

    Field *pl;

    for(int i = 0; i < 33; i++)
    {
        alphabet[i] = (char)code;
        printf("%c -", alphabet[i]);
        code++;

        pl = (Field *)&alphabet[i];

        print(pl);
    }
    return 0;
}

// ВОПРОС 18.2

// ВОПРОС 19.1

void deletion(struct queue **top,struct queue **last)
{
    if (!(*top))
    {
        return;
    }
    
    int number;
    scanf("%d",&number);
    
    struct queue *pointer = *top;
    struct queue *temp;

    for(int i = 1;i < number && pointer != NULL;i++)
    {
        pointer = pointer -> next;
    }
    
    if(pointer)
    {
        if(pointer == *top)
        {
            (*top) = (*top) -> next;

            free(pointer);
            return;
        }
        
        if (pointer == *last)
        {
            temp = (*top);
            while (temp -> next != pointer) temp = temp -> next;
            *last = temp;
            (*last) -> next = pointer -> next;

            free(temp);
            free(pointer);
            return;
        }
        
        if(pointer != *top && pointer != *last)
        {
            temp = (*top);
            while(temp -> next != pointer) temp = temp -> next;
            temp -> next = pointer -> next;

            free(temp);
            free(pointer);
            return;
        }
    }
}

// ВОПРОС 19.2

void add(struct library **pointer,int amount)
{
    if((*pointer) == NULL)
    {
        amount++;
        (*pointer) = (struct library*)malloc(amount*sizeof(struct library));
    }
    else
    {
        (*pointer) = (struct library*)realloc((*pointer),(amount+1) * sizeof(struct library));
    }
    fgets((*pointer) -> author,20,stdin);
    fgets((*pointer) -> book_name,20,stdin);
    scanf("%d",&((*pointer) -> year));
}

void sort_library(struct library *pointer,int amount)
{
    struct library temp;
    
    for(int i = 0; i< amount-1;i++)
        for(int j = 1; j< amount; j++)
        {
            if(strcmp(pointer[i].author,pointer[j].author) > 0)
            {
                temp = pointer[i];
                pointer[i] = pointer[j];
                pointer[j] = temp;
            }
        }
}

int main()
{
    int ask;
    int amount = 0;
    struct library *pointer = NULL;
    do
    {
        add(&pointer,&amount); // похуй на си файл закину ссылку он схавает
        scanf("%d",&ask);
    }while(ask == 1);
}

// ВОПРОС 20.1

// ВОПРОС 20.2

// ВОПРОС 21.1

int main()
{
    char filename[20];
    fgets(filename,20,stdin);
    strcat(filename,".bin");
    FILE *firstfile,*secondfile,*thirdfile;
    
    if(!(firstfile = fopen(filename,"rb")))
    {
        return 0;
    }
    if(!(secondfile = fopen(filename,"rb")))
    {
        return 0;
    }
    if(!(thirdfile = fopen(filename,"wb")))
    {
        return 0;
    }
    
    int k = sizeof(int);
    
    int buf1,buf2;
    fpos_t pos1,pos2;
    rewind(firstfile);
    fseek(firstfile,-k,2);
    fseek(secondfile,-k,2);
    fgetpos(firstfile, &pos1);
    fgetpos(secondfile, &pos2);
    fread(&buf1,sizeof(int),1,firstfile);
    rewind(secondfile);
    fread(&buf2,sizeof(int),1,secondfile);
    
    do
    {
        while(pos1 > 0 && buf1 > buf2)
        {
            fwrite(&buf1, sizeof(int), 1, thirdfile);
            fseek(firstfile,-k * 2,1);
            fgetpos(firstfile, &pos1);
            if(pos1 < 0) break;
            fread(&buf1,sizeof(int),1,firstfile);
        }
        
        if(feof(secondfile))break;
        
        while(pos2 > 0 && buf1 <= buf2)
        {
            fwrite(&buf2, sizeof(int), 1, thirdfile);
            fseek(secondfile,-k * 2,1);
            fgetpos(secondfile, &pos2);
            if(pos2 < 0) break;
            fread(&buf2,sizeof(int),1,secondfile);
        }
        
        
    }while(pos1 > 0 || pos2 > 0);
    
    while(pos1 > 0 )
    {
        fwrite(&buf1, sizeof(int), 1, thirdfile);
        fseek(firstfile,-k * 2,1);
        fgetpos(firstfile, &pos1);
        if(pos1 < 0) break;
        fread(&buf1,sizeof(int),1,firstfile);
    }
    
    while(pos2 > 0)
    {
        fwrite(&buf2, sizeof(int), 1, thirdfile);
        fseek(secondfile,-k * 2,1);
        fgetpos(secondfile, &pos2);
        if(pos2 < 0) break;
        fread(&buf2,sizeof(int),1,secondfile);
    }
    
    fclose(firstfile);
    fclose(secondfile);
    fclose(thirdfile);
    
    return 0;
}
// ВОПРОС 21.2

int main()
{
    int amount;

    scanf("%d",&amount);
    struct student *pointer;
    pointer = (struct student*)malloc(amount*sizeof(struct student));
    
    for(int i = 0; i< amount;i++)
    {
        rewind(stdin);
        fgets(pointer[i].group -> name,20,stdin);
        rewind(stdin);
        fgets(pointer[i].group -> group_name,20,stdin);
        
        for(int j = 0;j<4;j++)
        {
            scanf("%d",&(pointer[i].mark -> marks[j]));
        }
    }
    
    int max_mark = 0,max_student;
    
    for(int i = 0;i < amount;i++)
    {
        for(int j = 0;j < 4;j++)
        {
            if(max_mark < pointer[i].mark -> marks[j])
            {
                max_mark = pointer[i].mark -> marks[j];
                max_student = i;
            }
        }
    }
    
    return 0;
}

// ВОПРОС 22.1

// ВОПРОС 22.2

void sort_two_direction_ring(struct two_direction_ring **first)
{
    if (!(*first))
        return;
    
    struct two_direction_ring * pointer1,*pointer2,*pointer3;
    
    pointer1 = (*first);
    
    do
    {
        pointer2 = pointer1 -> next;
        pointer3 = pointer1;
        do
        {
            if(pointer3 -> number > pointer2 -> number) pointer3 = pointer2;
            pointer2 = pointer2 -> next;
        }while(pointer2 != (*first));
        
        if(pointer3 != pointer1)
        {
            if((*first) == pointer1) (*first) = pointer3;
            pointer3 -> prev -> next = pointer3 -> next;
            pointer3 -> next -> prev = pointer3 -> prev;
            pointer1 -> prev -> next = pointer3;
            pointer3 -> next = pointer1;
            pointer3 -> prev = pointer1 -> prev;
            pointer1 -> prev = pointer3;
        }else
        {
            pointer1 = pointer1 -> next;
        }
    }while(pointer1 -> next != (*first));
}

// ВОПРОС 23.1

// ВОПРОС 23.2

void sort_one_direction_ring(struct one_direction_ring **first)
{
    if (!(*first))
        return;
    
    struct one_direction_ring *pointer1,*pointer2,*pointer3,*pointer4,*pointer5,*pointer6;
    
    pointer1 = (*first);
    pointer2 = pointer1 -> next;
    
    while(pointer2 -> next != (*first))
        pointer2 = pointer2 -> next;
    do
    {
        pointer3 = pointer1 -> next;
        pointer4 = pointer1;
        pointer5 = pointer1;
        do
        {
            if(pointer5 -> number > pointer3 -> number)
            {
                pointer5 = pointer3;
                pointer6 = pointer4;
            }
            pointer3 = pointer3 -> next;
            pointer4 = pointer4 -> next;
        }while(pointer3 != (*first));
        if(pointer5 != pointer1)
        {
            if((*first) == pointer1) (*first) = pointer5;
            
            pointer2 -> next = pointer5;
            pointer6 -> next = pointer5 -> next;
            pointer5 -> next = pointer1;
            pointer2 = pointer5;
        }else
        {
            pointer1 = pointer1 -> next;
            pointer2 = pointer2 -> next;
        }
    }while(pointer1 -> next != (*first));

}


