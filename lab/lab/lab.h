#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define true 1
#define false 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sortCount;

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

void printLapTops(lapTopArrayStruct* laptops);

void arraySort(lapTopArrayStruct* laptops);

int compareForSort(const void* a, const void* b);

int initializeStructByHand();

int main();

lapTopArrayStruct* initLapTopArrayStruct(int size);

void deleteStruct(lapTopArrayStruct* laptops);

int menuint(lapTopArrayStruct* laptops);

void menu();

int validateInputRange(int min, int max);

int validateInputValues1(int value1, int value2, int value3);

int validateInputValues2(int value1, int value2, int value3, int value4);
