#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
#define STRING_SIZE 20
 
void getstring(char *string,int size);
int ClearStdin(void);
int input_check_int(void);
int input_check_int_for_sort(void);
float input_check_float(void);
int check_string(char *string);
void input_txt_content(FILE *file,char *file_name);
void output_txt_content(FILE *file,char *file_name);
void replace_spaces(FILE *file,char *file_name);
void frequency_of_symbols(FILE *file,char *file_name);
void input_bin_content(FILE *file, char *file_name, int amount);
void output_bin_content(FILE *file, char *file_name);
void even_sum(FILE *file, char *file_name);
void replace_even(FILE *file,char *file_name);
 
int main()
{
    int amount;
    FILE *text_file = NULL;
    FILE *binary_file = NULL;
 
    char *file_name = (char*)malloc((STRING_SIZE-5)*sizeof(char));
 
    printf("Choose what file to create:\n");
    printf("1-text file\n");
    printf("2-binary file\n");
    printf("Your choice: ");
 
    switch(input_check_int_for_sort())
    {
        case 1:
            do
            {
            printf("Enter name of the file: ");
            getstring(file_name,STRING_SIZE-5);
            }while(check_string(file_name));
 
            strcat(file_name,".txt");
            if(!(text_file = fopen(file_name,"w")))
            {
                printf("Unable to open a file.Program will be stopped\n");
                return 0;
            }
            fclose(text_file);
            while(1)
            {
                printf("1-Input a content\n");
                printf("2-Output a content\n");
                printf("3-Determine the frequency of occurrence of characters\n");
                printf("4-Replace spaces\n");
                printf("5-Exit\n");
                printf("Choose an option: ");
                switch(input_check_int())
                {
                    case 1:
                        input_txt_content(text_file,file_name);
                        break;
                    case 2:
                        output_txt_content(text_file,file_name);
                        break;
                    case 3:
                        frequency_of_symbols(text_file,file_name);
                        break;
                    case 4:
                        replace_spaces(text_file,file_name);
                        break;
                    case 5:
                        free(file_name);
                        return 0;
                    default:
                        printf("Wrong number\n");
                }
            }
            break;
        case 2:
            do
            {
            printf("Enter name of the file: ");
            getstring(file_name,STRING_SIZE-5);
            }while(check_string(file_name));
            strcat(file_name,".bin");
            if(!(binary_file = fopen(file_name,"wb")))
            {
                printf("Unable to open a file.Program will be stopped\n");
                return 0;
            }
            fclose(binary_file);
            while(1)
            {
                printf("1-Input a content\n");
                printf("2-Output a content\n");
                printf("3-Find the sum of even elements\n");
                printf("4-Replace even numbers the value of the minimum element\n");
                printf("5-Exit\n");
                printf("Choose an option: ");
                switch(input_check_int())
                {
                    case 1:
                        printf("How many numbers do u want: ");
                        //printf("Your input: ");
                        amount = input_check_int();
                        input_bin_content(binary_file,file_name,amount);
                        break;
                    case 2:
                        output_bin_content(binary_file,file_name);
                        break;
                    case 3:
                        even_sum(binary_file, file_name);
                        break;
                    case 4:
                        replace_even(binary_file, file_name);
                        break;
                    case 5:
                        free(file_name);
                        return 0;
                    default:
                        printf("Wrong number\n");
                }
            }
            break;
    }
    return 0;
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
 
int check_string(char *string)
{
    int i = 0;
    while(string[i])
    {
        if(string[i] == '/' || string[i] == '~' || string[i] == '|' || string[i] == '\\' || string[i] == '<' || string[i] == '>' ||
           string[i] == '{' || string[i] == '}' || string[i] == '[' || string[i] == ']' | string[i] == '%' || string[i] == '&' || string[i] == '+'
           || string[i] == '?' || string[i] == '"' || string[i] == '*' || string[i] == ':' || string[i] == '#')
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
 
    rewind(file);
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
    fclose(file);
}