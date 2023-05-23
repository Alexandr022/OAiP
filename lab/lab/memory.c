#include "lab.h"

lapTopArrayStruct* initLapTopArrayStruct(int size)
{
    lapTopArrayStruct* memory = (lapTopArrayStruct*)malloc(sizeof(lapTopArrayStruct));
    memory->size = size;
    memory->laptops = (lapTopStruct*)malloc(size * sizeof(lapTopStruct));
    if (memory == NULL)
    {
        printf("Error. Failed to allocate memory.\n");
        return NULL;
    }
    return memory;
}

void deleteStruct(lapTopArrayStruct* laptops)
{
    for (int i = 0; i < laptops->size; i++)
    {
        free(laptops[i].laptops);
    }

    free(laptops);
    printf("Choose the next action you want to take.\n");
    printf("1.At the begining.\n");
    printf("2.Close programm.\n");
    int count = 0;
    scanf_s("%d", &count);

    switch (count)
    {
    case 1:
        main();
        system("cls");
    case 2:
        return;
    default:
        return;
    }


}