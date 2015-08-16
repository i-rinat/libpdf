#include <stdio.h>

const void *
PPP_GetInterface(const char *interface_name);

int
main(void)
{
    printf("PPP_GetInterface: %p\n", &PPP_GetInterface);
    printf("pass\n");
    return 0;
}
