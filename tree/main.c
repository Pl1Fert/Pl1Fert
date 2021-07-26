#include "Functions.h"

int main()
{
    struct tree *root = NULL;
    struct dictionary record;
    char string[30];
    
    while(1)
    {
        switch(menu())
        {
            case 1:
                do
                {
                    record = input_info();
                    root = push(root,record);
                    
                    printf("To add else?\n");
                    printf("1-yes\n");
                    printf("2-no\n");
                    printf("Your choice: ");
                }while(input_check_int_for_sort() == 1);
                break;
            case 2:
                if (!root)
                {
                    printf("No records :(");
                    break;
                }
                output_menu(root);
                break;
            case 3:
                    do
                    {
                        printf("Еnter a word to find a record: ");
                        rewind(stdin);
                        fgets(string,30,stdin);
                    }while(check_string_for_number(string) == 1);
                    
                    output_record(search(root,string));
                break;
            case 4:
                do
                {
                    printf("Еnter a word to delete a record: ");
                    rewind(stdin);
                    fgets(string,30,stdin);
                }while(check_string_for_number(string) == 1);
                deletion(&root,string);
                //root = tree_balance(root);
                printf("Deleted succesfully!\n");
                break;
            case 5:
                full_deletion(&root);
                printf("Deleted succesfully!\n");
                return 0;
                //break;
            default:
                printf("Wrong number\n");
        }
    }
}

