#include "Functionss.h"

int main()
{
    struct car *top = NULL;
    while(1)
    {
        switch(menu())
        {
            case 1:
                input_info(&top);
                break;
            case 2:
                output_info(top);
                break;
            case 3:
                top = delete(top);
                break;
            case 4:
                search(top);
                break;
            case 5:
                input_in_file(top);
                break;
            case 6:
                load_from_file(&top);
                break;
            case 7:
                top = NULL;
                free(top);
                return 0;
            default:
                printf("Wrong number\n");
        }
    }
}
