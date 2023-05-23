#include "lab.h"

int validateInputRange(int min, int max)
{
    int value = 0;
    scanf_s("%d", &value);
    while (value < min || value > max)
    {
        printf("Wrong input. Please enter a value between %d and %d.\n", min, max);
        rewind(stdin);
        scanf_s("%d", &value);
    }
    return value;
}

int validateInputValues(int value1, int value2, int value3)
{
    int value = 0;
    scanf_s("%d", &value);
    while (value != value1 && value != value2 && value != value3)
    {
        printf("Wrong input. Please enter a valid value.\n");
        rewind(stdin);
        scanf_s("%d", &value);
    }
    return value;
}

int validateInputValues(int value1, int value2, int value3, int value4)
{
    int value = 0;
    scanf_s("%d", &value);
    while (value != value1 && value != value2 && value != value3 && value != value4)
    {
        printf("Wrong input. Please enter a valid value.\n");
        rewind(stdin);
        scanf_s("%d", &value);
    }
    return value;
}



