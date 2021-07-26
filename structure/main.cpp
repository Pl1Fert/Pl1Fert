#include "Functions.hpp"

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
                part_find(pointer,amount);
                break;
            case 8:
                add_student(pointer,amount);
                break;
            case 9:
                free(pointer);
                return 0;
            default:
                printf("Wrong number\n");
        }
    }
}

