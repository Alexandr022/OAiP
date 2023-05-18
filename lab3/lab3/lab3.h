#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "InputManager.h"

#define COLOR_SIZE 1024

#pragma pack(push, 1)

typedef struct 
{
	unsigned short signatur;
	unsigned int size;
	unsigned int reserved;
	unsigned int offset;
}BMPHEADER;

typedef struct 
{
	unsigned int size;
	unsigned int width;
	unsigned int height;
	unsigned short planes;
	unsigned short bitsPixels;
	unsigned int compression;
	unsigned int imageSize;
	unsigned int XpixelsPerMeter;
	unsigned int YpixelsPerMeter;
	unsigned int colorsUsed;
	unsigned int colorsImportant;
}BMPINFOHEADER;

#pragma pack(pop)

typedef struct
{
	BMPHEADER BMPHead;
	BMPINFOHEADER BMPinfo;
	unsigned char* pixels;
	unsigned char* head;
}BMPfile;

int main();

void menu(BMPfile BMP);

BMPfile initBMPstruct(FILE* file);

int comparePixels(const void* a, const void* b);

void outputBMPfile(FILE* file, BMPfile BMP);

void convertToNegative(BMPfile BMP);

void convertToBlackAndWhite(BMPfile BMP);

void medianFilter(BMPfile* bmp, int filterSize);

void gammaCorrection(BMPfile BMP, double count);