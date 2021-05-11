#include "Functions.h"

int menu(void)
{
    printf("\nChoose a number\n");
    printf("1-Enter info\n");
    printf("2-Output info\n");
    printf("3-Delete selected car\n");
    printf("4-Find cars\n");
    printf("5-Input in file\n");
    printf("6-Output from file\n");
    printf("7-Exit\n");
    printf("Your choice: ");
    return input_check_int();
}

struct car input_info()
{
    struct car pointer;
    char* buf_string;
    
        printf("Enter car's cost: ");
        pointer.cost = input_check_float();
        
        printf("Enter car's model: ");
        buf_string = get_model();
        pointer.car_model = buf_string;
        
        printf("\nChoose an option to Input: ");
        printf("\n1-Body type ");
        printf("\n2-Engine volume: ");
        printf("\nYour choice: ");
        
        switch(input_check_int_for_sort())
        {
            case 1:
                pointer.flag = 1;
                while(1)
                {
                    printf("\nInput body type: ");
                    rewind(stdin);
                    getstring(pointer.type.body_type,15);
                    if(check_string(pointer.type.body_type))break;
                }
                break;
            case 2:
                
                pointer.flag = 2;
                printf("\nInput engine volume: ");
                pointer.type.engine_volume = input_check_float();
                break;
        }
    return pointer;
}

void push(struct queue **top,struct queue **last)
{
    do
    {
        struct queue *pointer = malloc(sizeof(struct queue));
        struct car info = input_info();
        pointer -> car = info;
        
        if(!(*top))
        {
            (*top) = (*last) = pointer;
            //(*last) -> next = NULL;
        }else
        {
            (*last) -> next = pointer;
            (*last) = pointer;
            (*last) -> next = NULL;
        }
        printf("To add else?\n");
        printf("1-yes\n");
        printf("2-no\n");
        printf("Your choice: ");
    }while(input_check_int_for_sort() == 1);
}

void output_info(struct queue *top)
{
    int counter = 1;
    struct queue *pointer = top;
    if(!top)
    {
        printf("No cars:(");
        return;
    }
    
    put_header();
    while(pointer)
    {
        output_car(pointer,counter);
        pointer = pointer -> next;
        counter++;
    }
    free(pointer);
}

void output_car(struct queue *pointer ,int index)
{
    
    printf("|  %2d |",index);
    putstring(pointer ->car.car_model,20);
    put_cost(pointer ->car.cost);
    switch(pointer ->car.flag)
    {
        case 1:
            putstring(pointer ->car.type.body_type,15);
            printf("|    -------    |\n");
            break;
        case 2:
            printf("     -------     |");
            put_engine_volume(pointer ->car.type.engine_volume);
            break;
    }
    printf(" ---------------------------------------------------------------------------\n");
}

void deletion(struct queue **top,struct queue **last,int number)
{
    if (!(*top))
    {
        printf("No cars:(\n");
        return;
    }

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
            pointer = NULL;
            free(pointer);
            return;
        }
        
        if (pointer == *last)
        {
            temp = (*top);
            while (temp -> next != pointer) temp = temp -> next;
            *last = temp;
            (*last) -> next = pointer -> next;
            pointer = NULL;
            temp = NULL;
            free(temp);
            free(pointer);
            return;
        }
        
        if(pointer != *top && pointer != *last)
        {
            temp = (*top);
            while(temp -> next != pointer) temp = temp -> next;
            temp -> next = pointer -> next;
            pointer = NULL;
            temp = NULL;
            free(temp);
            free(pointer);
            return;
        }
    }
}

void search(struct queue *top)
{
    if (!top)
    {
        printf("No cars:(\n");
        return;
    }

    int isfound = 0,counter = 1;
    float buf_float;
    char *enter_string = (char*)malloc(20*sizeof(char));
    char *buf_string = (char*)malloc(20*sizeof(char));
    struct queue *pointer = NULL;

    while(1)
    {
        printf("What to find\n");
        printf("1-Cost\n");
        printf("2-Car model\n");
        printf("3-Body type\n");
        printf("4-Engine volume\n");
        printf("5-Exit\n");
        printf("Your choice: ");
        
        switch(input_check_int())
        {
            case 1:
                pointer = top;
                counter = 1;
                printf("Enter car's cost\n");
                rewind(stdin);
                buf_float = input_check_float();
                while(pointer)
                {
                    if(pointer ->car.cost == buf_float)
                    {
                        put_header();
                        output_car(pointer,counter);
                        isfound = 1;
                    }
                    counter++;
                    pointer = pointer -> next;
                }
                break;
            case 2:
                pointer = top;
                counter = 1;
                printf("Enter car's model\n");
                rewind(stdin);
                getstring(enter_string, 20);
                string_to_lowercase(enter_string);
                while(pointer)
                {
                    strcpy(buf_string,pointer ->car.car_model);
                    string_to_lowercase(buf_string);
                    if(strstr(buf_string,enter_string))
                    {
                        put_header();
                        output_car(pointer,counter);
                        isfound = 1;
                    }
                    counter++;
                    pointer = pointer -> next;
                }
                break;
            case 3:
                pointer = top;
                counter = 1;
                printf("Enter car's body type\n");
                rewind(stdin);
                getstring(enter_string, 20);
                string_to_lowercase(enter_string);
                while(pointer)
                {
                    strcpy(buf_string,pointer ->car.type.body_type);
                    string_to_lowercase(buf_string);
                    if(strstr(buf_string,enter_string))
                    {
                        put_header();
                        output_car(pointer,counter);
                        isfound = 1;
                    }
                    counter++;
                    pointer = pointer -> next;
                }
                break;
            case 4:
                counter = 1;
                pointer = top;
                printf("Enter engine's volume\n");
                rewind(stdin);
                buf_float = input_check_float();
                while(pointer)
                {
                    if(pointer ->car.type.engine_volume == buf_float)
                    {
                        put_header();
                        output_car(pointer,counter);
                        isfound = 1;
                    }
                    counter++;
                    pointer = pointer -> next;
                }
                break;
            case 5:
                free(buf_string);
                free(enter_string);
                if(pointer)free(pointer);
                return;
            default:
                printf("Wrong number\n");
        }
        if(!isfound)printf("No matches\n");
        isfound = 0;
    }
}

void input_in_file(struct queue *top)
{
    if (!top)
    {
        printf("No cars:(\n");
        return;
    }
    
    FILE *file;
    struct queue *pointer = top;
    char file_name[20];

    printf("Select the file type you want to save\n");
    printf("1-text file\n");
    printf("2-bin file\n");
    printf("Your choice: ");
    
    switch (input_check_int_for_sort()) {
        case 1:
            do
            {
                printf("Enter name of the file: ");
                getstring(file_name,15);
            }while(check_name(file_name));
            strcat(file_name,".txt");
            
            if(!(file = fopen(file_name,"w")))
            {
                printf("Unable to open a file.Process will be stopped\n");
                return;
            }
            
            while(pointer)
            {
                fprintf(file,"%.2f ",pointer ->car.cost);
                fprintf(file,"%s ",pointer ->car.car_model);
                fprintf(file,"%d ",pointer ->car.flag);
                switch(pointer ->car.flag)
                {
                    case 1:
                        fprintf(file,"%s\n\n",pointer ->car.type.body_type);
                        break;
                    case 2:
                        fprintf(file,"%.2f\n\n",pointer ->car.type.engine_volume);
                        break;
                }
                pointer = pointer -> next;
            }
            
            fclose(file);
            break;
        case 2:
            do
            {
                printf("Enter name of the file: ");
                getstring(file_name,15);
            }while(check_name(file_name));
            strcat(file_name,".bin");
            
            if(!(file = fopen(file_name,"wb")))
            {
                printf("Unable to open a file.Process will be stopped\n");
                return;
            }
            
            while(pointer)
            {
                fwrite(&pointer ->car.cost,sizeof(float),1,file);
                fwrite(pointer ->car.car_model,sizeof(char),strlen(pointer ->car.car_model),file);
                fwrite(&pointer ->car.flag,sizeof(int),1,file);
                switch(pointer ->car.flag)
                {
                    case 1:
                        fwrite(&pointer ->car.type.body_type,15,1,file);
                        break;
                    case 2:
                        fwrite(&pointer ->car.type.engine_volume,sizeof(pointer ->car.type.engine_volume),1,file);
                        break;
                }
                pointer = pointer -> next;
                 
            }
            
            fclose(file);
            break;
            
        default:
            printf("Wrong number\n");
    }
    printf("\nSaved successfully!\n");
    free(pointer);
}


void load_from_file(struct queue **top,struct queue **last)
{
    FILE *file;
    struct queue *pointer;
    char file_name[20];
    char *buf_string = NULL;
    float buf_float;
    int buf_int;

    printf("Select the file type you want to open\n");
    printf("1-text file\n");
    printf("2-bin file\n");
    printf("3-exit\n");
    printf("Your choice: ");
    
    switch (input_check_int_for_sort()) {
        case 1:
            do
            {
                printf("Enter name of the file: ");
                getstring(file_name,15);
            }while(check_name(file_name));
            strcat(file_name,".txt");
            
            if(!(file = fopen(file_name,"r")))
            {
                printf("Unable to open a file.Process will be stopped\n");
                return;
            }
            
            while (1)
            {
                fscanf(file, "%f", &buf_float);
                if(feof(file))break;
                if (!(pointer = (struct queue*)malloc(sizeof(struct queue))))
                {
                    printf("Something went wrong\n");
                    return ;
                }
                buf_string = (char*)malloc(20*sizeof(char));


                pointer ->car.cost = buf_float;

                fscanf(file, "%s", buf_string);

                pointer ->car.car_model = (char*)malloc((strlen(buf_string))*sizeof(char));
                for(int i = 0; buf_string[i]; i++)
                {
                    pointer->car.car_model[i] = buf_string[i];
                }

                fscanf(file, "%d", &buf_int);
                pointer ->car.flag = buf_int;

                switch(pointer ->car.flag)
                {
                    case 1:
                        fscanf(file, "%s", buf_string);
                        strcpy(pointer ->car.type.body_type,buf_string);
                        break;
                    case 2:
                        fscanf(file, "%f", &buf_float);
                        pointer ->car.type.engine_volume = buf_float;
                        break;
                }
                
                if(!(*top))
                {
                    (*top)=(*last)=pointer;
                }else
                {
                    (*last) -> next = pointer;
                    (*last) = pointer;
                    (*last) -> next = NULL;
                }
            }
            fclose(file);
            break;
        case 2:
            do
            {
                printf("Enter name of the file: ");
                getstring(file_name,15);
            }while(check_name(file_name));
            strcat(file_name,".bin");
            
            if(!(file = fopen(file_name,"rb")))
            {
                printf("Unable to open a file.Process will be stopped\n");
                return;
            }
            
            char c;
            int i;
            
            while(1)
            {
                fread(&buf_float,sizeof(float),1,file);
                if(feof(file))break;
                if (!(pointer = (struct queue*)malloc(sizeof(struct queue))))
                {
                    printf("Something went wrong\n");
                    return ;
                }
                
                pointer ->car.cost = buf_float;
                pointer ->car.car_model = (char*)malloc(sizeof(char));

                for (i = 0; fread(&c, sizeof(char), 1, file) == 1; ++i)
                {

                    if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
                    {
                        fseek(file,-1,SEEK_CUR);
                        break;
                    }

                    if (!(buf_string = (char*)realloc(buf_string, i + 2)))
                    {
                        printf("Not enough memory!");
                        return;
                    }

                    (c >= 'A' && c <= 'Z') ? buf_string[i] = (char) (c + ('a' - 'A'))
                                           : (buf_string[i] = c);
                }
                
                if(buf_string)
                {
                    buf_string[i] = '\0';
                }
                
                strcpy(pointer ->car.car_model, buf_string);

                fread(&pointer ->car.flag, sizeof(int), 1, file);
                
                switch(pointer ->car.flag)
                {
                    case 1:
                        fread(buf_string,15,1,file);

                        strcpy(pointer ->car.type.body_type,buf_string);
                        break;
                    case 2:
                        fread(&pointer ->car.type.engine_volume,sizeof(float),1,file);
                        break;
                }
                
                if(!(*top))
                {
                    (*top)=(*last)=pointer;
                }else
                {
                    (*last) -> next = pointer;
                    (*last) = pointer;
                    (*last) -> next = NULL;
                }
            }
            fclose(file);
            break;
        case 3:
            break;
        default:
            printf("Wrong number\n");
    }
    
    printf("\nCopied successfully!\n");
    pointer = NULL;
    free(pointer);
    free(buf_string);
}

int check_name(char *string)
{
    int i = 0;

    while(string[i])
    {
        if(string[i] == '/' || string[i] == '~' || string[i] == '|' || string[i] == '\\' || string[i] == '<' || string[i] == '>' ||
           string[i] == '{' || string[i] == '}' || string[i] == '[' || string[i] == ']' || string[i] == '%' || string[i] == '&' ||
           string[i] == '+' || string[i] == '?' || string[i] == '"' || string[i] == '*' || string[i] == ':' || string[i] == '#' ||
           string[i] == '@' || string[i] == '=' || string[i] == '$')
        {
            return 1;
        }

        i++;
    }
    return 0;
}

void put_cost(float num)
{
    if(num < 10)
    {
        printf("|  %.1f       |", num);
    }else if(num < 100)
    {
        printf("|  %.1f      |", num);
        
    }else if(num < 1000)
    {
        printf("|  %.1f     |", num);
    }else if(num < 10000)
    {
        printf("|  %.1f    |", num);
        
    }else if(num < 100000)
    {
        printf("|  %.1f   |", num);
        
    }else if(num < 1000000)
    {
        printf("|  %.1f  |", num);
        
    }else if(num < 10000000)
    {
        printf("|  %.1f |", num);
    }
}

void put_engine_volume(float num)
{
    if(num < 10)
    {
        printf("      %.1f      |\n",num);
    }else
        printf("      %.1f     |\n",num);
}

void getstring(char *string,int size)
{
    char buf;
    
    while((buf = getchar()) != '\n' && --size > 0)
        *string++ = buf;
    *string = '\0';
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

float input_check_float()
{
    int read_count, is_empty;
    float number;
     
    while (1)
    {
         read_count = scanf("%f", &number);
         is_empty = ClearStdin();
         if (read_count == 1 && is_empty != 0 && number > 0)
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

int confirmation()
{
    printf("Are you sure?\n");
    printf("1-Yes\n");
    printf("2-No\n");
    
    return input_check_int_for_sort();
}

void putstring(char* string, int len)
{
    printf("  %s", string);
    for(long int i = strlen(string); i < len; i++)
    {
        printf("%c", ' ');
    }
    return;
}

void put_header()
{
    printf(" ---------------------------------------------------------------------------\n");
    printf("| NUM |      Car Model       |    Cost    |    Body type    | Engine volume |\n");
    printf(" ---------------------------------------------------------------------------\n");
}

char* get_model(void)
{
    rewind(stdin);

    char* string = NULL;
    char c;
    size_t i;

    for (i = 0; (c = (char)getchar()) != '\n'; ++i)
    {
        if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
        {
            puts("Invalid input, try again!");
            return NULL;
        }

        if (!(string = (char*)realloc(string, i + 2)))
        {
            puts("Not enough memory!");
            return NULL;
        }

        (c >= 'A' && c <= 'Z') ? string[i] = (char)(c + ('a' - 'A')) : (string[i] = c);
    }
    if (string) string[i] = '\0';
    return string;
}

int check_string(char *string)
{
    if(string[0] != '\0' && string[0] != '\n' && string[0] != ' ' && check_string_for_number(string) == 0)return 1;
    return 0;
}


