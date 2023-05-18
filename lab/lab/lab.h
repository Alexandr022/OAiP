#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define true 1
#define false 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InputManager.h"

typedef enum 
{
    Windows_10,
    Windows_11,
    Linux,
    None,
}OCenum;

typedef enum 
{
    Black,
    Grey,
    White,
    Dark_Gray,
    Dark_Blue,
    Silver,
}Colorenum;

typedef struct {
    char name[200];
    int displaysize[2];
    int resolution[2];
    int frequency;
    char cpu[50];
    int ramsize;
    char ramtype[10];
    int storagesize;
    char storagetype[20];
    char gpu[100];
    int vram;
    OCenum OC;
    Colorenum color;
    float price;
}lapTopStruct;

typedef struct
{
    lapTopStruct* laptops;
    int size;
}lapTopArrayStruct;

int compareForSort(void* a, void* b);