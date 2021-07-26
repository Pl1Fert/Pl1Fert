#include "Functions.hpp"

int menu(void)
{
    printf("\nChoose a number\n");
    printf("1-enter a new struct\n");
    printf("2-output a struct\n");
    printf("3-delete selected car\n");
    printf("4-find cars\n");
    printf("5-add new cars\n");
    printf("6-find cars with max engine volume\n");
    printf("7-exit\n");
    printf("Your choice: ");
    return input_check_int();
}

void enter_struct(struct car* pointer,int amount)
{
    for(int i = 0;i < amount;i++)
    {
        pointer[i].car_model = (char*)malloc(20*sizeof(char));
        
        printf("\nCar %d: \n",i+1);
        printf("Enter car's cost: ");
        pointer[i].cost = input_check_float();
        while(1)
        {
            printf("Enter car's model: ");
            rewind(stdin);
            //fgets(pointer[i].car_model,20,stdin);
            gets(pointer[i].car_model);
            if(pointer[i].car_model[0] != '\0' && pointer[i].car_model[0] != '\n' && pointer[i].car_model[0] != ' ' && check_string_for_number(pointer[i].car_model) == 0)break;
        }
        printf("\nChoose an option to Input: ");
        printf("\n1-Body type ");
        printf("\n2-Engine volume: ");
        printf("\nYour choice: ");
        switch(input_check_int_for_sort())
        {
            case 1:
                pointer[i].flag = 1;
                
                while(1)
                {
                    printf("\nInput body type: ");
                    rewind(stdin);
                    //fgets(pointer[i].type.body_type,20,stdin);
                    gets(pointer[i].type.body_type);
                    if(pointer[i].type.body_type[0] != '\0' && pointer[i].type.body_type[0] != '\n' && pointer[i].type.body_type[0] != ' ' && check_string_for_number(pointer[i].type.body_type) == 0)break;
                }
                break;
            case 2:
                pointer[i].flag = 2;
                printf("\nInput engine volume: ");
                pointer[i].type.engine_volume = input_check_float();
                break;
        }
    }
}

void put_cost(float num,struct car pointer)
{
    if(num < 10)
    {
        printf("|  %.1f       |", pointer.cost);
    }else if(num < 100)
    {
        printf("|  %.1f      |", pointer.cost);
        
    }else if(num < 1000)
    {
        printf("|  %.1f     |", pointer.cost);
    }else if(num < 10000)
    {
        printf("|  %.1f    |", pointer.cost);
        
    }else if(num < 100000)
    {
        printf("|  %.1f   |", pointer.cost);
        
    }else if(num < 1000000)
    {
        printf("|  %.1f  |", pointer.cost);
        
    }else if(num < 10000000)
    {
        printf("|  %.1f |", pointer.cost);
    }
}

void put_engine_volume(float num,struct car pointer)
{
    if(num < 10)
    {
        printf("      %.1f      |\n",pointer.type.engine_volume);
    }else
        printf("      %.1f     |\n",pointer.type.engine_volume);
}

void output_struct(struct car* pointer,int amount)
{
    if (!pointer || amount == 0)
    {
        printf("No cars:(\n");
        return;
    }
    put_header();
    for(int i = 0;i < amount;i++)
    {
        output_car(pointer[i],i);
    }
}

void output_car(struct car pointer , int index)
{
    printf("|  %2d |",index+1);
    //printf("   %5s   |", pointer[i].car_model);
    putstring(pointer.car_model,20);
    //printf("|  %.1f  ", pointer[i].cost);
    put_cost(pointer.cost,pointer);
    switch(pointer.flag)
    {
        case 1:
            putstring(pointer.type.body_type,15);
            printf("|    -------    |\n");
            break;
        case 2:
            printf("     -------     |");
            //printf("      %.1f      |\n",pointer.type.engine_volume);
            put_engine_volume(pointer.type.engine_volume,pointer);
            break;
    }
    printf(" ---------------------------------------------------------------------------\n");
}

void add_car(struct car* pointer,int &amount)
{
    int index;
    int i;
    int buf;
    
    if (!pointer || amount == 0)
    {
        printf("No cars:(\n");
        return;
    }
    
    index = amount;
    printf("Enter amount of cars to add: ");
    buf=input_check_int();
    amount+=buf;
    
    for(int i = 0;i<buf;i++)pointer = (struct car*)realloc(pointer,1* sizeof(struct car));
    
    for(i = index;i < amount;i++)
    {
        printf("\nCar %d: \n",i+1);
        printf("Enter car's cost: ");
        pointer[i].cost = input_check_float();
        pointer[i].car_model = (char*)malloc(20*sizeof(char));
        while(1)
        {
            printf("Enter car's model: ");
            rewind(stdin);
            gets(pointer[i].car_model);
            //fgets(pointer[i].car_model,20,stdin);
            if(pointer[i].car_model[0] != '\0' && pointer[i].car_model[0] != '\n' && pointer[i].car_model[0] != ' ' && check_string_for_number(pointer[i].car_model) == 0)break;
        }
        printf("\nChoose an option to Input: ");
        printf("\n1-Body type ");
        printf("\n2-Engine volume: ");
        printf("\nYour choice: ");
        switch(input_check_int_for_sort())
        {
            case 1:
                pointer[i].flag = 1;
                
                while(1)
                {
                    printf("\nInput body type: ");
                    rewind(stdin);
                    gets(pointer[i].type.body_type);
                    //fgets(pointer[i].type.body_type,20,stdin);
                    if(pointer[i].type.body_type[0] != '\0' && pointer[i].type.body_type[0] != '\n' && pointer[i].type.body_type[0] != ' ' && check_string_for_number(pointer[i].type.body_type) == 0)break;
                }
                break;
            case 2:
                pointer[i].flag = 2;
                printf("\nInput engine volume: ");
                pointer[i].type.engine_volume = input_check_float();
                break;
        }
    }
}

void find(struct car* pointer,int amount)
{
    char *enter_string = (char*)malloc(20*sizeof(char));
    char *buf_string = (char*)malloc(20*sizeof(char));
    
    if (!pointer || amount == 0)
    {
        printf("No cars:(\n");
        return;
    }
    
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
                printf("Enter car's cost\n");
                rewind(stdin);
                for(int i = 0;i < amount;i++)
                {
                    if(pointer[i].cost == input_check_float())
                    {
                        put_header();
                        output_car(pointer[i],i);
                    }
                }
                break;
            case 2:
                printf("Enter car's model\n");
                rewind(stdin);
                gets(enter_string);
                //fgets(enter_string, 20, stdin);
                string_to_lowercase(enter_string);
                for(int i = 0;i < amount;i++)
                {
                    strcpy(buf_string,pointer[i].car_model);
                    string_to_lowercase(buf_string);
                    if(strstr(buf_string,enter_string))
                    {
                        put_header();
                        output_car(pointer[i],i);
                    }
                }
                break;
            case 3:
                printf("Enter car's body type\n");
                rewind(stdin);
                gets(enter_string);
                //fgets(enter_string, 20, stdin);
                string_to_lowercase(enter_string);
                for(int i = 0;i < amount;i++)
                {
                    strcpy(buf_string,pointer[i].type.body_type);
                    string_to_lowercase(buf_string);
                    if(strstr(buf_string,enter_string))
                    {
                        put_header();
                        output_car(pointer[i],i);
                    }
                }
                break;
            case 4:
                printf("Enter engine's volume\n");
                rewind(stdin);
                for(int i = 0;i < amount;i++)
                {
                    if(pointer[i].type.engine_volume == input_check_float())
                    {
                        put_header();
                        output_car(pointer[i],i);
                    }
                }
                break;
            case 5:
                free(buf_string);
                free(enter_string);
                return;
            default:
                printf("Wrong number\n");
        }
    }
}

void header_delete(struct car *pointer, int &amount)
{
    int number;
    char *enter_string = (char*)malloc(20*sizeof(char));
    char *buf_string = (char*)malloc(20*sizeof(char));
    
    if (!pointer || amount == 0)
    {
        printf("No cars:(\n");
        return;
    }
    
    while(1)
    {
        printf("What to delete\n");
        printf("1-Cost\n");
        printf("2-Car model\n");
        printf("3-Body type\n");
        printf("4-Engine volume\n");
        printf("5-Number\n");
        printf("6-Exit\n");
        printf("Your choice: ");
        
        switch(input_check_int())
        {
            case 1:
                printf("Enter car's cost\n");
                rewind(stdin);
                for(int i = 0;i < amount;i++)
                {
                    if(pointer[i].cost == input_check_float())
                    {
                        delete_car(pointer,i,amount);
                    }
                }
                break;
            case 2:
                printf("Enter car's model\n");
                rewind(stdin);
                gets(enter_string);
                //fgets(enter_string, 20, stdin);
                string_to_lowercase(enter_string);
                for(int i = 0;i < amount;i++)
                {
                    strcpy(buf_string,pointer[i].car_model);
                    string_to_lowercase(buf_string);
                    if(strstr(buf_string,enter_string))
                    {
                        delete_car(pointer,i,amount);
                    }
                }
                break;
            case 3:
                printf("Enter car's body type\n");
                rewind(stdin);
                gets(enter_string);
                //fgets(enter_string, 20, stdin);
                string_to_lowercase(enter_string);
                for(int i = 0;i < amount;i++)
                {
                    strcpy(buf_string,pointer[i].type.body_type);
                    string_to_lowercase(buf_string);
                    if(strstr(buf_string,enter_string))
                    {
                        delete_car(pointer,i,amount);
                    }
                }
                break;
            case 4:
                printf("Enter engine's volume\n");
                rewind(stdin);
                for(int i = 0;i < amount;i++)
                {
                    if(pointer[i].type.engine_volume == input_check_float())
                    {
                        delete_car(pointer,i,amount);
                    }
                }
                break;
            case 5:
                printf("Enter number\n");
                rewind(stdin);
                number = input_check_int()-1;
                delete_car(pointer,number,amount);
                break;
            case 6:
                free(buf_string);
                free(enter_string);
                return;
            default:
                printf("Wrong number\n");
        }
    }
}

void delete_car(struct car* pointer,int index,int& amount)
{
    if (index != amount-1 && confirmation() == 1)
    {
        for (; index+1 < amount; index++)
        {
            pointer[index] = pointer[index+1];
        }
        amount--;
        pointer = (struct car*)realloc(pointer,amount * sizeof(struct car));
    }
    
    if (index == amount-1 && confirmation() == 1)
    {
        amount--;
        pointer = (struct car*)realloc(pointer,amount * sizeof(struct car));
    }
    
}

void find_max_engine_volume(struct car *pointer, int amount)
{
    if (!pointer || amount == 0)
    {
        printf("No cars:(\n");
        return;
    }
    
    float max_engine_volume = 0;

    for(int i = 0; i < amount;i++)
    {
        if( max_engine_volume < pointer[i].type.engine_volume && pointer[i].flag == 2)
        {
            max_engine_volume = pointer[i].type.engine_volume;
        }
    }
    if(max_engine_volume)
    {
        put_header();
    }else
        printf("No cars with engine volume info");
    
    for(int i = 0;i < amount;i++)
    {
        if(pointer[i].type.engine_volume == max_engine_volume)
        {
            output_car(pointer[i],i);
        }
    }
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
    for(int i = strlen(string); i < len; i++)
    {
        //str[i] = " ";
        printf("%s", " ");
    }
    return;
}

void put_header()
{
    printf(" ---------------------------------------------------------------------------\n");
    printf("| NUM |      Car Model       |    Cost    |    Body type    | Volume engine |\n");
    printf(" ---------------------------------------------------------------------------\n");
}
