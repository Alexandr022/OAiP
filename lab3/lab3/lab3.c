// lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "lab3.h"

BMPfile initBMPstruct(FILE* file)
{
    BMPfile BMP;
    fread(&BMP.BMPHead, sizeof(BMP.BMPHead), 1, file);
    fread(&BMP.BMPinfo, sizeof(BMP.BMPinfo), 1, file);
    fseek(file, 0, SEEK_SET);
    BMP.head = (unsigned char*)malloc(BMP.BMPHead.offset);
    fread(BMP.head, sizeof(unsigned char), BMP.BMPHead.offset, file);

    int numPixels = BMP.BMPinfo.width * BMP.BMPinfo.height;
    int bytesPerPixel = BMP.BMPinfo.bitsPixels / 8;
    BMP.pixels = (unsigned char*)malloc(numPixels * bytesPerPixel);

    for (int i = 0; i < numPixels; i++) {
        if (fread(&BMP.pixels[i * bytesPerPixel], sizeof(unsigned char), bytesPerPixel, file) != bytesPerPixel) {
            printf("Error reading pixel data.\n");
            break;
        }
    }

    return BMP;
}

void outputBMPfile(FILE* file, BMPfile BMP)
{
	fwrite(BMP.head, sizeof(unsigned char), BMP.BMPHead.offset, file);

	for (int i = 0; i < BMP.BMPinfo.width * BMP.BMPinfo.height * BMP.BMPinfo.bitsPixels / 8; i++)
	{
		fwrite(&BMP.pixels[i], sizeof(unsigned char), 1, file);
	}
}

void convertToNegative(BMPfile BMP)
{
	for (int i = 0; i < BMP.BMPinfo.width * BMP.BMPinfo.height * BMP.BMPinfo.bitsPixels / 8; i++)
	{
		BMP.pixels[i]= ~BMP.pixels[i];
	}
}

void convertToBlackAndWhite(BMPfile BMP)
{
	if (BMP.BMPinfo.bitsPixels == 24)
	{
		unsigned char gray;

		for (int i = 0; i < BMP.BMPinfo.width * BMP.BMPinfo.height * BMP.BMPinfo.bitsPixels / 8; i += 3)
		{
			gray = (BMP.pixels[i] + BMP.pixels[i + 1] + BMP.pixels[i + 2]) / 3;
			BMP.pixels[i] = gray;
			BMP.pixels[i + 1] = gray;
			BMP.pixels[i + 2] = gray;
		}
	}
	
}

void copyPixelData(const unsigned char* srcPixels, unsigned char* destPixels, int size)
{
    for (int i = 0; i < size; i++) {
        destPixels[i] = srcPixels[i];
    }
}

void calculatePixelAverage(const unsigned char* tempPixels, const BMPINFOHEADER* BMPinfo, int x, int y, int filterSize, PixelAverage* average)
{
    int width = BMPinfo->width;
    int height = BMPinfo->height;
    int bitsPerPixel = BMPinfo->bitsPixels;
    
    for (int fy = -filterSize / 2; fy <= filterSize / 2; fy++) {
        for (int fx = -filterSize / 2; fx <= filterSize / 2; fx++) {
            int xi = x + fx;
            int yi = y + fy;
            if (xi >= 0 && xi < width && yi >= 0 && yi < height) {
                int index = ((height - yi - 1) * width + xi) * bitsPerPixel / 8;
                int b = tempPixels[index];
                int g = tempPixels[index + 1];
                int r = tempPixels[index + 2];
                average->blue += b;
                average->green += g;
                average->red += r;
                (average->count)++;
            }
        }
    }
}


void medianFilter(BMPfile* BMP, int filterSize)
{
  
    unsigned char* tempPixels = (unsigned char*)malloc(BMP->BMPinfo.width * BMP->BMPinfo.height * BMP->BMPinfo.bitsPixels / 8);

    if (tempPixels == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    copyPixelData(BMP->pixels, tempPixels, BMP->BMPinfo.width * BMP->BMPinfo.height * BMP->BMPinfo.bitsPixels / 8);

    unsigned int height = BMP->BMPinfo.height;
    unsigned int width = BMP->BMPinfo.width;
    int bitsPerPixel = BMP->BMPinfo.bitsPixels;

    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            int red = 0;
            int green = 0;
            int blue = 0;
            int count = 0;

            calculatePixelAverage(tempPixels, &BMP->BMPinfo, x, y, filterSize, &red, &green, &blue, &count);

            int index = ((height - y - 1) * width + x) * bitsPerPixel / 8;
            if (count > 0) {
                BMP->pixels[index] = (unsigned char)(blue / count);
                BMP->pixels[index + 1] = (unsigned char)(green / count);
                BMP->pixels[index + 2] = (unsigned char)(red / count);
            }
        }
    }
    
    free(tempPixels);
}
int comparePixels(const void* a, const void* b)
{
	const unsigned char* pixelA = (const unsigned char*)a;
	const unsigned char* pixelB = (const unsigned char*)b;

	if (*pixelA < *pixelB)
	{
		return -1;
	}
	if (*pixelA > *pixelB)
	{
		return 1;
	}
	return 0;
}

void gammaCorrection(BMPfile BMP, double gamma)
{
	for (int i = 0; i < BMP.BMPinfo.width * BMP.BMPinfo.height * BMP.BMPinfo.bitsPixels / 8; i++)
	{
		double oldValue = (double)BMP.pixels[i];
		double newValue = pow(oldValue / 255.0, 1.0 / gamma) * 255.0;
		BMP.pixels[i] = (unsigned char)newValue;
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
