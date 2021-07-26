#include "Functions.hpp"

int menu(void)
{
    printf("\nChoose a number\n");
    printf("1-enter a new struct\n");
    printf("2-output a struct\n");
    printf("3-delete selected student\n");
    printf("4-sort students\n");
    printf("5-edit selected student\n");
    printf("6-find students\n");
    printf("7-part find students\n");
    printf("8-add new students\n");
    printf("9-exit\n");
    printf("Your choice: ");
    return input_check_int();
}

void enter_struct(struct student *pointer,int amount)
{
    for(int i = 0;i < amount;i++)
    {
        printf("\nStudent %d: \n",i+1);
        while(1)
        {
            printf("Enter student's lastname: ");
            rewind(stdin);
            fgets(pointer[i].lastname,20,stdin);
            if(pointer[i].lastname[0] != '\0' && pointer[i].lastname[0] != '\n' && pointer[i].lastname[0] != ' ' && check_string_for_number(pointer[i].lastname) == 0)break;
        }
        while(1)
        {
            printf("Enter student's name: ");
            rewind(stdin);
            fgets(pointer[i].name,20,stdin);
            if(pointer[i].name[0] != '\0' && pointer[i].name[0] != '\n' && pointer[i].name[0] != ' ' && check_string_for_number(pointer[i].name) == 0)break;
        }
        while(1)
        {
            printf("Enter student's patronymic: ");
            rewind(stdin);
            fgets(pointer[i].patronymic,20,stdin);
            if(pointer[i].patronymic[0] != '\0' && pointer[i].patronymic[0] != '\n' && pointer[i].patronymic[0] != ' ' && check_string_for_number(pointer[i].patronymic) == 0)break;
        }
        while(1)
        {
            printf("Enter student's address: ");
            rewind(stdin);
            fgets(pointer[i].address,20,stdin);
            if(pointer[i].address[0] != '\0' && pointer[i].address[0] != '\n' && pointer[i].address[0] != ' ')break;
        }
        while(1)
        {
            printf("Enter student's group number: ");
            rewind(stdin);
            fgets(pointer[i].group_number,20,stdin);
            if(pointer[i].group_number[0] != '\0' && pointer[i].group_number[0] != '\n' && pointer[i].group_number[0] != ' ')break;
        }
        printf("Enter student's rating: ");
        rewind(stdin);
        pointer[i].rating = input_check_float();
    }
}

void output_struct(struct student *pointer,int amount)
{
    if (!pointer)
    {
        printf("No students:(\n");
        return;
    }
    
    for(int i = 0;i < amount;i++)
    {
        printf("\nStudent %d: \n",i+1);
        printf("Lastname: %s\n", pointer[i].lastname);
        printf("Name: %s\n", pointer[i].name);
        printf("Patronymic: %s\n", pointer[i].patronymic);
        printf("Home address: %s\n", pointer[i].address);
        printf("Group number: %s\n", pointer[i].group_number);
        printf("Rating: %.2f\n", pointer[i].rating);
        printf("\n");
    }
}

void header_delete(struct student *pointer, int &amount)
{
    int number;
    char *enter_string = (char*)malloc(20*sizeof(char));
    char *buf_string = (char*)malloc(20*sizeof(char));
    
    if (!pointer)
    {
       printf("No students:(\n");
       return;
    }
    
    while(1)
    {
        printf("What to delete\n");
        printf("1-Lastname\n");
        printf("2-Name\n");
        printf("3-Patronymic\n");
        printf("4-Address\n");
        printf("5-Groupnumber\n");
        printf("6-Rating\n");
        printf("7-Number\n");
        printf("8-Exit\n");
        printf("Your choice: ");
        
        switch(input_check_int())
        {
              case 1:
                  printf("Enter lastname\n");
                  rewind(stdin);
                  fgets(enter_string, 20, stdin);
                  string_to_lowercase(enter_string);
                  for(int i = 0;i < amount;i++)
                  {
                      strcpy(buf_string,pointer[i].lastname);
                      string_to_lowercase(buf_string);
                      if(!strcmp(buf_string,enter_string))
                      {
                          delete_student(pointer,i,amount);
                      }
                  }
                  break;
              case 2:
                  printf("Enter name\n");
                  rewind(stdin);
                  fgets(enter_string, 20, stdin);
                  string_to_lowercase(enter_string);
                  for(int i = 0;i < amount;i++)
                  {
                      strcpy(buf_string,pointer[i].name);
                      string_to_lowercase(buf_string);
                      if(!strcmp(buf_string,enter_string))
                      {
                          delete_student(pointer,i,amount);
                      }
                  }
                  break;
              case 3:
                  printf("Enter patronymic\n");
                  rewind(stdin);
                  fgets(enter_string, 20, stdin);
                  string_to_lowercase(enter_string);
                  for(int i = 0;i < amount;i++)
                  {
                      strcpy(buf_string,pointer[i].patronymic);
                      string_to_lowercase(buf_string);
                      if(!strcmp(buf_string,enter_string))
                      {
                          delete_student(pointer,i,amount);
                      }
                  }
                  break;
              case 4:
                  printf("Enter address\n");
                  rewind(stdin);
                  fgets(enter_string, 20, stdin);
                  string_to_lowercase(enter_string);
                  for(int i = 0;i < amount;i++)
                  {
                      strcpy(buf_string,pointer[i].address);
                      string_to_lowercase(buf_string);
                      if(!strcmp(buf_string,enter_string))
                      {
                          delete_student(pointer,i,amount);
                      }
                  }
                  break;
              case 5:
                  printf("Enter groupnumber\n");
                  rewind(stdin);
                  fgets(enter_string, 20, stdin);
                  string_to_lowercase(enter_string);
                  for(int i = 0;i < amount;i++)
                  {
                      strcpy(buf_string,pointer[i].group_number);
                      string_to_lowercase(buf_string);
                      if(!strcmp(buf_string,enter_string))
                      {
                          delete_student(pointer,i,amount);
                      }
                  }
                  break;
              case 6:
                  printf("Enter rating\n");
                  rewind(stdin);
                  for(int i = 0;i < amount;i++)
                  {
                      if(pointer[i].rating == input_check_float())
                      {
                          delete_student(pointer,i,amount);
                      }
                  }
                  break;
              case 7:
                  printf("Enter number\n");
                  rewind(stdin);
                  number = input_check_int()-1;
                  delete_student(pointer,number,amount);
                  break;
              case 8:
                  free(buf_string);
                  free(enter_string);
                  return;
              default:
                  printf("Wrong number\n");
        }
    }
}

void delete_student(struct student* pointer,int index,int& amount)
{
    if (index == amount-1 && confirmation() == 1)
    {
        amount--;
        pointer = (struct student*)realloc(pointer,amount * sizeof(struct student));
    }
    
    if (index != amount && confirmation() == 1)
    {
        for (; index+1 < amount; index++)
        {
            pointer[index] = pointer[index+1];
        }
        amount--;
        pointer = (struct student*)realloc(pointer,amount * sizeof(struct student));
    }
}

void edit_student(struct student *pointer, int amount)
{
    int number;
    char *buf_string = (char*)malloc(20*sizeof(char));
    
    if (!pointer)
    {
       printf("No students:(\n");
       return;
    }
    
    printf("Choose what student you want to edit\n");
    printf("Your choice: ");
    number = input_check_int();
    
    while(1)
    {
        printf("1-Lastname\n");
        printf("2-Name\n");
        printf("3-Patronymic\n");
        printf("4-Address\n");
        printf("5-Groupnumber\n");
        printf("6-Rating\n");
        printf("7-Exit\n");
        
        switch (input_check_int())
        {
            case 1:
                while(1)
                {
                    printf("Enter student's lastname: ");
                    rewind(stdin);
                    fgets(buf_string,20,stdin);
                    if(buf_string[0] != '\0' && buf_string[0] != '\n' && buf_string[0] != ' ' && check_string_for_number(buf_string) == 0)break;
                }
                if(confirmation() == 1)
                    strcpy(pointer[number-1].lastname,buf_string);
                rewind(stdin);
                break;
            case 2:
                while(1)
                {
                    printf("Enter student's name: ");
                    rewind(stdin);
                    fgets(buf_string,20,stdin);
                    if(buf_string[0] != '\0' && buf_string[0] != '\n' && buf_string[0] != ' ' && check_string_for_number(buf_string) == 0)break;
                }
                if(confirmation() == 1)
                    strcpy(pointer[number-1].name,buf_string);
                rewind(stdin);
                break;
            case 3:
                while(1)
                {
                    printf("Enter student's patronymic: ");
                    rewind(stdin);
                    fgets(buf_string,20,stdin);
                    if(buf_string[0] != '\0' && buf_string[0] != '\n' && buf_string[0] != ' ' && check_string_for_number(buf_string) == 0)break;
                }
                if(confirmation() == 1)
                    strcpy(pointer[number-1].patronymic,buf_string);
                rewind(stdin);
                break;
            case 4:
                while(1)
                {
                    printf("Enter student's address: ");
                    rewind(stdin);
                    fgets(buf_string,20,stdin);
                    if(buf_string[0] != '\0' && buf_string[0] != '\n' && buf_string[0] != ' ' )break;
                }
                if(confirmation() == 1)
                    strcpy(pointer[number-1].address,buf_string);
                rewind(stdin);
                break;
            case 5:
                while(1)
                {
                    printf("Enter student's groupnumber: ");
                    rewind(stdin);
                    fgets(buf_string,20,stdin);
                    if(buf_string[0] != '\0' && buf_string[0] != '\n' && buf_string[0] != ' ')break;
                }
                if(confirmation() == 1)
                    strcpy(pointer[number-1].group_number,buf_string);
                rewind(stdin);
                break;
            case 6:
                printf("Enter new student's rating: ");
                rewind(stdin);
                if(confirmation() == 1)
                    pointer[number-1].rating = input_check_float();
                rewind(stdin);
            case 7:
                free(buf_string);
                return;
            default:
                printf("Wrong number\n");
        }
    }
}

void find(struct student *pointer, int amount)
{
    char *enter_string = (char*)malloc(20*sizeof(char));
    char *buf_string = (char*)malloc(20*sizeof(char));

    if (!pointer)
    {
       printf("No students:(\n");
       return;
    }
    
    while(1)
    {
        printf("What to find\n");
        printf("1-Lastname\n");
        printf("2-Name\n");
        printf("3-Patronymic\n");
        printf("4-Address\n");
        printf("5-Groupnumber\n");
        printf("6-Rating\n");
        printf("7-Exit\n");
        printf("Your choice: ");
        
        switch(input_check_int())
        {
            case 1:
                printf("Enter lastname\n");
                rewind(stdin);
                fgets(enter_string, 20, stdin);
                string_to_lowercase(enter_string);
                for(int i = 0;i < amount;i++)
                {
                    strcpy(buf_string,pointer[i].lastname);
                    string_to_lowercase(buf_string);
                    if(!strcmp(buf_string,enter_string))
                    {
                        output_student(pointer[i]);
                    }
                }
                break;
            case 2:
                printf("Enter name\n");
                rewind(stdin);
                fgets(enter_string, 20, stdin);
                string_to_lowercase(enter_string);
                for(int i = 0;i < amount;i++)
                {
                    strcpy(buf_string,pointer[i].name);
                    string_to_lowercase(buf_string);
                    if(!strcmp(buf_string,enter_string))
                    {
                        output_student(pointer[i]);
                    }
                }
                break;
            case 3:
                printf("Enter patronymic\n");
                rewind(stdin);
                fgets(enter_string, 20, stdin);
                string_to_lowercase(enter_string);
                for(int i = 0;i < amount;i++)
                {
                    strcpy(buf_string,pointer[i].patronymic);
                    string_to_lowercase(buf_string);
                    if(!strcmp(buf_string,enter_string))
                    {
                        output_student(pointer[i]);
                    }
                }
                break;
            case 4:
                printf("Enter address\n");
                rewind(stdin);
                fgets(enter_string, 20, stdin);
                string_to_lowercase(enter_string);
                for(int i = 0;i < amount;i++)
                {
                    strcpy(buf_string,pointer[i].address);
                    string_to_lowercase(buf_string);
                    if(!strcmp(buf_string,enter_string))
                    {
                        output_student(pointer[i]);
                    }
                }
                break;
            case 5:
                printf("Enter groupnumber\n");
                rewind(stdin);
                fgets(enter_string, 20, stdin);
                string_to_lowercase(enter_string);
                for(int i = 0;i < amount;i++)
                {
                    strcpy(buf_string,pointer[i].group_number);
                    string_to_lowercase(buf_string);
                    if(!strcmp(buf_string,enter_string))
                    {
                        output_student(pointer[i]);
                    }
                }
                break;
            case 6:
                printf("Enter rating\n");
                rewind(stdin);

                for(int i = 0;i < amount;i++)
                {
                    if(pointer[i].rating == input_check_float())
                    {
                        output_student(pointer[i]);
                    }
                }
                break;
            case 7:
                free(buf_string);
                free(enter_string);
                return;
            default:
                printf("Wrong number\n");
        }
    }
}

void output_student(struct student pointer)
{
    printf("Lastname: %s\n", pointer.lastname);
    printf("Name: %s\n", pointer.name);
    printf("Patronymic: %s\n", pointer.patronymic);
    printf("Home address: %s\n", pointer.address);
    printf("Group number: %s\n", pointer.group_number);
    printf("Rating: %.2f\n", pointer.rating);
    printf("\n");
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

void header_sort(struct student *pointer, int amount)
{
    
    if (!pointer)
    {
       printf("No students:(\n");
       return;
    }
    
    while(1)
      {
          printf("Сhoose by which parameter you want to sort\n");
          printf("1-By lastname\n");
          printf("2-By name\n");
          printf("3-By patronymic\n");
          printf("4-By address\n");
          printf("5-By groupnumber\n");
          printf("6-By rating\n");
          printf("7-Exit\n");
          printf("Your choice: ");
          
          switch(input_check_int())
          {
            case 1:
                  sort_lastname(pointer,amount);break;
            case 2:
                  sort_name(pointer,amount);break;
            case 3:
                  sort_patronymic(pointer,amount);break;
            case 4:
                  sort_address(pointer,amount);break;
            case 5:
                  sort_groupnumber(pointer,amount);break;
            case 6:
                  sort_rating(pointer,amount);break;
            case 7:
                  return;
            default:
                printf("Wrong number\n");
          }
      }
}

void sort_lastname(struct student *pointer, int amount)
{
    struct student temp;
    
    printf("\n1 - In ascending order\n");
    printf("2 - In descending order\n");
    printf("Your choice: ");
    
    if(input_check_int_for_sort() == 1)
    {
        for(int i = 0; i< amount-1;i++)
            for(int j = 1; j< amount; j++)
            {
                if(strcmp(pointer[i].lastname,pointer[j].lastname) > 0)
                {
                    temp = pointer[i];
                    pointer[i] = pointer[j];
                    pointer[j] = temp;
                }
            }
    }else
    {
        for(int i = 0; i< amount-1;i++)
            for(int j = 1; j< amount; j++)
            {
                if(strcmp(pointer[i].lastname,pointer[j].lastname) < 0)
                {
                    temp = pointer[i];
                    pointer[i] = pointer[j];
                    pointer[j] = temp;
                }
            }
    }
    printf("Sorted successfully\n");
}

void sort_name(struct student *pointer, int amount)
{
    struct student temp;
    
    printf("\n1 - In ascending order\n");
    printf("2 - In descending order\n");
    printf("Your choice: ");
    
    if(input_check_int_for_sort() == 1)
    {
        for(int i = 0; i< amount-1;i++)
            for(int j = 1; j< amount; j++)
            {
                if(strcmp(pointer[i].name,pointer[j].name) > 0)
                {
                    temp = pointer[i];
                    pointer[i] = pointer[j];
                    pointer[j] = temp;
                }
            }
    }else
    {
        for(int i = 0; i< amount-1;i++)
            for(int j = 1; j< amount; j++)
            {
                if(strcmp(pointer[i].name,pointer[j].name) < 0)
                {
                    temp = pointer[i];
                    pointer[i] = pointer[j];
                    pointer[j] = temp;
                }
            }
    }
    printf("Sorted successfully\n");
}

void sort_patronymic(struct student *pointer, int amount)
{
    struct student temp;
    
    printf("\n1 - In ascending order\n");
    printf("2 - In descending order\n");
    printf("Your choice: ");
    
    if(input_check_int_for_sort() == 1)
    {
        for(int i = 0; i< amount-1;i++)
            for(int j = 1; j< amount; j++)
            {
                if(strcmp(pointer[i].patronymic,pointer[j].patronymic) > 0)
                {
                    temp = pointer[i];
                    pointer[i] = pointer[j];
                    pointer[j] = temp;
                }
            }
    }else
    {
        for(int i = 0; i< amount-1;i++)
            for(int j = 1; j< amount; j++)
            {
                if(strcmp(pointer[i].patronymic,pointer[j].patronymic) < 0)
                {
                    temp = pointer[i];
                    pointer[i] = pointer[j];
                    pointer[j] = temp;
                }
            }
    }
    printf("Sorted successfully\n");
}

void sort_address(struct student *pointer, int amount)
{
    struct student temp;
    
    printf("\n1 - In ascending order\n");
    printf("2 - In descending order\n");
    printf("Your choice: ");
    if(input_check_int_for_sort() == 1)
    {
        for(int i = 0; i< amount-1;i++)
            for(int j = 1; j< amount; j++)
            {
                if(strcmp(pointer[i].address,pointer[j].address) > 0)
                {
                    temp = pointer[i];
                    pointer[i] = pointer[j];
                    pointer[j] = temp;
                }
            }
    }else
    {
        for(int i = 0; i< amount-1;i++)
            for(int j = 1; j< amount; j++)
            {
                if(strcmp(pointer[i].address,pointer[j].address) < 0)
                {
                    temp = pointer[i];
                    pointer[i] = pointer[j];
                    pointer[j] = temp;
                }
            }
    }
    printf("Sorted successfully\n");
}

void sort_groupnumber(struct student *pointer, int amount)
{
    struct student temp;
    
    printf("\n1 - In ascending order\n");
    printf("2 - In descending order\n");
    printf("Your choice: ");
    
    if(input_check_int_for_sort() == 1)
    {
        for(int i = 0; i< amount-1;i++)
            for(int j = 1; j< amount; j++)
            {
                if(strcmp(pointer[i].group_number,pointer[j].group_number) > 0)
                {
                    temp = pointer[i];
                    pointer[i] = pointer[j];
                    pointer[j] = temp;
                }
            }
    }else
    {
        for(int i = 0; i< amount-1;i++)
            for(int j = 1; j< amount; j++)
            {
                if(strcmp(pointer[i].group_number,pointer[j].group_number) < 0)
                {
                    temp = pointer[i];
                    pointer[i] = pointer[j];
                    pointer[j] = temp;
                }
            }
    }
    printf("Sorted successfully\n");
}

void sort_rating(struct student *pointer, int amount)
{
    struct student temp;
    
    printf("\n1 - In ascending order\n");
    printf("2 - In descending order\n");
    printf("Your choice: ");
    
    if(input_check_int_for_sort() == 1)
    {
        for(int i = 0; i< amount-1;i++)
            for(int j = 1; j< amount; j++)
            {
                if(pointer[i].rating > pointer[j].rating)
                {
                    temp = pointer[i];
                    pointer[i] = pointer[j];
                    pointer[j] = temp;
                }
            }
    }else
    {
        for(int i = 0; i< amount-1;i++)
            for(int j = 1; j< amount; j++)
            {
                if(pointer[i].rating < pointer[j].rating)
                {
                    temp = pointer[i];
                    pointer[i] = pointer[j];
                    pointer[j] = temp;
                }
            }
    }
    printf("Sorted successfully\n");
}

void part_find(struct student* pointer,int amount)
{
    char *enter_string = (char*)malloc(20*sizeof(char));
    char *buf_string = (char*)malloc(20*sizeof(char));
    
    if (!pointer)
    {
       printf("No students:(\n");
       return;
    }
    
    while(1)
    {
        printf("What to find\n");
        printf("1-Lastname\n");
        printf("2-Name\n");
        printf("3-Patronymic\n");
        printf("4-Address\n");
        printf("5-Groupnumber\n");
        printf("6-Rating\n");
        printf("7-Exit\n");
        printf("Your choice: ");
        
        switch(input_check_int())
        {
            case 1:
                printf("Enter lastname\n");
                rewind(stdin);
                getstring(enter_string,20);
                string_to_lowercase(enter_string);
                for(int i = 0;i < amount;i++)
                {
                    strcpy(buf_string,pointer[i].lastname);
                    string_to_lowercase(buf_string);
                    if(strstr(buf_string,enter_string))
                    {
                        output_student(pointer[i]);
                    }
                }
                break;
            case 2:
                printf("Enter name\n");
                rewind(stdin);
                getstring(enter_string,20);
                string_to_lowercase(enter_string);
                for(int i = 0;i < amount;i++)
                {
                    strcpy(buf_string,pointer[i].name);
                    string_to_lowercase(buf_string);
                    if(strstr(buf_string,enter_string))
                    {
                        output_student(pointer[i]);
                    }
                }
                break;
            case 3:
                printf("Enter patronymic\n");
                rewind(stdin);
                getstring(enter_string,20);
                string_to_lowercase(enter_string);
                for(int i = 0;i < amount;i++)
                {
                    strcpy(buf_string,pointer[i].patronymic);
                    string_to_lowercase(buf_string);
                    if(strstr(buf_string,enter_string))
                    {
                        output_student(pointer[i]);
                    }
                }
                break;
            case 4:
                printf("Enter address\n");
                rewind(stdin);
                getstring(enter_string,20);
                string_to_lowercase(enter_string);
                for(int i = 0;i < amount;i++)
                {
                    strcpy(buf_string,pointer[i].address);
                    string_to_lowercase(buf_string);
                    if(strstr(buf_string,enter_string))
                    {
                        output_student(pointer[i]);
                    }
                }
                break;
            case 5:
                printf("Enter groupnumber\n");
                rewind(stdin);
                getstring(enter_string,20);
                string_to_lowercase(enter_string);
                for(int i = 0;i < amount;i++)
                {
                    strcpy(buf_string,pointer[i].group_number);
                    string_to_lowercase(buf_string);
                    if(strstr(buf_string,enter_string))
                    {
                        output_student(pointer[i]);
                    }
                }
                break;
            case 6:
                printf("Enter rating\n");
                rewind(stdin);

                for(int i = 0;i < amount;i++)
                {
                    if(pointer[i].rating == input_check_float())
                    {
                        delete_student(pointer,i,amount);
                    }
                }
                break;
            case 7:
                free(buf_string);
                free(enter_string);
                return;
            default:
                printf("Wrong number\n");
        
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

void add_student(struct student* pointer,int &amount)
{
    int index;
    int i;
    int buf;
    
    if (!pointer)
    {
       printf("No students:(\n");
       return;
    }
    
    index = amount;
    printf("Enter amount of students to add: ");
    buf=input_check_int();
    amount+=buf;

    for(int i = 0;i<buf;i++)pointer = (struct student*)realloc(pointer,1 * sizeof(struct student));
    
    for(i = index;i < amount;i++)
    {
        printf("\nStudent %d: \n",i+1);
        while(1)
        {
            printf("Enter student's lastname: ");
            rewind(stdin);
            fgets(pointer[i].lastname,20,stdin);
            if(pointer[i].lastname[0] != '\0' && pointer[i].lastname[0] != '\n' && pointer[i].lastname[0] != ' ' && check_string_for_number(pointer[i].lastname) == 0)break;
        }
        while(1)
        {
            printf("Enter student's name: ");
            rewind(stdin);
            fgets(pointer[i].name,20,stdin);
            if(pointer[i].name[0] != '\0' && pointer[i].name[0] != '\n' && pointer[i].name[0] != ' ' && check_string_for_number(pointer[i].name) == 0)break;
        }
        while(1)
        {
            printf("Enter student's patronymic: ");
            rewind(stdin);
            fgets(pointer[i].patronymic,20,stdin);
            if(pointer[i].patronymic[0] != '\0' && pointer[i].patronymic[0] != '\n' && pointer[i].patronymic[0] != ' ' && check_string_for_number(pointer[i].patronymic) == 0)break;
        }
        while(1)
        {
            printf("Enter student's address: ");
            rewind(stdin);
            fgets(pointer[i].address,20,stdin);
            if(pointer[i].address[0] != '\0' && pointer[i].address[0] != '\n' && pointer[i].address[0] != ' ')break;
        }
        while(1)
        {
            printf("Enter student's groupnumber: ");
            rewind(stdin);
            fgets(pointer[i].group_number,20,stdin);
            if(pointer[i].group_number[0] != '\0' && pointer[i].group_number[0] != '\n' && pointer[i].group_number[0] != ' ')break;
        }
        printf("Enter student's rating: ");
        rewind(stdin);
        pointer[i].rating = input_check_float();
    }
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

/*
void header_sort(struct student *pointer, int amount)
{
    int choice;
    
    if (!pointer)
    {
       printf("No students:(\n");
       return;
    }
    
    while(1)
      {
          printf("Choose how you want to sort\n");
          printf("1-sort lastnames in ascending order\n");
          printf("2-sort lastnames in descending order\n");
          
          printf("3-sort names in ascending order\n");
          printf("4-sort names in descending order\n");
          
          printf("5-sort patronymics in ascending order\n");
          printf("6-sort patronymics in descending order\n");
          
          printf("7-sort addresses in ascending order\n");
          printf("8-sort addresses in descending order\n");
          
          printf("9-sort group numbers in ascending order\n");
          printf("10-sort group numbers in descending order\n");
          
          printf("11-sort ratings in ascending order\n");
          printf("12-sort ratings in descending order\n");
          printf("13-exit\n");
          
          printf("Your choice: ");
          scanf("%d",&choice);
          switch(choice)
          {
            case 1:
                  sort_lastname_ascending_order(pointer,amount);
                  break;
            case 2:
                  sort_lastname_descending_order(pointer,amount);
                  break;
            case 3:
                  sort_name_ascending_order(pointer,amount);
                  break;
            case 4:
                  sort_name_descending_order(pointer,amount);
                  break;
            case 5:
                  sort_patronymic_ascending_order(pointer,amount);
                  break;
            case 6:
                  sort_patronymic_descending_order(pointer,amount);
                  break;
            case 7:
                  sort_address_ascending_order(pointer,amount);
                  break;
            case 8:
                  sort_address_descending_order(pointer,amount);
                  break;
            case 9:
                  sort_groupnumber_ascending_order(pointer,amount);
                  break;
            case 10:
                  sort_groupnumber_descending_order(pointer,amount);
                  break;
            case 11:
                  sort_rating_ascending_order(pointer,amount);
                  break;
            case 12:
                  sort_rating_descending_order(pointer,amount);
                  break;
            case 13:
                  return;
          }
      }
}

void sort_lastname_ascending_order(struct student* pointer,int amount)
{
    struct student temp;
    for(int i = 0; i< amount-1;i++)
        for(int j = 1; j< amount; j++)
        {
            if(strcmp(pointer[i].lastname,pointer[j].lastname) > 0)
            {
                temp = pointer[i];
                pointer[i] = pointer[j];
                pointer[j] = temp;
            }
        }
    printf("Sorted successfully\n");
}

void sort_lastname_descending_order(struct student* pointer,int amount)
{
    struct student temp;
    for(int i = 0; i< amount-1;i++)
        for(int j = 1; j< amount; j++)
        {
            if(strcmp(pointer[i].lastname,pointer[j].lastname) < 0)
            {
                temp = pointer[i];
                pointer[i] = pointer[j];
                pointer[j] = temp;
            }
        }
    printf("Sorted successfully\n");
}

void sort_name_ascending_order(struct student* pointer,int amount)
{
    struct student temp;
    for(int i = 0; i< amount-1;i++)
        for(int j = 1; j< amount; j++)
        {
            if(strcmp(pointer[i].name,pointer[j].name) > 0)
            {
                temp = pointer[i];
                pointer[i] = pointer[j];
                pointer[j] = temp;
            }
        }
    printf("Sorted successfully\n");
}

void sort_name_descending_order(struct student* pointer,int amount)
{
    struct student temp;
    for(int i = 0; i< amount-1;i++)
        for(int j = 1; j< amount; j++)
        {
            if(strcmp(pointer[i].name,pointer[j].name) < 0)
            {
                temp = pointer[i];
                pointer[i] = pointer[j];
                pointer[j] = temp;
            }
        }
    printf("Sorted successfully\n");
}

void sort_patronymic_ascending_order(struct student* pointer,int amount)
{
    struct student temp;
    for(int i = 0; i< amount-1;i++)
        for(int j = 1; j< amount; j++)
        {
            if(strcmp(pointer[i].patronymic,pointer[j].patronymic) > 0)
            {
                temp = pointer[i];
                pointer[i] = pointer[j];
                pointer[j] = temp;
            }
        }
    printf("Sorted successfully\n");
}

void sort_patronymic_descending_order(struct student* pointer,int amount)
{
    struct student temp;
    for(int i = 0; i< amount-1;i++)
        for(int j = 1; j< amount; j++)
        {
            if(strcmp(pointer[i].patronymic,pointer[j].patronymic) < 0)
            {
                temp = pointer[i];
                pointer[i] = pointer[j];
                pointer[j] = temp;
            }
        }
    printf("Sorted successfully\n");
}

void sort_address_ascending_order(struct student* pointer,int amount)
{
    struct student temp;
    for(int i = 0; i< amount-1;i++)
        for(int j = 1; j< amount; j++)
        {
            if(strcmp(pointer[i].address,pointer[j].address) > 0)
            {
                temp = pointer[i];
                pointer[i] = pointer[j];
                pointer[j] = temp;
            }
        }
    printf("Sorted successfully\n");
}

void sort_address_descending_order(struct student* pointer,int amount)
{
    struct student temp;
    for(int i = 0; i< amount-1;i++)
        for(int j = 1; j< amount; j++)
        {
            if(strcmp(pointer[i].address,pointer[j].address) < 0)
            {
                temp = pointer[i];
                pointer[i] = pointer[j];
                pointer[j] = temp;
            }
        }
    printf("Sorted successfully\n");
}

void sort_groupnumber_ascending_order(struct student* pointer,int amount)
{
    struct student temp;
    for(int i = 0; i< amount-1;i++)
        for(int j = 1; j< amount; j++)
        {
            if(strcmp(pointer[i].group_number,pointer[j].group_number) > 0)
            {
                temp = pointer[i];
                pointer[i] = pointer[j];
                pointer[j] = temp;
            }
        }
    printf("Sorted successfully\n");
}

void sort_groupnumber_descending_order(struct student* pointer,int amount)
{
    struct student temp;
    for(int i = 0; i< amount-1;i++)
        for(int j = 1; j< amount; j++)
        {
            if(strcmp(pointer[i].group_number,pointer[j].group_number) < 0)
            {
                temp = pointer[i];
                pointer[i] = pointer[j];
                pointer[j] = temp;
            }
        }
    printf("Sorted successfully\n");
}

void sort_rating_ascending_order(struct student* pointer,int amount)
{
    struct student temp;
    for(int i = 0; i< amount-1;i++)
        for(int j = 1; j< amount; j++)
        {
            if(pointer[i].rating > pointer[j].rating)
            {
                temp = pointer[i];
                pointer[i] = pointer[j];
                pointer[j] = temp;
            }
        }
    printf("Sorted successfully\n");
}

void sort_rating_descending_order(struct student* pointer,int amount)
{
    struct student temp;
    for(int i = 0; i< amount-1;i++)
        for(int j = 1; j< amount; j++)
        {
            if(pointer[i].rating < pointer[j].rating)
            {
                temp = pointer[i];
                pointer[i] = pointer[j];
                pointer[j] = temp;
            }
        }
    printf("Sorted successfully\n");
}
*/
