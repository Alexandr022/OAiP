#include "lab.h"

void menu()
{
    printf("----------------------------------------------------------------\n");
    printf("Select an action.\n");
    printf("1. Sort the array by each field of the structure.\n");
    printf("2. Sorting by two fields at the same time.\n");
    printf("3. Remove the structure from the array.\n");
    printf("4. Parsing HTML file.\n");
    printf("----------------------------------------------------------------\n");
}

int menuint(lapTopArrayStruct* laptops)
{
    menu();
    printf("Write a number from 1 to 3.\n");
    int count = 0;
    scanf_s("%d", &count);

    switch (count)
    {
    case 1:
        arraySort(laptops);
        break;
    case 2:
        return 0;
    case 3:
        deleteStruct(laptops);
        break;
    default:
        return 0;
    }
    return 0;
}