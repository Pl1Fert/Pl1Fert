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

struct two_direction_queue
{
    struct two_direction_queue *next;
    struct two_direction_queue *prev;
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
            //fseek(firstfile,-k * 2,1);
            pos-=k;
            fsetpos(firstfile, &pos);
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
        //fseek(firstfile,-k * 2,1);
        pos-=k;
        fsetpos(firstfile, &pos);
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

//int main()
//{
//    char filename[20];
//    fgets(filename,20,stdin);
//    strcat(filename,".txt");
//    FILE *file;
//
//    if(!(file = fopen(filename,"w+")))
//    {
//        return 0;
//    }
//
//
//    int buf1,buf2;
//    fpos_t pos1,pos2;
//
//    rewind(file);
//    fseek(file, 2, 0);
//
//    while(1)
//    {
//        fgetpos(file, &pos1);
//        fscanf(file,"%d", &buf1);
//        if(feof(file))rewind(file);
//
//        pos2 = pos1 - 2;
//        fsetpos(file,&pos2);
//        while(pos2 >= 0)
//        {
//            fgetpos(file, &pos2);
//            fscanf(file,"%d", &buf2);
//            if(buf2 > buf1)
//            {
//                pos2 +=2;
//                fsetpos(file,&pos2);
//                fprintf(file,"%d",buf2);
//                pos2 -= 2;
//            }else
//                break;
//            pos2 -= 2;
//            if(pos2 >= 0) fsetpos(file, &pos2);
//        }
//        pos2 += 2;
//        fsetpos(file,&pos2);
//        fprintf(file,"%d",buf1);
//        pos1 += 2;
//        if(pos1 >= filelength(fileno(file))) break;
//        fsetpos(file,&pos1);
//    }
//
//    fclose(file);
//    return 0;
//}

void main()
{
    FILE *f;
    int i=1,j,k,kk,flag=0,ind;
    f=fopen("aaa.txt","r+");
     while(1)
     {
         fseek (f,3*i,0);
          fscanf (f,"%3d",&k);
          if (feof(f)) flag=1;
          j=i-1;
          fseek (f,3*j,0);
          fscanf (f,"%3d",&kk);
          ind=0;
          while (j>=0 && k<kk)
          {
              fseek (f,3*(j+1),0);
               fprintf (f,"%3d",kk);
               j--;
               if (j<=0) rewind(f);
               else
                   fseek (f,3*j,0);
               fscanf (f,"%3d",&kk);
               ind=1;
          }
            if (ind)
            {
                fseek (f,3*(j+1),0);
               fprintf (f,"%3d",k);
            }
              if (flag) break;
              
                 i++;
     }
 fclose(f);
    
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

int main()
{
    char filename[20];
    fgets(filename,20,stdin);
    strcat(filename,".bin");
    FILE *file;
    
    if(!(file = fopen(filename,"w+b")))
    {
        return 0;
    }
    
    int k = sizeof(int);
    int buf1,buf2;
    fpos_t pos1,pos2;
    
    rewind(file);
    fseek(file, k, 0);
    
    while(1)
    {
        fgetpos(file, &pos1);
        fread(&buf1,sizeof(int),1,file);
        if(feof(file))rewind(file);
        
        pos2 = pos1 - k;
        fsetpos(file,&pos2);
        while(pos2 >= 0)
        {
            fgetpos(file, &pos2);
            fread(&buf2,sizeof(int),1,file);
            if(buf2 > buf1)
            {
                pos2 +=k;
                fsetpos(file,&pos2);
                fwrite(&buf2, sizeof(int), 1,file);
                pos2 -= k;
            }else
                break;
            pos2 -= k;
            if(pos2 >= 0) fsetpos(file, &pos2);
        }
        pos2 += k;
        fsetpos(file,&pos2);
        fwrite(&buf1, sizeof(int), 1,file);
        pos1 += k;
        if(pos1 >= filelength(fileno(file))) break;
        fsetpos(file,&pos1);
    }
    
    fclose(file);
    return 0;
}

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
        pointer->prev->next = pointer->next;
        pointer->next->prev = pointer->prev;
        
        free(pointer);
    }
}

// ВОПРОС 5.1

int main()
{
    char filename[20];
    fgets(filename,20,stdin);
    strcat(filename,".bin");
    FILE *file;
    
    if(!(file = fopen(filename,"w+b")))
    {
        return 0;
    }
    int ask;
    int k = sizeof(int);
    int buf1,buf2;
    fpos_t pos1,pos2;
    
    rewind(file);
    
    while(1)
    {
        scanf("%d",&ask);
        if(ask == 999)break;
        
        while(1)
        {
            fgetpos(file, &pos1);
            fread(&buf1,sizeof(int),1,file);
            if(feof(file) || buf1 > ask )break;
        }
        rewind(file);
        
        if(buf1 < ask)
        {
            fseek(file, 0, 2);
            fwrite(&ask, sizeof(int), 1,file);
            continue;
        }
        fseek(file, -k, 2);
        
        do
        {
            fgetpos(file, &pos2);
            fread(&buf1,sizeof(int),1,file);
            rewind(file);
            pos2 +=k;
            fsetpos(file, &pos2);
            fwrite(&buf1, sizeof(int), 1,file);
            fseek(file,pos2 - 2*k,0);
        }while(pos1 < pos2 - k);
        
        fseek(file, pos2 - k, 0);
        fwrite(&ask, sizeof(int), 1,file);
    }
    fclose(file);
    return 0;
}

// ВОПРОС 5.2 неправильно


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

int main(int argc,char *argv[])
{
    char *filename = (char*)malloc(strlen(argv[1])+1);
    strcpy(filename,argv[1]);
    strcat(filename,".bin");
    FILE *file;
    
    int min = atoi(argv[2]);
    int max = atoi(argv[3]);
    int buf;
    
    int /*i1 = 0,i2 = 0,*/cutSize = 0;
    
    if(!(file = fopen(filename,"rb+")))
    {
        return 0;
    }
    
//    while(1)
//    {
//        fread(&buf,sizeof(int),1,file);
//        if(feof(file))break;
//        fseek(file,i1,0);
//        fwrite(&buf, sizeof(int), 1,file);
//        fseek(file,++i2,0);
//        if(buf < min || buf > max)i1++;
//    }
    
    while(1)
    {
        fread(&buf, sizeof(int), 1, file);
        if(buf == EOF || feof(file))
            break;
        if(buf > min && buf < max)
        {
            fseek(file, -sizeof(int), SEEK_CUR);
            fwrite("", 1, 1, file);
            cutSize++;
        }
    }

    chsize(fileno(file), cutSize);

    fclose(file);
    return 0;
}

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

// ВОПРОС 7.1   доделать

struct struct7
{
    char surname[20];
    char mark1,mark2,mark3;
};

int main(int argc,char *argv[])
{
    char *filename = (char*)malloc(strlen(argv[1])+1);
    strcpy(filename,argv[1]);
    strcat(filename,".bin");
    FILE *file;
    
    if(!(file = fopen(filename,"rb+")))
    {
        return 0;
    }
    
    int flag = 0,min;
    
    while(1)
    {
        struct struct7 rec;
        if(fread(&rec, sizeof(rec), 1, file) == 0)break;
        if(flag == 0)
        {
            min = rec.mark1 + rec.mark2 + rec.mark3;
            flag = 1;
        }
        
        int buf = rec.mark1 + rec.mark2 + rec.mark3;
        
        if(buf < min) min = buf;
    }
    rewind(file);
    
    int from_read = 0;
    int to_write = 0;
    while(1)
    {
        struct struct7 rec;
        fseek(file, from_read, 0);
        if(fread(&rec, sizeof(rec), 1, file) == 0)
        {
            rewind(file);
            fseek(file, to_write, 0);
            chsize(fileno(file), ftell(file));
            break;
        }
        
        if(rec.mark1 + rec.mark2 + rec.mark3 != min)
        {
            fseek(file, to_write, 0);
            fwrite((void*)&rec, sizeof(rec), 1, file);
            to_write += sizeof(rec);
        }
        from_read +=sizeof(rec);
    }
    
    fclose(file);
    return 0;
}

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
            if(pointer3 -> number > pointer2 -> number)
                pointer3 = pointer2;
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

// ВОПРОС 8.1 c черточкой

int main()
{
    FILE *file;
    file = fopen("a.txt","r+w");
    
    char buf1,buf2;
    fpos_t pos1,pos2;
    int len = 0,i = 0;
    while(1)
        if(fscanf(file, "%c",&buf1)==1)len++;
        else break;
    
    fseek(file, 0, 2);
    fgetpos(file, &pos2);
    rewind(file);
    while(1)
    {
        fgetpos(file, &pos1);
        fscanf(file,"%c",&buf1);
        fsetpos(file, &pos2);
        fscanf(file,"%c",&buf2);
        fsetpos(file, &pos1);
        fprintf(file,"%c", buf2);
        fsetpos(file, &pos2);
        fprintf(file,"%c", buf1);
        pos1+=2;
        pos2-=2;
        i++;
        fsetpos(file, &pos1);
        if(i >=len/2)break;
    }
    fclose(file);
    return 0;
}

// ВОПРОС 8.2

void deletion(struct one_direction_ring **first,int number)
{
    if (!(*first)) return;
    
    //struct one_direction_ring *prev,*next;
    struct one_direction_ring *pointer = (*first);
    struct one_direction_ring *temp = (*first) -> next;
    
    for(int i = 1;i < number && pointer -> next != (*first);i++)
        pointer = pointer -> next;
    
    for(;temp -> next != pointer;)
        temp = temp -> next;
    
    if(pointer && temp)
    {
//        if(pointer -> next == (*first))
//        {
//            (*first) = NULL;
//            free(pointer);
//            free(temp);
//            return;
//        }
        temp -> next = pointer -> next;
        free(pointer);
        free(temp);
    }
}

// ВОПРОС 9.1

int  main()
{
    FILE *file;
    fpos_t *pos1;
    int i1,i2;
    file =fopen ("aaa.bin","w+b");
    rewind(file);
    while(1)
    {
        fgetpos (file,pos1);
        fread (&i1,1,sizeof(int),file);
        if (feof(file)) break;
        fread (&i2,1,sizeof(int),file);
        if (feof(file)) break;
        fsetpos(file,pos1);
        fwrite (&i2,1,sizeof(int),file);
        fwrite (&i1,1,sizeof(int),file);
        *pos1+=(2*sizeof(int));
        fsetpos (file,pos1);
    }
    fclose(file);
    return 0;
}

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

int main()
{
    char filename[20];
    fgets(filename,20,stdin);
    strcat(filename,".bin");
    FILE *file;
    
    if(!(file = fopen(filename,"w+b")))
    {
        return 0;
    }
    
    int k = sizeof(int);
    int buf1,buf2;
    fpos_t pos1,pos2;
    
    rewind(file);
    fseek(file, k, 0);
    
    while(1)
    {
        fgetpos(file, &pos1);
        fread(&buf1,sizeof(int),1,file);
        if(feof(file))rewind(file);
        
        pos2 = pos1 - k;
        fsetpos(file,&pos2);
        while(pos2 >= 0)
        {
            fgetpos(file, &pos2);
            fread(&buf2,sizeof(int),1,file);
            if(buf2 > buf1)
            {
                pos2 +=k;
                fsetpos(file,&pos2);
                fwrite(&buf2, sizeof(int), 1,file);
                pos2 -= k;
            }else
                break;
            pos2 -= k;
            if(pos2 >= 0) fsetpos(file, &pos2);
        }
        pos2 += k;
        fsetpos(file,&pos2);
        fwrite(&buf1, sizeof(int), 1,file);
        pos1 += k;
        if(pos1 >= filelength(fileno(file))) break;
        fsetpos(file,&pos1);
    }
    
    fclose(file);
    return 0;
}

// ВОПРОС 10.1 c черточкой

int main()
{
    char filename[20];
    fgets(filename,20,stdin);
    strcat(filename,".bin");
    FILE *file;
    
    if(!(file = fopen(filename,"w+b")))
    {
        return 0;
    }
    
    int k = sizeof(int);
    int buf1,buf2,minbuf;
    fpos_t pos1,pos2,minpos;
    
    rewind(file);
    
    while(1)
    {
        fgetpos(file, &pos1);
        fread(&buf1,sizeof(int),1,file);
        if(feof(file))break;
        minbuf = buf1;
        minpos = pos1;
        while(1)
        {
            fgetpos(file, &pos2);
            fread(&buf2,sizeof(int),1,file);
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
            fwrite(&minbuf, sizeof(int), 1,file);
            fsetpos(file,&minpos);
            fwrite(&buf1, sizeof(int), 1,file);
        }
        pos1+=k;
        fsetpos(file,&pos1);
    }
    fclose(file);
    return 0;
}

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
            (*last) = temp;
            (*last) -> next = NULL;

            free(temp);
            free(pointer);
            return;
        }
        
        if(pointer != (*top) && pointer != (*last))
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
        while(pos1 > 0 && buf1 < buf2)
        {
            fwrite(&buf1, sizeof(int), 1, thirdfile);
            //fseek(firstfile,-k * 2,1);
            pos1 -=k;
            fsetpos(firstfile, &pos1);
            fgetpos(firstfile, &pos1);
            if(pos1 < 0) break;
            fread(&buf1,sizeof(int),1,firstfile);
        }
        
        //if(feof(firstfile))break;
        
        while(pos2 > 0 && buf1 >= buf2)
        {
            fwrite(&buf2, sizeof(int), 1, thirdfile);
            //fseek(secondfile,-k * 2,1);
            pos2 -=k;
            fsetpos(firstfile, &pos2);
            fgetpos(secondfile, &pos2);
            if(pos2 < 0) break;
            fread(&buf2,sizeof(int),1,secondfile);
        }
        
        //if(feof(secondfile))break;
        
    }while(pos1 > 0 || pos2 > 0);
    
    while(pos1 > 0 )
    {
        fwrite(&buf1, sizeof(int), 1, thirdfile);
        //fseek(firstfile,-k * 2,1);
        pos1 -=k;
        fsetpos(firstfile, &pos1);
        fgetpos(firstfile, &pos1);
        if(pos1 < 0) break;
        fread(&buf1,sizeof(int),1,firstfile);
    }
    
    while(pos2 > 0)
    {
        fwrite(&buf2, sizeof(int), 1, thirdfile);
        //fseek(secondfile,-k * 2,1);
        pos2 -=k;
        fsetpos(firstfile, &pos2);
        fgetpos(secondfile, &pos2);
        if(pos2 < 0) break;
        fread(&buf2,sizeof(int),1,secondfile);
    }
    
    fclose(firstfile);
    fclose(secondfile);
    fclose(thirdfile);
    
    return 0;
}

// ВОПРОС 11.2

struct ring11
{
    char *string;
    struct man *pointer;
    struct ring11 *next;
};

struct man
{
    char* man;
    struct man *next;
};

void del (struct ring11 **enter)
{
    struct ring11 *runner, *maxElement, *preMaxElement;
    struct man *tempHead;

    runner = *enter;
    maxElement = *enter;

    if ((*enter)->next == *enter)
    {
        free(*enter);
        return;
    }

    while (runner->next != *enter)
    {
        if (strcmp(runner->next->string, maxElement->string) > 0)
        {
            preMaxElement = runner;
            maxElement = runner->next;
        }
        runner = runner->next;
    }

    if(maxElement == *enter)
    {
        while((*enter)->pointer)
        {
            tempHead = (struct man *)malloc(sizeof(struct man));           // Распределяю память на новую голову стека
            tempHead->man = (*enter)->pointer->man;                  // Копирую данные из стека, который надо переписать в новую голову

            tempHead->next = (*enter)->next->pointer;                  // Показываю, что следующий элемент новой головы - предыдущая голова стека
            (*enter)->next->pointer = tempHead;                        // Устанавливаю новую голову

            (*enter)->pointer = (*enter)->pointer->next;
        }
        runner->next = (*enter)->next;
        free(*enter);
    }
    else
    {
        while(maxElement->pointer)
        {
            tempHead = (struct man *)malloc(sizeof(struct man));
            tempHead->man = maxElement->pointer->man;

            tempHead->next = maxElement->next->pointer;
            maxElement->next->pointer = tempHead;

            maxElement->pointer = maxElement->pointer->next;
        }

        preMaxElement->next = maxElement->next;
        free(maxElement);
    }
}

// ВОПРОС 12.1

int main()
{
    char filename[20];
    fgets(filename,20,stdin);
    strcat(filename,".bin");
    FILE *firstfile,*secondfile;
    
    if(!(firstfile = fopen(filename,"r+b")))
    {
        return 0;
    }
    if(!(secondfile = fopen(filename,"w")))
    {
        return 0;
    }
    
    //int k = sizeof(int);
    
    int buf1,buf2,buf3;
    fpos_t pos;
    rewind(firstfile);
    
    while(1)
    {
        fread(&buf1,sizeof(int),1,firstfile);
        if(feof(firstfile))break;
        pos = 0;
        while(1)
        {
            fsetpos(secondfile, &pos);
            //fgetpos(secondfile, &pos);
            fscanf(secondfile, "%d",&buf2);
            if(feof(secondfile))break;
            
            if(buf1 == buf2)
            {
                while(1)
                {
                    fscanf(secondfile, "%d",&buf3);
                    if(feof(secondfile))break;
                    fseek(secondfile,-2,1);
                    fprintf(secondfile,"%d",buf3);
                    fseek(secondfile,2,1);
                }
            }
            else pos += 2;
        }
        if(feof(firstfile))break;
    }
    
    fclose(firstfile);
    fclose(secondfile);
        
    return 0;
}

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

int main()
{
    char filename[20];
    fgets(filename,20,stdin);
    strcat(filename,".bin");
    FILE *firstfile,*secondfile;
    
    if(!(firstfile = fopen(filename,"r")))
    {
        return 0;
    }
    if(!(secondfile = fopen(filename,"w+b")))
    {
        return 0;
    }
    
    int k = sizeof(int);
    
    int buf1,buf2,buf3;
    fpos_t pos;
    rewind(firstfile);
    
    while(1)
    {
        fscanf(firstfile, "%d",&buf1);
        if(feof(firstfile))break;
        pos = 0;
        while(1)
        {
            fsetpos(secondfile, &pos);
            //fgetpos(secondfile, &pos);
            fread(&buf2,sizeof(int),1,secondfile);
            if(feof(secondfile))break;
            
            if(buf1 == buf2)
            {
                while(1)
                {
                    fread(&buf3,sizeof(int),1,secondfile);
                    if(feof(secondfile)) break;
                    fseek(secondfile,-k * 2,1);
                    fwrite(&buf3, sizeof(int), 1, secondfile);
                    fseek(secondfile,k,1);
                }
            }
            else pos += k;
        }
        if(feof(firstfile))break;
    }
    
    fclose(firstfile);
    fclose(secondfile);
        
    return 0;
}

// ВОПРОС 13.2

struct ring13
{
    struct gandon *pointer;
    struct ring13 *next;
};

struct gandon
{
    char man[20];
};

void sort_one_direction_ring(struct ring13 **first)
{
    if (!(*first))
        return;
    
    struct ring13 *pointer1,*pointer2,*pointer3,*pointer4,*pointer5,*pointer6;
    
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
            if(strcmp(pointer5 ->pointer ->man, pointer3 -> pointer -> man) > 0)
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

void sort(struct ring13 **enter)
{
    struct ring13 *preSort, *sort, *preCheck, *check;
    check = preCheck = *enter;

    while (preCheck->next != *enter)
        preCheck = preCheck->next;

    while(1)
    {
        preSort = preCheck;
        sort = check->next;

        // Ищем элемент, который будет меньше, чем сортируемый
        while (strcmp(preSort->next->pointer ->man, sort->pointer -> man) < 0)
            preSort = preSort->next;

        if (sort != preCheck)
        {
            if (preSort != check)
            {
                check->next = sort->next;
                sort->next = preSort->next;
                preSort->next = sort;
                if (sort->next == *enter)
                    *enter = sort;
            }
            else
                check = check->next;
        }
        else
        {
            if (sort == preSort)
                *enter = sort;
            else
            {
                check->next = sort->next;
                sort->next = preSort->next;
                preSort->next = sort;
            }
            break;
        }
    }
}

// ВОПРОС 14.1

int main()
{
    char filename[20];
    fgets(filename,20,stdin);
    strcat(filename,".bin");
    FILE *file;
    
    if(!(file = fopen(filename,"w+b")))
    {
        return 0;
    }
    int ask;
    int k = sizeof(int);
    int buf1,buf2;
    fpos_t pos1,pos2;
    
    rewind(file);
    
    while(1)
    {
        scanf("%d",&ask);
        if(ask == 999)break;
        
        while(1)
        {
            fgetpos(file, &pos1);
            fread(&buf1,sizeof(int),1,file);
            if(feof(file) || buf1 < ask )break;
        }
        rewind(file);
        
        if(buf1 > ask)
        {
            fseek(file, 0, 2);
            fwrite(&ask, sizeof(int), 1,file);
        }
        fseek(file, -k, 2);
        
        do
        {
            fgetpos(file, &pos2);
            fread(&buf1,sizeof(int),1,file);
            pos2 +=k;
            fsetpos(file, &pos2);
            fwrite(&buf1, sizeof(int), 1,file);
            fseek(file,pos2 - 2*k,0);
        }while(pos1 < pos2 - k);
        
        fseek(file, pos2 - k, 0);
        fwrite(&ask, sizeof(int), 1,file);
    }
    fclose(file);
    return 0;
}

// ВОПРОС 14.2

struct stringtree *inputt(struct stringtree *node,char temp[])
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
                node -> left = inputt(node -> left,temp);
        }
        
        if(comparison > 0)
        {
            node -> right = inputt(node -> right,temp);
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
       
    while((fscanf(file,"%s",temp)) == 1)
          root = inputt(root,temp);
    
    fclose(file);
    return 0;
}

// ВОПРОС 15.1  хз для текстового ли

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
    
    
    int buf1,buf2,buf3;
    fpos_t pos1,pos2;
    
//    rewind(file);
//    fgetpos(file, &pos1);
//    fscanf(file,"%d", &buf1);
//
//    rewind(file);
//    fseek(file,-2,2);
//    fgetpos(file, &pos2);
//    fscanf(file,"%d", &buf2);
//    rewind(file);
    pos1 = 0;
    pos2 = 7*sizeof(int);
    
    for(int i = 0; i < 4;i++)
    {
        fsetpos(file, &pos1);
        fscanf(file,"%d", &buf1);
        fsetpos(file, &pos2);
        fscanf(file,"%d", &buf2);
        buf3 = buf1;
        buf1 = buf2;
        buf2 = buf3;
        fsetpos(file, &pos1);
        fprintf(file,"%d",buf1);
        fsetpos(file, &pos2);
        fprintf(file,"%d",buf2);
        pos1 += sizeof(int);
        pos2 -= sizeof(int);
    }
    
//    while(pos2 >= 0 || pos1 <= filelengh(fileno(file)))
//    {
//
//        fsetpos(file, &pos1);
//        fprintf(file,"%d",buf2);
//        fsetpos(file, &pos2);
//        fprintf(file,"%d",buf1);
//        pos1+=2;
//        pos2-=2;
//        fsetpos(file, &pos1);
//        fgetpos(file, &pos1);
//        fscanf(file,"%d", &buf1);
//        rewind(file);
//        fsetpos(file, &pos2);
//        fgetpos(file, &pos2);
//        fscanf(file,"%d", &buf2);
//    }
    
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

int main(int argc,char *argv[])
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
    fseek(secondfile,-k,2);
    fgetpos(firstfile, &pos1);
    fgetpos(secondfile, &pos2);
    fread(&buf1,sizeof(int),1,firstfile);
    fread(&buf2,sizeof(int),1,secondfile);
    
    do
    {
        while(!feof(firstfile) && buf1 < buf2)
        {
            fwrite(&buf1, sizeof(int), 1, thirdfile);
            fread(&buf1,sizeof(int),1,firstfile);
        }
        
        if(feof(firstfile))break;
        
        while(pos2 >= 0 && buf1 >= buf2)
        {
            fwrite(&buf2, sizeof(int), 1, thirdfile);
            fseek(secondfile,-k * 2,1);
            fgetpos(secondfile, &pos2);
            if(pos2 < 0) break;
            fread(&buf2,sizeof(int),1,secondfile);
        }
    }while(pos2 >= 0);
    
    while(!feof(firstfile))
    {
        fwrite(&buf1, sizeof(int), 1, thirdfile);
        fread(&buf1,sizeof(int),1,firstfile);
    }
    
    while(pos2 >= 0)
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

void printt (Field *pl)
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

        printt(pl);
    }
    return 0;
}

// ВОПРОС 18.2

struct queue18
{
    struct queue18 *next;
    int number;
};

void writingToBinary(struct queue18 *head, FILE **File)
{
    if (head)
    {
        writingToBinary(head -> next, File);
        fwrite(&(head -> number), sizeof(head -> number), 1, *File);
    }
    else
        return;
}

int main(int argc,char *argv[])
{
    struct queue18 *first = NULL;
    
    char *filename = (char*)malloc(strlen(argv[1])+1);
    strcpy(filename,argv[1]);
    strcat(filename,".bin");
    FILE *file;
    if(!(file = fopen(filename,"wb")))
    {
        return 0;
    }
    
    writingToBinary(first, &file);
    fclose(file);
    return 0;
}

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

int main()
{
    FILE *file;
    
    file = fopen("text.txt", "r+w");
    char buf1,buf2,buf3;
    //fpos_t pos1 = 0,pos2;
    int len = 0 ;
//    while(1)
//    {
//        fgetpos(file, &pos1);
//        fscanf(file, "%c",&buf1);
//        if(feof(file))break;
//        pos2 = pos1 + 1;
//        while(1)
//        {
//            fgetpos(file, &pos2);
//            fscanf(file, "%c",&buf2);
//            if(feof(file))break;
//            if(buf1 == buf2)
//            {
//
//            }
//        }
//    }
    while(1)
        if(fscanf(file,"%c", &buf1) == 1) len++;
        else break;
    rewind(file);
    for(int i = 0;i < len; i++)
    {
        fseek(file,i,0);
        fscanf(file, "%c",&buf1);
        for(int j = i+1;j <= len;j++)
        {
            fseek(file,j,0);
            fscanf(file, "%c",&buf2);
            if(buf1 == buf2)
            {
                len--;
                for(int k = j;k< len;k++)
                {
                    fseek(file,k+1,0);
                    fscanf(file, "%c",&buf3);
                    fseek(file,k+1,0);
                    fprintf(file, "%c",' ');
                    fseek(file,k,0);
                    fprintf(file, "%c",buf3);
                }
            }
        }
        rewind(file);
    }
    fclose(file);
    return 0;
}

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
            //fseek(firstfile,-k * 2,1);
            pos1-=k;
            fsetpos(firstfile, &pos1);
            fgetpos(firstfile, &pos1);
            if(pos1 < 0) break;
            fread(&buf1,sizeof(int),1,firstfile);
        }
        
        if(feof(secondfile))break;
        
        while(pos2 > 0 && buf1 <= buf2)
        {
            fwrite(&buf2, sizeof(int), 1, thirdfile);
            //fseek(firstfile,-k * 2,1);
            pos2-=k;
            fsetpos(firstfile, &pos2);
            fgetpos(secondfile, &pos2);
            if(pos2 < 0) break;
            fread(&buf2,sizeof(int),1,secondfile);
        }
        
        
    }while(pos1 > 0 || pos2 > 0);
    
    while(pos1 > 0 )
    {
        fwrite(&buf1, sizeof(int), 1, thirdfile);
        //fseek(firstfile,-k * 2,1);
        pos1-=k;
        fsetpos(firstfile, &pos1);
        fgetpos(firstfile, &pos1);
        if(pos1 < 0) break;
        fread(&buf1,sizeof(int),1,firstfile);
    }
    
    while(pos2 > 0)
    {
        fwrite(&buf2, sizeof(int), 1, thirdfile);
        //fseek(firstfile,-k * 2,1);
        pos2-=k;
        fsetpos(firstfile, &pos2);
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

int main()
{
    char filename[20];
    fgets(filename,20,stdin);
    strcat(filename,".bin");
    FILE *file;
    
    if(!(file = fopen(filename,"w+b")))
    {
        return 0;
    }
    
    int k = sizeof(int);
    
    int buf1,buf2,buf3;
    fpos_t pos;
    
    while(1)
    {
        scanf("%d",&buf1);
        pos = 0;
        while(1)
        {
            fsetpos(file, &pos);
            //fgetpos(secondfile, &pos);
            fread(&buf2,sizeof(int),1,file);
            if(feof(file))break;
            
            if(buf1 == buf2)
            {
                while(1)
                {
                    fread(&buf3,sizeof(int),1,file);
                    if(feof(file)) break;
                    fseek(file,-k * 2,1);
                    fwrite(&buf3, sizeof(int), 1, file);
                    fseek(file,k,1);
                }
            }
            else pos += k;
        }
    }
    
    fclose(file);
        
    return 0;
}

// ВОПРОС 22.2

void sort_two_direction_queue(struct two_direction_queue **head,struct two_direction_queue **tail)
{
    struct two_direction_queue *pointer1,*pointer2,*pointer3;
    
    for(pointer2 = (*head);pointer2;pointer2 = pointer2 -> prev)
    {
        for(pointer1 = (*tail);pointer1 -> next;pointer1 = pointer1 -> next)
        {
            if(strcmp(pointer1 -> next -> string, pointer1 -> string) > 0)
            {
                pointer3 = pointer1 -> next;
                if(!pointer1 -> prev) (*tail) = pointer1 -> next;
                pointer1 -> next = pointer1 -> next -> next;
                if(pointer1 -> next) pointer1 -> next -> prev = pointer1;
                else pointer2 = (*head) = pointer1;
                pointer3 -> prev = pointer1 -> prev;
                pointer3 -> next = pointer1;
                if(pointer3 -> prev) pointer3 -> prev -> next = pointer3;
                pointer1 -> prev = pointer3;
                pointer1 = pointer1 -> prev;
            }
        }
    }
}

// ВОПРОС 23.1

int main(int argc,char *argv[])
{
    char *filename = (char*)malloc(strlen(argv[1])+1);
    strcpy(filename,argv[1]);
    strcat(filename,".txt");
    FILE *file;
    if(!(file = fopen(filename,"r")))
    {
        return 0;
    }
       
    char symbol,file_symbol;
    fpos_t pos1,pos2;
    
    while(1)
    {
        scanf("%c",&symbol);
        if(symbol == '.')break;
        
        while(1)
        {
            fgetpos(file,&pos1);
            fscanf(file, "%c",&file_symbol);
            
            if(feof(file) || symbol > file_symbol) break;
        }
        
        if(symbol > file_symbol)
        {
            fseek(file,0,2);
            fprintf(file,"%c",symbol);
        }
        
        fseek(file,-2,2);
        
        do
        {
            fgetpos(file,&pos2);
            fscanf(file, "%c",&file_symbol);
            rewind(file);
            pos2+=2;
            fsetpos(file, &pos2);
            fprintf(file,"%c",file_symbol);
            fseek(file,pos2-4,0);
        }while(pos1 < pos2 - 2);
        
        fseek(file,pos2-4,0);
        fprintf(file,"%c",symbol);
    }
    fclose(file);
    return 0;
}

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


