#include "Functions.hpp"

int main()
{
    int amount = 0;
    struct car *pointer = NULL;
    while(1)
    {
        switch(menu())
        {
            case 1:
                printf("Enter amount of cars: ");
                scanf("%d",&amount);
                if(!(pointer = (struct car*)malloc(amount * sizeof(struct car))))
                {
                    printf("Something went wrong...");
                    return 0;
                }
                enter_struct(pointer, amount);
                break;
            case 2:
                output_struct(pointer,amount);
                break;
            case 3:
                header_delete(pointer,amount);
                break;
            case 4:
                find(pointer,amount);
                break;
            case 5:
                add_car(pointer,amount);
                break;
            case 6:
                find_max_engine_volume(pointer,amount);
                break;
            case 7:
                free(pointer);
                return 0;
            default:
                printf("Wrong number\n");
        }
    }
}
