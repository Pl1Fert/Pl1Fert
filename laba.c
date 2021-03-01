//
//  main.cpp
//  test
//
//  Created by AlexeyRusel on 2/28/21.
//  Copyright © 2021 PL1Fert. All rights reserved.
//

//
//  main.c
//  mainFIle
//
//  Created by AlexeyRusel on 2/21/21.
//  Copyright © 2021 PL1Fert. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
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

 int main()
 {
     int read_count, is_empty;
     int n;
     
      while (1)
     {
         read_count = scanf("%d", &n);
         is_empty = ClearStdin();
         if (read_count == 1 && is_empty != 0 && n > 0)
         {
             break;
         }
         printf("Неверный формат числа. Введите целое положительное число\n");
     }
 */


struct student
{
    char lastname[20];
    char name[20];
    char patronymic[20];
    char address[20];
    char group_number[20];
    float rating;

};

int menu(void);
void enter_struct(struct student*,int amount);
void output_struct(struct student*,int amount);
void header_delete(struct student*,int &amount);
void delete_student(struct student*,int index,int &amount);
void edit_student(struct student*,int amount);
int confirmation(void);
void find(struct student*,int amount);
void string_to_lowercase(char *string);
void output_student(struct student pointer);

void header_sort(struct student*,int amount);
void sort_lastname_ascending_order(struct student*,int amount);
void sort_lastname_descending_order(struct student*,int amount);

void sort_name_ascending_order(struct student*,int amount);
void sort_name_descending_order(struct student*,int amount);

void sort_patronymic_ascending_order(struct student*,int amount);
void sort_patronymic_descending_order(struct student*,int amount);

void sort_address_ascending_order(struct student*,int amount);
void sort_address_descending_order(struct student*,int amount);

void sort_groupnumber_ascending_order(struct student*,int amount);
void sort_groupnumber_descending_order(struct student*,int amount);

void sort_rating_ascending_order(struct student*,int amount);
void sort_rating_descending_order(struct student*,int amount);


int main()
{
    int amount = 0;
    struct student *pointer = NULL;
    while(1)
    {
        switch(menu())
        {
            case 1:
                printf("Enter amount of students: ");
                scanf("%d",&amount);
                pointer = (struct student*)malloc(amount * sizeof(struct student));
                enter_struct(pointer, amount);
                break;
            case 2:
                output_struct(pointer,amount);
                break;
            case 3:
                header_delete(pointer,amount);
                break;
            case 4:
                header_sort(pointer,amount);
                break;
            case 5:
                edit_student(pointer,amount);
                break;
            case 6:
                find(pointer,amount);
                break;
            case 7:
                free(pointer);
                return 0;
        }
    }
    
    return 0;
}

int menu(void)
{
    int choice;
    printf("Choose a numebr\n");
    printf("1-enter a new struct\n");
    printf("2-output a struct\n");
    printf("3-delete selected student\n");
    printf("4-sort students\n");
    printf("5-edit selected student\n");
    printf("6-find students\n");
    printf("7-exit\n");
    printf("Your choice: ");
    scanf("%d",&choice);
    return choice;
}

void enter_struct(struct student *pointer,int amount)
{
    for(int i = 0;i < amount;i++)
    {
        printf("\nStudent %d: \n",i+1);
        printf("Enter student's lastname: ");
        rewind(stdin);
        fgets(pointer[i].lastname,20,stdin);
        
        printf("Enter student's name: ");
        rewind(stdin);
        fgets(pointer[i].name,20,stdin);
        
        printf("Enter student's patronymic: ");
        rewind(stdin);
        fgets(pointer[i].patronymic,20,stdin);
        
        printf("Enter student's address: ");
        rewind(stdin);
        fgets(pointer[i].address,20,stdin);
        
        printf("Enter student's group number: ");
        rewind(stdin);
        fgets(pointer[i].group_number,20,stdin);
        
        printf("Enter student's rating: ");
        rewind(stdin);
        scanf("%f",&pointer[i].rating);
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
    
    int choice;
    char *enter_string = (char*)malloc(20*sizeof(char));
    char *buf_string = (char*)malloc(20*sizeof(char));
    float buf_float;
    
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
      scanf("%d",&choice);
        
      switch(choice)
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
              scanf("%f",&buf_float);
              for(int i = 0;i < amount;i++)
              {
                  if(pointer[i].rating == buf_float)
                  {
                      output_student(pointer[i]);
                  }
              }
              break;
          case 7:
              free(buf_string);
              free(enter_string);
              return;
      }
    }
    /*
    printf("Choose what student you want to delete\n");
    printf("Your choice: ");
    scanf("%d",&number);
    
    printf("Enter a number of student to delete\n");
    printf("To delete all students enter '999'\n");
    printf("Your choice: ");
    scanf("%d", &number);
    number -=1;
    if(number == 999 && confirmation() == 1)
    {
        amount = 0;
        free(pointer);
    }
    
    if (number != 999 && number == amount-1 && confirmation() == 1)
    {
        amount--;
        pointer = (struct student*)realloc(pointer,amount * sizeof(struct student));
    }
    
    if (number != 999 && number != amount && confirmation() == 1)
    {
        for (; number+1 < amount; number++)
        {
            pointer[number] = pointer[number+1];
        }
        amount--;
        pointer = (struct student*)realloc(pointer,amount * sizeof(struct student));
    }
     */
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
    int number,choice;
    char *buf_string = (char*)malloc(20*sizeof(char));
    float buf_float;
    
    if (!pointer)
    {
       printf("No students:(\n");
       return;
    }
    
    printf("Choose what student you want to edit\n");
    printf("Your choice: ");
    scanf("%d",&number);
    
    while(1)
    {
        printf("1-Lastname\n");
        printf("2-Name\n");
        printf("3-Patronymic\n");
        printf("4-Address\n");
        printf("5-Groupnumber\n");
        printf("6-Rating\n");
        printf("7-Exit\n");
        scanf("%d",&choice);
        
        switch (choice)
        {
            case 1:
                printf("Enter new student's lastname: ");
                rewind(stdin);
                fgets(buf_string, 20, stdin);
                if(confirmation())
                    strcpy(pointer[number-1].lastname,buf_string);
                rewind(stdin);
                break;
            case 2:
                printf("Enter new student's name: ");
                rewind(stdin);
                fgets(buf_string, 20, stdin);
                if(confirmation())
                    strcpy(pointer[number-1].name,buf_string);
                rewind(stdin);
                break;
            case 3:
                printf("Enter new student's patronymic: ");
                rewind(stdin);
                fgets(buf_string, 20, stdin);
                if(confirmation())
                    strcpy(pointer[number-1].patronymic,buf_string);
                rewind(stdin);
                break;
            case 4:
                printf("Enter new student's address: ");
                rewind(stdin);
                fgets(buf_string, 20, stdin);
                if(confirmation())
                    strcpy(pointer[number-1].address,buf_string);
                rewind(stdin);
                break;
            case 5:
                printf("Enter new student's address: ");
                rewind(stdin);
                fgets(buf_string, 20, stdin);
                if(confirmation())
                    strcpy(pointer[number-1].group_number,buf_string);
                rewind(stdin);
                break;
            case 6:
                printf("Enter new student's address: ");
                rewind(stdin);
                scanf("%f",&buf_float);
                if(confirmation())
                    pointer[number-1].rating = buf_float;
                rewind(stdin);
            case 7:
                free(buf_string);
                return;
        }
    }
}

void find(struct student *pointer, int amount)
{
    int number;
    float buf_float;
    char *enter_string = (char*)malloc(20*sizeof(char));
    char *buf_string = (char*)malloc(20*sizeof(char));
    //char *buf_string_2 = (char*)malloc(20*sizeof(char));
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
        scanf("%d",&number);
        switch(number)
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
                scanf("%f",&buf_float);
                for(int i = 0;i < amount;i++)
                {
                    if(pointer[i].rating == buf_float)
                    {
                        output_student(pointer[i]);
                    }
                }
                break;
            case 7:
                free(buf_string);
                free(enter_string);
                return;
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
        //if(string[i] <= 'Z' && string[i] >= 'A')
        //string[i] += 'z'-'Z';
        i++;
    }
}

int confirmation()
{
    int choice;
    printf("Are you sure?\n");
    printf("1-Yes\n");
    printf("0-No\n");
    scanf("%d",&choice);
    return choice;
}

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


