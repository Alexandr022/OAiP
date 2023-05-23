#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 3
#define COUNT 2

typedef struct
{
	char* word;
	int wordSize;
	int countWords;
	int freq;
}Words;

int averageCount(Words* words, int size);

int averageLength(Words* words, int size);

int isThereWord(Words* words, const char* word, int size);
