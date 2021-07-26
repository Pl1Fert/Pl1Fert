
#ifndef Functions_h
#define Functions_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STRING_SIZE 20

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
 
int check_string(char *string)
{
    int i = 0;
    while(string[i])
    {
        if(string[i] == '/' || string[i] == '~' || string[i] == '|' || string[i] == '\\' || string[i] == '<' || string[i] == '>' ||
           string[i] == '{' || string[i] == '}' || string[i] == '[' || string[i] == ']' | string[i] == '%' || string[i] == '&' || string[i] == '+'
           || string[i] == '?' || string[i] == '"' || string[i] == '*' || string[i] == ':' || string[i] == '#' || string[i] == '@' || string[i] == '=' || string[i] == '$')
        {
            return 1;
        }
        i++;
    }
    return 0;
}
 
void input_txt_content(FILE *file,char *file_name)
{
    char *string = (char*)malloc((3*STRING_SIZE)*sizeof(char));
 
    if(!(file = fopen(file_name,"w")))
        printf("Unable to open a file: ");
 
    printf("Enter content: \n");
    rewind(stdin);
    getstring(string,3*STRING_SIZE);
    fprintf(file,"%s",string);

    puts("\n");
    fclose(file);
    free(string);
}
 
void output_txt_content(FILE *file,char *file_name)
{
    char *string = (char*)malloc((3*STRING_SIZE)*sizeof(char));
 
    if(!(file = fopen(file_name,"r")))
        printf("Unable to open a file");
 
    rewind(stdin);
    fgets(string,3*STRING_SIZE,file);
    printf("Your string: %s\n", string);
    puts("\n");
    
    fclose(file);
    free(string);
}
 
void replace_spaces(FILE *file,char *file_name)
{
    fpos_t space;
    file = fopen(file_name,"r+a");
    char enter_symbol,symbol;
    printf("Enter a symbol: ");
    scanf("%c",&enter_symbol);
    while(!feof(file))
    {
        fgetpos(file,&space);
        fscanf(file,"%c",&symbol);
        if(symbol == ' ')
        {
            rewind(file);
            fsetpos(file,&space);
            fprintf(file,"%c",enter_symbol);
            rewind(file);
        }
    }
    fclose(file);
}
 
void frequency_of_symbols(FILE *file,char *file_name)
{
    int array[255] = {0};
    char symbol;
    file = fopen(file_name,"r");
    while(1)
    {
        fscanf(file, "%c", &symbol);
        if(feof(file))break;
        array[(int)symbol]++;
    }

    for(int i = 0;i < 255; i++)
    {
        if(array[i] > 0)
        {
            printf("Symbol '%c' met -",(char)i);
            printf(" %d times\n",array[i]);
        }
    }
    puts("\n");
    fclose(file);
}
 
void input_bin_content(FILE *file, char *file_name, int amount)
{
    file = fopen(file_name, "wb");
 
    int index,number;
 
    for(index = 0; index < amount; index++)
    {
        printf("Number %d: \n",index+1);
        scanf("%d", &number);
        fwrite(&number, sizeof(int), 1, file);
    }
    fclose(file);
}
 
void output_bin_content(FILE *file, char *file_name)
{
    file = fopen(file_name, "rb");
 
    int number;

    while (1)
    {
      fread(&number, sizeof(int), 1, file);
      if (feof(file)) break;
      printf("%3d", number);
    }
    puts("\n");
    fclose(file);
}
 
void even_sum(FILE *file, char *file_name)
{
    int counter = 0,number,sum = 0;
 
    file = fopen(file_name, "rb");
 
    while (1)
    {
        fread(&number, sizeof(int), 1, file);
        if (feof(file)) break;
        counter++;
        if(number % 2 == 0)
        {
            sum += number;
        }
    }
 
    printf("Counter = %d\nSum = %d\n", counter, sum);
    puts("\n");
    fclose(file);
}
 
void replace_even(FILE *file,char *file_name)
{
    int counter = 0,min,number;
    file = fopen(file_name, "r+b");
 
    rewind(file);
    while(!feof(file))
    {
        if (fread(&number, sizeof(int), 1, file))
        {
            if(!min) min = number;
            else if(min > number) min = number;
        }
    }
 
    rewind(file);
    while(!feof(file))
    {
        if (fread(&number, sizeof(int), 1, file))
        {
            counter++;
 
            if(number % 2 == 0)
            {
                fseek(file, (counter-1)*sizeof(int), SEEK_SET);
                fwrite(&min, sizeof(int), 1, file);
            }
        }
    }
    printf("\nReplaced successfully\n");
    puts("\n");
    fclose(file);
}


#endif /* Functions_h */
