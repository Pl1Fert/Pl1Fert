#include "Functionss.h"

int main()
{
    struct car *top = NULL;
    struct car *last = NULL;
    int number = 0;
    while(1)
    {
        switch(menu())
        {
            case 1:
                input_info(&top,&last);
                break;
            case 2:
                output_info(top);
                break;
            case 3:
                printf("Enter a number to delete: ");
                number = input_check_int();
                deletion(&top,&last,number);
                break;
            case 4:
                search(top);
                break;
            case 5:
                input_in_file(top);
                break;
            case 6:
                load_from_file(&top,&last);
                break;
            case 7:
                for(int i = 1;i < records_number(top);i++)
                    deletion(&top,&last,i);
                top = NULL;
                last = NULL;
                free(last);
                free(top);
                return 0;
            default:
                printf("Wrong number\n");
        }
    }
}
