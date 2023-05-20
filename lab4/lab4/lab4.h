#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <ctype.h>
#include "InputManager.h"

#define LENGTH 256
#define ZERO_STRING "NULL"

typedef struct
{
    char word[LENGTH];
    struct Node* left;
    struct Node* right;
} Node;

Node* initTree(FILE* inputFile);

void gameTree(Node* root);

void initNewTree(Node* root, FILE* outputFile);

void freeTree(Node* node);