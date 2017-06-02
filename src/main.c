#include <stdio.h>
#include <stdlib.h>
#include "devmem2.h"

int main()
{
    unsigned long readfrommemory = 0;

    readmem("0x01E00130", 'w', readfrommemory);

    printf("Value: 0x%X", readfrommemory);
    return 0;
}
