#include "lab2.1.h"

int averageCount(Words* words, int size)
{
    int average = 0;

    if (words == NULL)
    {
        printf("Invalid pointer: words is NULL.\n");
        return 0;
    }

    if (size == 0)
    {
        printf("Invalid size: size is zero.\n");
        return 0;
    }

    for (int i = 0; i < size; i++)
    {
        average += words[i].countWords;
    }

    return (average / size);
}

int averageLength(Words* words, int size)
{
    int average = 0;
    if (words == NULL)
    {
        printf("Invalid pointer: words is NULL.\n");
        return 0;
    }

    if (size == 0)
    {
        printf("Invalid size: size is zero.\n");
        return 0;
    }

    for (int i = 0; i < size; i++)
    {
        average += words[i].wordSize;
    }
    return (average / size);
}
