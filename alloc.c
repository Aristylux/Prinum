#include "./headers/alloc.h"

/*
 * allocTest:
 * test if pointer is null
 * to avoid error
 */
/*
 * Example of use
 * [type] *[var] = ([type] *)malloc(sizeof([type]));
 *  if (allocTest[type]([var], "message error"))
 *       return EXIT_FAILURE;
 */
Bool allocTestChar(char *ptr, char *error_message)
{
    if (ptr == NULL)
    {
        printf("Allocation memory failed : %s", error_message);
        return 1;
    }
    else
        return 0;
}

Bool allocTestInt(int *ptr, char *error_message)
{
    if (ptr == NULL)
    {
        printf("Allocation memory failed : %s", error_message);
        return 1;
    }
    else
        return 0;
}

/*
void freePtrChar(char *ptr){
    free(ptr);
    ptr = NULL;
}
*/