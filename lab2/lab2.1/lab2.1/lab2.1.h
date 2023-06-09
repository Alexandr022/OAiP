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

void frequency(Words* words, int size);

void distribution(Words* words, int* size, Words** wordsArrayOne, Words** wordsArrayTwo);

int replaceWords(FILE* file, Words* wordsArrayOne, Words* wordsArrayTwo, int size, char* word);

void initializeArr(FILE* file, Words** words, int* size);
