#include "Functions.h"


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
                //puts("\n");
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
                //puts("\n");
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

